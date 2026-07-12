# 🗄️ Memoization

> **Subtopic of:** Dynamic Programming  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Memoization** is the technique of **caching the result of a recursive function** so that if the same inputs are seen again, the cached result is returned instantly instead of recomputing.

It's **top-down Dynamic Programming**: you write the natural recursive solution, then add a cache.

```
Without memo:          With memo:
fib(5)                 fib(5)
├── fib(4)             ├── fib(4)  ← computed once, cached
│   ├── fib(3)         │   ├── fib(3) ← cached
│   │   ├── fib(2)     │   └── fib(2) ← cached
│   │   └── fib(1)     └── fib(3)  ← returned from cache ✓
│   └── fib(2)
└── fib(3)
    ├── fib(2)         No repeated work!
    └── fib(1)
Exponential repeats!
```

---

## When to Use Memoization

- Recursive function called with **same arguments multiple times**
- Problem has **overlapping subproblems**
- You can express the answer as `f(state)` where state is a small set of parameters
- The brute-force recursion is too slow (exponential)
- You want to keep recursive code structure but need speed

---

## The Memoization Recipe

### Step 1: Write the pure recursive solution
```cpp
int solve(int i, int j) {
    if (base_case) return base_val;
    return max(solve(i+1, j), solve(i, j+1)) + cost[i][j];
}
```

### Step 2: Identify the state
What parameters uniquely define a subproblem?
- `solve(i)` → 1D state
- `solve(i, j)` → 2D state
- `solve(i, j, k)` → 3D state

### Step 3: Add a cache
```cpp
vector<vector<int>> dp(m, vector<int>(n, -1));  // -1 = uncomputed

int solve(int i, int j) {
    if (base_case) return base_val;
    if (dp[i][j] != -1) return dp[i][j];       // cache hit

    int result = max(solve(i+1, j), solve(i, j+1)) + cost[i][j];
    return dp[i][j] = result;                   // cache and return
}
```

### Step 4: Initialize and call
```cpp
dp.assign(m, vector<int>(n, -1));
return solve(0, 0);
```

---

## Choosing the Cache Type

| State Dimensions | Cache Type | Example |
|---|---|---|
| 1D (one int) | `vector<int> dp(n, -1)` | Fibonacci |
| 2D (two ints) | `vector<vector<int>> dp(m, vector<int>(n, -1))` | Grid paths |
| 3D (three ints) | `vector<vector<vector<int>>> dp(...)` | Safe walk |
| String / complex key | `unordered_map<string, int>` or `map<>` | Word break |

**Important:** The cache key must capture **everything** that affects the output. If the same `(i, j)` can produce different outputs depending on some other variable, that variable must also be part of the state.

---

## Memoization vs Tabulation

| | Memoization (Top-Down) | Tabulation (Bottom-Up) |
|---|---|---|
| Direction | Start from answer, recurse down | Start from base cases, build up |
| Code style | Recursive | Iterative |
| State computed | Only needed states | All states |
| Overhead | Function call overhead | No recursion overhead |
| Easier to write | ✅ Usually yes | More thinking about order |

**Rule of thumb:** Start with memoization. If too slow or stack overflow, convert to tabulation.

---

## Common Patterns

### 1D Memoization — Linear DP
```cpp
vector<int> dp(n, -1);

int solve(int i) {
    if (i >= n) return 0;
    if (dp[i] != -1) return dp[i];
    return dp[i] = min(solve(i+1), solve(i+2)) + cost[i];
}
```

---

### 2D Memoization — Grid / Matrix
```cpp
vector<vector<int>> dp(m, vector<int>(n, -1));

int dfs(int i, int j) {
    if (i >= m || j >= n) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    // Only go to cells with strictly larger values
    int best = 0;
    for (auto [di, dj] : dirs)
        if (valid(i+di, j+dj) && mat[i+di][j+dj] > mat[i][j])
            best = max(best, dfs(i+di, j+dj));

    return dp[i][j] = 1 + best;
}
```
**Used in:** 0329 Longest Increasing Path in Matrix

---

### 3D Memoization — Extra State Dimension
```cpp
// State: (row, col, remaining_health)
vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(H+1, -1)));

bool dfs(int i, int j, int health) {
    if (/* out of bounds or dead */) return false;
    if (/* reached destination */) return true;
    if (dp[i][j][health] != -1) return dp[i][j][health];

    vis[i][j] = true;
    bool ans = dfs(i+1,j,health) || dfs(i-1,j,health) || ...;
    vis[i][j] = false;   // backtrack

    return dp[i][j][health] = ans;
}
```
**Used in:** 3286 Safe Walk Through Grid

---

### Memoization on Subsequences — 1D with next-pointer
```cpp
vector<int> dp(n, -1), nxt(n, -1);

int solve(int i) {
    if (dp[i] != -1) return dp[i];
    dp[i] = 1;
    for (int j = i+1; j < n; j++) {
        if (compatible(i, j)) {
            int cur = 1 + solve(j);
            if (cur > dp[i]) {
                dp[i] = cur;
                nxt[i] = j;     // track path for reconstruction
            }
        }
    }
    return dp[i];
}
```
**Used in:** 2901 Longest Unequal Adjacent Groups Subsequence II

---

## Cache Invalidation Pitfall

**Always initialize the cache to a value that can't be a valid answer.**

- Count problems → use `-1` (counts are ≥ 0)
- Boolean problems → use `-1` (booleans are 0 or 1)
- Max problems → use `INT_MIN` or `-1`

If `0` is a valid answer, don't use `0` as the "uncomputed" sentinel!

---

## Complexity

| | Without Memo | With Memo |
|---|---|---|
| Fibonacci | O(2^n) | O(n) |
| Grid paths m×n | O(2^(m+n)) | O(m×n) |
| Time (general) | Exponential | O(states × work per state) |
| Space | O(depth) | O(states) |

---

## Problems in This Folder

| # | Problem | State | Cache Type | Key Detail |
|---|---|---|---|---|
| 0329 | Longest Increasing Path in Matrix | (row, col) | `dp[m][n]` | DFS in 4 directions; only move to larger value; cache length |
| 2901 | Longest Unequal Adj Groups Subseq II | index `i` | `dp[n]` + `nxt[n]` | Track next-index for path reconstruction; valid = diff groups + Hamming distance 1 |
| 3286 | Safe Walk Through Grid | (row, col, health) | `dp[m][n][H+1]` | 3D state captures remaining health; `vis[][]` for backtracking |
