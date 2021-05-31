SELECT name
FROM people
JOIN stars ON stars.person_id=people.id
JOIN movies ON stars.movie_id=movies.id
WHERE name IN
    (SELECT name FROM people JOIN stars ON stars.person_id=people.id WHERE NOT (name=="Kevin Bacon" AND birth = 1958) AND movie_id IN (SELECT movie_id FROM stars JOIN people ON stars.person_id=people.id WHERE person_id==(SELECT id FROM people WHERE name=="Kevin Bacon" AND birth = 1958)))
GROUP BY people.id;