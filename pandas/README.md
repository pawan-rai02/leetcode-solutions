# 🐼 Pandas (Python Data Manipulation)

## What Is It?

**Pandas** is a Python library for data manipulation and analysis. It provides two primary data structures:
- **Series** — 1D labeled array (like a column in Excel)
- **DataFrame** — 2D labeled table (like a full spreadsheet or SQL table)

LeetCode Pandas problems mirror SQL problems but solved in Python using Pandas method chaining and transformations.

---

## When to Use It

- LeetCode problems tagged "Pandas" or "DataFrame"
- Data engineering / data science roles where Python is preferred over SQL
- Filtering, sorting, grouping, merging, transforming tabular data in Python

---

## Core Data Structures

```python
import pandas as pd

# Creating a DataFrame
df = pd.DataFrame({
    'name': ['Alice', 'Bob'],
    'age': [25, 30],
    'weight': [55, 80]
})

# Reading structure
df.shape          # (rows, cols)
df.dtypes         # column types
df.columns        # column names
df.head(5)        # first 5 rows
df.info()         # summary
```

---

## Essential Operations

### Filtering Rows (WHERE equivalent)
```python
# Single condition
df[df['weight'] > 100]

# Multiple conditions (use & | ~ instead of and/or/not)
df[(df['weight'] > 100) & (df['age'] < 30)]

# Filter with isin (IN equivalent)
df[df['status'].isin(['approved', 'pending'])]

# Filter with str methods
df[df['name'].str.startswith('A')]

# isna / notna
df[df['col'].isna()]
df[df['col'].notna()]
```

**Used in:** 2891 Method Chaining (`df[df['weight'] > 100]`)

---

### Selecting Columns (SELECT equivalent)
```python
df['column']           # Series
df[['col1', 'col2']]   # DataFrame with subset of columns

# Drop columns
df.drop(columns=['col1', 'col2'])
```

**Used in:** 2891 Method Chaining (`return animals[['name']]`)

---

### Sorting (ORDER BY equivalent)
```python
df.sort_values(by='weight', ascending=False)                   # DESC
df.sort_values(by=['col1', 'col2'], ascending=[True, False])   # multiple columns
```

**Used in:** 2891 Method Chaining

---

### Renaming Columns (AS equivalent)
```python
df.rename(columns={'old_name': 'new_name'})
```

---

### Aggregation (GROUP BY + aggregate equivalent)
```python
# groupby + agg
df.groupby('department')['salary'].mean()

# Multiple aggregations
df.groupby('country').agg(
    trans_count=('id', 'count'),
    total_amount=('amount', 'sum')
).reset_index()

# Conditional count (CASE WHEN equivalent)
df['is_approved'] = (df['state'] == 'approved').astype(int)
df.groupby('country')['is_approved'].sum()
```

---

### Merging DataFrames (JOIN equivalent)
```python
# INNER JOIN
pd.merge(df1, df2, on='key')
pd.merge(df1, df2, on='key', how='inner')

# LEFT JOIN
pd.merge(df1, df2, on='key', how='left')

# Different column names
pd.merge(df1, df2, left_on='user_id', right_on='id')
```

---

### Apply & Lambda (Custom transformations)
```python
df['new_col'] = df['col'].apply(lambda x: x * 2)

# More complex
df['category'] = df['score'].apply(lambda x: 'High' if x > 90 else 'Low')
```

---

### String Operations
```python
df['name'].str.upper()
df['name'].str.lower()
df['name'].str.contains('pattern')
df['name'].str.startswith('A')
df['name'].str.replace('old', 'new')
df['date'].str[:7]   # '2021-04' (like DATE_FORMAT)
```

---

### Date Operations
```python
df['date'] = pd.to_datetime(df['date'])
df['year']  = df['date'].dt.year
df['month'] = df['date'].dt.month
df['date'].dt.strftime('%Y-%m')   # format like SQL DATE_FORMAT
```

---

