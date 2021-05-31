SELECT title
FROM movies
WHERE id IN (SELECT movies.id FROM movies JOIN stars ON movies.id=stars.movie_id JOIN people ON stars.person_id=people.id WHERE name == "Johnny Depp" intersect SELECT movies.id FROM movies JOIN stars ON movies.id=stars.movie_id JOIN people ON stars.person_id=people.id WHERE name == "Helena Bonham Carter")
;