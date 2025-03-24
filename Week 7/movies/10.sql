select name from people where id in (select distinct person_id from directors where movie_id in (select movie_id from ratings where rating >= 9.0));
