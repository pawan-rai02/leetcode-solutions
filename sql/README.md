# 🗃️ SQL (Structured Query Language)

## What Is It?

**SQL** is the standard language for querying and manipulating relational databases. LeetCode SQL problems test your ability to extract, filter, aggregate, and join data from tables to answer business questions.

These are not algorithmic problems — they test **database query design skills**.

---

## When You'll Use SQL

- Any data retrieval / reporting problem with tables
- Filtering, grouping, ranking, aggregating data
- Real-world: data engineering, backend, data science, analytics roles
- Common in interviews at companies with data-heavy roles (Meta, Google, Uber, etc.)

---

## SQL Execution Order (Critical!)

SQL queries execute in this order (NOT the order you write them):

```
FROM / JOIN        ← 1st: identify tables
WHERE              ← 2nd: filter rows
GROUP BY           ← 3rd: group remaining rows
HAVING             ← 4th: filter groups
SELECT             ← 5th: select columns (aliases defined here)
ORDER BY           ← 6th: sort results
LIMIT              ← 7th: limit output
```

**Why this matters:** You cannot use a column alias (defined in SELECT) inside WHERE or GROUP BY, because those run before SELECT.

---

## Core Building Blocks

### SELECT & FROM
```sql
SELECT column1, column2
FROM table_name;
```

### WHERE — Row-Level Filtering
```sql
SELECT *
FROM orders
WHERE status = 'approved' AND amount > 100;
```

### GROUP BY — Aggregation
```sql
SELECT country, COUNT(*) AS total, SUM(amount) AS revenue
FROM transactions
GROUP BY country;
```

### HAVING — Filter After Grouping
```sql
-- WHERE can't filter on aggregates, HAVING can
SELECT country, COUNT(*) AS cnt
FROM orders
GROUP BY country
HAVING COUNT(*) > 5;
```

### ORDER BY
```sql
SELECT contest_id, percentage
FROM results
ORDER BY percentage DESC, contest_id ASC;  -- multiple sort keys
```

### LIMIT
```sql
SELECT * FROM table LIMIT 10;
```

---

## Aggregate Functions

| Function | Meaning |
|---|---|
| `COUNT(*)` | Count all rows |
| `COUNT(col)` | Count non-NULL values |
| `COUNT(DISTINCT col)` | Count unique values |
| `SUM(col)` | Sum of values |
| `AVG(col)` | Average |
| `MAX(col)` | Maximum value |
| `MIN(col)` | Minimum value |
| `ROUND(val, n)` | Round to n decimal places |

---

## JOINs

```sql
-- INNER JOIN: only matching rows from both tables
SELECT a.col, b.col
FROM tableA a
INNER JOIN tableB b ON a.id = b.id;

-- LEFT JOIN: all rows from left, matched rows from right (NULL if no match)
SELECT a.col, b.col
FROM tableA a
LEFT JOIN tableB b ON a.id = b.id;

-- RIGHT JOIN: all rows from right
-- FULL OUTER JOIN: all rows from both (not supported in MySQL, use UNION)
```

---

## Subqueries

```sql
-- Scalar subquery (returns single value)
SELECT *, salary / (SELECT AVG(salary) FROM employees) AS ratio
FROM employees;

-- Subquery in WHERE
SELECT user_id
FROM users
WHERE user_id IN (SELECT user_id FROM premium_users);

-- Subquery in FROM (derived table)
SELECT * FROM (
    SELECT user_id, COUNT(*) AS cnt
    FROM orders
    GROUP BY user_id
) AS order_counts
WHERE cnt > 5;
```

---

## CTEs (Common Table Expressions)

CTEs make complex queries readable by naming intermediate results.

```sql
WITH cte_name AS (
    SELECT col1, col2
    FROM table
    WHERE condition
)
SELECT *
FROM cte_name
WHERE another_condition;
```

**Multiple CTEs:**
```sql
WITH cte1 AS (...),
     cte2 AS (SELECT * FROM cte1 WHERE ...)
SELECT * FROM cte2;
```

