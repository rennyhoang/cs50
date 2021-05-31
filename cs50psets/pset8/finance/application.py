import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    currentUser = list(db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0].values())[0]
    portfolio = db.execute("SELECT symbol, sum(num) TOTAL, username, price, sum(total), name FROM transactions WHERE username=? GROUP BY symbol;", currentUser)
    cash = int(db.execute("SELECT cash FROM users WHERE username=?", currentUser)[0]["cash"])
    for row in portfolio:
        cash -= int(row["sum(total)"])
    endTotal = cash
    for row in portfolio:
        endTotal += int(row["sum(total)"])
    return render_template("index.html", portfolio = portfolio, cash = cash, endTotal = endTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        currentUser = list(db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0].values())[0]
        symbol = request.form.get("symbol")
        numOfStocks = request.form.get("numOfStocks")
        if not numOfStocks or numOfStocks == 0:
            return apology("please buy a stock")
        numOfStocks = int(numOfStocks)
        quote = lookup(symbol)
        if quote == None:
            return apology("stock does not exist")
        symbol = symbol.upper()
        price = int(quote["price"])
        cash = list(db.execute("SELECT cash FROM users WHERE username=?;", currentUser)[0].values())[0]
        name = quote["name"]

        if numOfStocks * price > cash:
            return apology("you cannot afford this purchase")

        db.execute("INSERT INTO transactions (symbol, num, username, price, total, name) VALUES (?, ?, ?, ?, ?, ?);", symbol, numOfStocks, currentUser, price, numOfStocks * price, name)
        return redirect("/")


@app.route("/history")
@login_required
def history():
    currentUser = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]
    transactions = db.execute("SELECT symbol, num, price, time FROM transactions WHERE username=?;", currentUser)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("stock does not exist")
        name = quote["name"]
        price = quote["price"]
        return render_template("quoted.html", name = name, symbol = symbol, price = price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method=="GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        if not username:
            return apology("please put a username")
        password = request.form.get("password")
        if not password:
            return apology("please put a password")
        passwordConfirmation = request.form.get("password-confirmation")
        if password != passwordConfirmation:
            return apology("please confirm your password")

        checkDuplicated = db.execute("SELECT * FROM users WHERE username == ?;", username)
        if len(checkDuplicated) != 0:
            return apology("this username is taken")

        password = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000);", username, password)
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method=="GET":
        currentUser = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]
        symbols = db.execute("SELECT symbol, sum(num) FROM transactions WHERE username=? GROUP BY symbol;", currentUser)
        return render_template("sell.html", symbols=symbols)
    else:
        currentUser = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("please input a symbol (or purchase a stock if there is no symbol)")
        numOfStocks = request.form.get("numOfStocks")
        if not numOfStocks or numOfStocks == '0':
            return apology("please sell a stock")
        numOfStocks = int(numOfStocks)
        numOfStocksOwned = int(db.execute("SELECT sum(num) TOTAL FROM transactions WHERE username=? AND symbol=? GROUP BY symbol;", currentUser, symbol)[0]["TOTAL"])

        if numOfStocksOwned < numOfStocks:
            return apology("you don't have enough stocks")

        quote = lookup(symbol)
        if quote == None:
            return apology("stock does not exist")
        price = int(quote["price"])
        name = quote["name"]

        db.execute("INSERT INTO transactions (symbol, num, username, price, total, name) VALUES (?, ?, ?, ?, ?, ?);", symbol, numOfStocks * -1, currentUser, price, numOfStocks * price * -1, name)
        return redirect("/")

@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():
    if request.method=="GET":
        currentUser = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]
        portfolio = db.execute("SELECT symbol, sum(num) TOTAL, username, price, sum(total), name FROM transactions WHERE username=? GROUP BY symbol;", currentUser)
        cash = int(db.execute("SELECT cash FROM users WHERE username=?", currentUser)[0]["cash"])
        for row in portfolio:
            cash -= int(row["sum(total)"])
        return render_template("addCash.html", cash = cash)
    else:
        currentUser = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]
        cash = int(db.execute("SELECT cash FROM users WHERE username=?", currentUser)[0]["cash"])
        cashToAdd = int(request.form.get("cashToAdd"))
        if cashToAdd <= 0:
            return apology("please input a positive number")
        db.execute("UPDATE users SET cash=? WHERE username=?", cash + cashToAdd, currentUser)
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
