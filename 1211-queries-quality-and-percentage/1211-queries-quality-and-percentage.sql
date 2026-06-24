with q as(
select
    query_name,
    rating / position as rp,
    case when rating < 3 then 1 else 0 end as rating
from queries)

select
    query_name,
    round(avg(rp), 2) as quality,
    round(avg(rating) * 100, 2) as poor_query_percentage
from q
group by query_name