**Used in:** 1174 Immediate Food Delivery II, 1211 Queries Quality

---

## CASE WHEN — Conditional Logic

```sql
SELECT
    CASE
        WHEN salary > 10000 THEN 'High'
        WHEN salary > 5000  THEN 'Medium'
        ELSE 'Low'
    END AS salary_band
FROM employees;

-- In aggregates:
SELECT
    SUM(CASE WHEN state = 'approved' THEN 1 ELSE 0 END) AS approved_count,
    SUM(CASE WHEN state = 'approved' THEN amount ELSE 0 END) AS approved_total
FROM transactions;
```

**Used in:** 1193 Monthly Transactions, 1174 Immediate Food Delivery

---

## Window Functions

Window functions compute across a set of rows **without collapsing them** (unlike GROUP BY).

```sql
SELECT
    col,
    ROW_NUMBER() OVER (PARTITION BY group_col ORDER BY sort_col) AS rn,
    RANK()       OVER (PARTITION BY group_col ORDER BY sort_col) AS rnk,
    DENSE_RANK() OVER (PARTITION BY group_col ORDER BY sort_col) AS dense_rnk,
    LAG(col, 1)  OVER (ORDER BY sort_col) AS prev_val,
    LEAD(col, 1) OVER (ORDER BY sort_col) AS next_val,
    SUM(col)     OVER (PARTITION BY group_col) AS group_sum
FROM table;
```

| Function | Behavior |
|---|---|
| `ROW_NUMBER()` | Unique rank (no ties) |
| `RANK()` | Ties get same rank, next rank skips |
| `DENSE_RANK()` | Ties get same rank, next rank does NOT skip |
| `LAG(col, n)` | Value n rows before current row |
| `LEAD(col, n)` | Value n rows after current row |

**Used in:** 1174 Immediate Food Delivery II (ROW_NUMBER for first order per customer)

---

## DATE Functions (MySQL)

```sql
DATE_FORMAT(date_col, '%Y-%m')       -- "2021-04"
YEAR(date_col)                        -- 2021
MONTH(date_col)                       -- 4
DATEDIFF(date1, date2)               -- difference in days
DATE_ADD(date, INTERVAL 1 DAY)       -- add 1 day
```

**Used in:** 1193 Monthly Transactions (`DATE_FORMAT`)

---

## Common Problem Patterns

### Pattern 1 — Percentage / Ratio
```sql
-- Percentage of rows satisfying condition
SELECT
    ROUND(
        SUM(CASE WHEN condition THEN 1 ELSE 0 END) * 100.0 / COUNT(*),
        2
    ) AS percentage
FROM table;

-- Or using AVG (elegant trick!)
SELECT ROUND(AVG(CASE WHEN condition THEN 1 ELSE 0 END) * 100, 2) AS pct
FROM table;
```

**Used in:** 1174, 1633, 1211

---

### Pattern 2 — First/Last Record Per Group
```sql
-- Using ROW_NUMBER
WITH ranked AS (
    SELECT *, ROW_NUMBER() OVER (PARTITION BY user_id ORDER BY order_date) AS rn
    FROM orders
)
SELECT * FROM ranked WHERE rn = 1;

-- Or using subquery with MIN
SELECT * FROM orders
WHERE (user_id, order_date) IN (
    SELECT user_id, MIN(order_date) FROM orders GROUP BY user_id
);
```

**Used in:** 1174 Immediate Food Delivery (first order per customer)

---

### Pattern 3 — Count with Conditions (Pivot-style)
```sql
SELECT
    DATE_FORMAT(trans_date, '%Y-%m') AS month,
    country,
    COUNT(*) AS trans_count,
    SUM(CASE WHEN state = 'approved' THEN 1 ELSE 0 END) AS approved_count,
    SUM(amount) AS trans_total_amount,
    SUM(CASE WHEN state = 'approved' THEN amount ELSE 0 END) AS approved_total_amount
FROM Transactions
GROUP BY country, DATE_FORMAT(trans_date, '%Y-%m');
```

