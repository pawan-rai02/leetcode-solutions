# Write your MySQL query statement below
with managers as (
    select
        e.reports_to as mid,
        m.name,
        e.age
    from
        employees as e
    inner join
        employees as m
    on
        m.employee_id = e.reports_to
)

    select
        mid as employee_id,
        name,
        count(mid) as reports_count,
        round(avg(age), 0) as average_age
    from
        managers
    group by
        mid, name
    order by
        mid