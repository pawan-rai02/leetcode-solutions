# Write your MySQL query statement below
with feb_ratings as (
    select
        movie_id,
        avg(rating) as avg_rating
    from
        movierating
    where 
        year(created_at) = 2020
    and
        month(created_at) = 2
    group by movie_id
)
, moviename as(
    select
        f.*,
        m.title as name,
        rank() over(order by f.avg_rating desc, m.title) as rnk
    from
        feb_ratings as f
    left join
        movies as m
    on m.movie_id = f.movie_id
)


, users_rated as (
    select
        user_id,
        count(rating) as ct
    from
        movierating
    group by 
        user_id
)

, ranks as (
    select
        r.*,
        u.name,
        row_number() over(order by ct desc, u.name) as rnk
    from
        users_rated as r
    left join
        users as u
    on u.user_id = r.user_id
)

select
    name as results
from
    ranks
where rnk = 1

union all

select
    name as results
from
    moviename
where rnk = 1