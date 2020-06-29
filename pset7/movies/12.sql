SELECT  movies.title
FROM ((stars INNER JOIN movies ON stars.movie_id = movies.id)
INNER JOIN people ON stars.person_id = people.id)
WHERE people.name ="Johnny Depp" AND movies.id IN (
SELECT stars.movie_id
FROM ((stars INNER JOIN movies ON stars.movie_id = movies.id)
INNER JOIN people ON stars.person_id = people.id)
WHERE people.name ="Helena Bonham Carter");

