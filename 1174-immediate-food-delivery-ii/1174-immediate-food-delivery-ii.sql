with del as (
    select
        delivery_id,
        customer_id,
        order_date,
        customer_pref_delivery_date,
        row_number() over(PARTITION BY customer_id order by order_date) as rnk
    from 
        delivery
)

select
    round(avg(case when order_date = customer_pref_delivery_date then 1 else 0 end) * 100, 2) as immediate_percentage 
from
    del
where rnk = 1