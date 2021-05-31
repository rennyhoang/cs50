height = input("Height: ")

while True:
    try:
        height = int(height)
        break
    except:
        height = input("Height: ")

while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(0, height):
    counter = height - i
    spaceCounter = height - 1
    while counter > 1:
        print(" ", end="")
        counter -= 1
        spaceCounter -= 1
    
    spaceCounterCopy = spaceCounter
    
    while spaceCounter >= 0:
        print("#", end="")
        spaceCounter -= 1
    
    print("  ", end="")
    
    while spaceCounterCopy >= 0:
        print("#", end="")
        spaceCounterCopy -= 1
    
    print("\n", end="")