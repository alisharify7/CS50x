SELECT name FROM people WHERE id IN(
SELECT person_id FROM stars WHERE movie_id IN(
SELECT movie_id FROM stars WHERE person_id =(
    SELECT id FROM people WHERE name LIKE "Kevin Bacon" AND birth = 1958
))) AND name NOT LIKE "Kevin Bacon";