### Window Functions equivalent
```python
# ROW_NUMBER equivalent
df['rn'] = df.groupby('user_id')['order_date'].rank(method='first')

# Cumulative sum
df['cumsum'] = df.groupby('user_id')['amount'].cumsum()

# LAG / LEAD
df['prev'] = df.groupby('user_id')['value'].shift(1)   # LAG
df['next'] = df.groupby('user_id')['value'].shift(-1)  # LEAD
```

---

## Method Chaining (The Pandas Way)

Instead of creating intermediate variables, chain methods:

```python
# Without chaining (verbose)
df1 = df[df['weight'] > 100]
df2 = df1.sort_values('weight', ascending=False)
return df2[['name']]

# With chaining (clean)
return (
    df
    .pipe(lambda x: x[x['weight'] > 100])
    .sort_values('weight', ascending=False)
    [['name']]
)
```

Or even simpler inline:
```python
animals = animals[animals['weight'] > 100]
animals = animals.sort_values(by='weight', ascending=False)
return animals[['name']]
```

**Used in:** 2891 Method Chaining

---

## SQL → Pandas Cheatsheet

| SQL | Pandas |
|---|---|
| `SELECT col1, col2` | `df[['col1', 'col2']]` |
| `WHERE condition` | `df[df['col'] > val]` |
| `ORDER BY col DESC` | `df.sort_values('col', ascending=False)` |
| `GROUP BY col` | `df.groupby('col')` |
| `COUNT(*)` | `.count()` or `len(df)` |
| `SUM(col)` | `.sum()` |
| `AVG(col)` | `.mean()` |
| `COUNT(DISTINCT col)` | `.nunique()` |
| `INNER JOIN` | `pd.merge(df1, df2, on='key')` |
| `LEFT JOIN` | `pd.merge(df1, df2, on='key', how='left')` |
| `LIMIT n` | `df.head(n)` |
| `ROUND(val, 2)` | `round(val, 2)` |
| `AS alias` | `.rename(columns={'old': 'new'})` |
| `IN (...)` | `df['col'].isin([...])` |
| `IS NULL` | `df['col'].isna()` |
| `CASE WHEN` | `.apply(lambda x: ...)` or `np.where()` |

---

## Performance Tips

| Tip | Why |
|---|---|
| Use vectorized operations | Much faster than `.apply()` with loops |
| Filter early | Reduce DataFrame size before operations |
| Use `.query()` for readability | `df.query('age > 20 & salary < 5000')` |
| Avoid `iterrows()` | Extremely slow, never use in production |
| Use `inplace=False` (default) and reassign | Safer and clearer than `inplace=True` |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Using `and/or` instead of `&/|` | Python `and/or` don't work element-wise |
| Forgetting parentheses in multiple conditions | `(cond1) & (cond2)` — brackets required |
| Modifying copy vs. original | Always reassign: `df = df[...]` |
| Using `apply` for simple math | Use vectorized: `df['col'] * 2` not `df['col'].apply(lambda x: x*2)` |
| Not resetting index after groupby | Add `.reset_index()` after `groupby().agg()` |
| Forgetting `pd.to_datetime()` for date ops | Convert strings to datetime before using `.dt` |

---

## Problems in This Folder

| # | Problem | Key Operations |
|---|---|---|
| 2891 | Method Chaining | Filter by weight > 100, sort descending, select column |

---

## Interview Tips

- Know the **SQL ↔ Pandas equivalents** — interviewers often ask "how would you do this in Python?"
- **Method chaining** is idiomatic Pandas — it shows you write clean code
- `groupby` + `agg` is the most powerful Pandas pattern — master it
- Know `pd.merge` with all `how` options (inner, left, right, outer)
- Practice: top-n per group, pivot tables (`df.pivot_table`), `melt` / `stack` / `unstack`
- Pandas interview questions are common in data engineering and data science interviews
- Always know both the SQL and Pandas approach — shows versatility
