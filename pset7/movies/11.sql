SELECT movies.title
FROM (((stars INNER JOIN movies ON stars.movie_id = movies.id)
INNER JOIN people ON people.id = stars.person_id)
INNER JOIN ratings ON stars.movie_id = ratings.movie_id)
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;