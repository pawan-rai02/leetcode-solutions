with first_orders as (
    select
        customer_id,
        order_date,
        customer_pref_delivery_date,
        row_number() over(partition by customer_id order by order_date) as rowss
    from
        delivery
)

, immediate as (
    select
        customer_id,
        order_date,
        customer_pref_delivery_date,
        case when customer_pref_delivery_date = order_date then 1 else 0 end as type
    from
        first_orders
    where rowss = 1
)


select
    round(avg(type) * 100, 2) as immediate_percentage
from
    immediate