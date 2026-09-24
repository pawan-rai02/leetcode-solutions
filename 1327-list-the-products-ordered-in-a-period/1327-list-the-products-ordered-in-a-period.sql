# Write your MySQL query statement below
with grouped as(
    select
        product_id,
        DATE_FORMAT(order_date, '%Y-%m') as month,
        sum(unit) as units
    from
        orders
    group by
        product_id, DATE_FORMAT(order_date, '%Y-%m')
)

select
    p.product_name,
    g.units as unit
from
    grouped as g
join    
    products as p
on 
    p.product_id = g.product_id
where 
    units >= 100 and month = '2020-02'