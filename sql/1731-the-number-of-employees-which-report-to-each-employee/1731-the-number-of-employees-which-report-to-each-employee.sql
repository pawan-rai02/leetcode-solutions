with reports as (
    select
        employee_id,
        reports_to,
        age
    from
        employees
    where reports_to is not null
)

, managers as(
    select
        m.employee_id as m_id,
        m.name,
        r.employee_id,
        r.age
    from
        employees as m
    inner join
        reports as r
    on
        m.employee_id = r.reports_to
)

select
    m_id as employee_id,
    name,
    count(employee_id) as reports_count,
    round(avg(age), 0) as average_age
from
    managers
group by
    m_id, name
order by m_id