**Used in:** 1193 Monthly Transactions

---

### Pattern 4 — Count Distinct
```sql
SELECT teacher_id, COUNT(DISTINCT subject_id) AS cnt
FROM teacher
GROUP BY teacher_id;
```

**Used in:** 2356 Unique Subjects per Teacher

---

## Performance Tips

| Tip | Why |
|---|---|
| Filter early with WHERE | Reduces rows before GROUP BY |
| Use indexed columns in WHERE/JOIN | Faster lookups |
| Avoid `SELECT *` | Fetches unnecessary data |
| Use EXISTS instead of IN for large subqueries | EXISTS stops at first match |
| Use CTEs for readability | Easier to debug and optimize |

---

## Problems in This Folder

| # | Problem | Key Concept | Technique Used |
|---|---|---|---|
| 0196 | Delete Duplicate Emails | Self-JOIN DELETE | `DELETE p1 FROM Person p1 JOIN Person p2 ON same email AND p1.id > p2.id` |
| 0626 | Exchange Seats | Conditional swap | `CASE WHEN id % 2 = 1 AND id+1 <= MAX THEN id+1 WHEN even THEN id-1 ELSE id` |
| 1174 | Immediate Food Delivery II | First order per customer | CTE + ROW_NUMBER window function |
| 1193 | Monthly Transactions I | Conditional aggregation | DATE_FORMAT + GROUP BY + CASE WHEN |
| 1211 | Queries Quality and Percentage | Computed aggregation | CTE + AVG over derived column |
| 1321 | Restaurant Growth | Moving 7-day window | CTE + `SUM/AVG OVER (ROWS BETWEEN 6 PRECEDING AND CURRENT ROW)` |
| 1331 | (Moved to Greedy) | — | — |
| 1341 | Movie Rating | Multi-result UNION | CTE + RANK window fn + UNION ALL for user and movie results |
| 1484 | Group Sold Products by Date | String aggregation | `GROUP_CONCAT(DISTINCT product ORDER BY product)` |
| 1517 | Find Users with Valid E-mails | Pattern matching | `REGEXP '^[a-zA-Z][a-zA-Z0-9_.-]*@leetcode\.com$'` |
| 1527 | Patients with a Condition | String prefix matching | `LIKE 'DIAB1%' OR LIKE '% DIAB1%'` |
| 1633 | Percentage of Users Attended a Contest | Ratio with subquery | Scalar subquery in SELECT |
| 1667 | Fix Names in a Table | String manipulation | `CONCAT(UPPER(LEFT(name,1)), LOWER(SUBSTRING(name,2)))` |
| 1731 | Employees Reporting to Each Employee | Self-JOIN + aggregation | CTE + INNER JOIN employees to themselves on `reports_to` |
| 1789 | Primary Department for Each Employee | Conditional filter | `WHERE primary_flag = 'Y' OR employee_id IN (single-dept employees)` |
| 1907 | Count Salary Categories | CASE + LEFT JOIN skeleton | CTE for classification; LEFT JOIN to all-category skeleton to preserve zeros |
| 2356 | Unique Subjects per Teacher | Count distinct | COUNT(DISTINCT) + GROUP BY |

---

## Interview Tips

- **Always mention the execution order** — shows you understand the engine
- **Use CTEs** — they make your query readable and show good code style
- **Window functions** (ROW_NUMBER, LAG, LEAD, RANK) appear frequently — practice them
- Know when to use `WHERE` vs `HAVING` — common interview trick question
- **CASE WHEN inside aggregates** is extremely common for conditional counts
- Test your query mentally with small data before finalizing
- MySQL vs PostgreSQL differences: MySQL doesn't support `FULL OUTER JOIN`, PostgreSQL supports more window functions
- Practice: Nth Highest Salary, Rank Scores, Department Highest Salary, Consecutive Numbers
