select movies.title
from movies
where id in (
    select movie_id
    from stars
    where person_id in (
        select id
        from people
        where name = "Chadwick Boseman"
    )
)
order by (
    select rating
    from ratings
    where movie_id = movies.id
) desc
limit 5;
