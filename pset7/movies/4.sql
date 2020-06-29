SELECT COUNT(movies.id) 
FROM movies INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;
