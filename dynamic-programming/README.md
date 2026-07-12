# 🧠 Dynamic Programming (DP)

## What Is It?

**Dynamic Programming** is an algorithmic technique for solving problems by breaking them into **overlapping subproblems**, solving each subproblem **once**, and storing the result (**memoization** or **tabulation**) to avoid redundant computation.

> "Don't solve the same subproblem twice."

DP is used when brute-force recursion would revisit the same states over and over.

---

## When to Use It

Key signals:
- The problem asks for **optimal value** (min/max/count/true-false)
- It has **overlapping subproblems** — same inputs lead to same outputs
- It has **optimal substructure** — optimal solution of the problem contains optimal solutions to subproblems
- Brute-force recursion leads to exponential time (2^n, n!)
- Keywords: **"minimum cost"**, **"maximum profit"**, **"number of ways"**, **"longest"**, **"can you reach"**

---

## Core Intuition

### Think Recursively First
Every DP solution starts as a recursive solution. The key insight is:

```
solve(state) = f(solve(smaller_state_1), solve(smaller_state_2), ...)
```

**Then add memoization** to cache the result of each state.

### Two Approaches

#### 1. Top-Down (Memoization)
Start from the full problem and recurse down. Cache results.

```cpp
unordered_map<int, int> memo;

int solve(int state) {
    if (base_case) return base_value;
    if (memo.count(state)) return memo[state];  // cached
    
    int result = f(solve(state - 1), solve(state - 2));  // recurse
    return memo[state] = result;                          // cache & return
}
```

**Pros:** Intuitive, only computes needed states  
**Cons:** Recursion stack overhead

#### 2. Bottom-Up (Tabulation)
Start from base cases and build up to the answer.

```cpp
vector<int> dp(n + 1, 0);
dp[0] = base;
dp[1] = base;

for (int i = 2; i <= n; i++) {
    dp[i] = dp[i-1] + dp[i-2];  // fill in order
}

return dp[n];
```

**Pros:** No recursion, cache-friendly, often faster  
**Cons:** Need to figure out the right order to fill

---

## The 5-Step Framework to Solve Any DP Problem

### Step 1: Define the State
What information completely defines a subproblem?

- `dp[i]` — answer for first i elements
- `dp[i][j]` — answer considering rows 0..i and cols 0..j
- `dp[i][j][k]` — answer with index i, j, and remaining budget k

> The state captures everything you need to answer the subproblem.

### Step 2: Define the Recurrence (Transition)
How does `dp[i]` relate to smaller states?

```
dp[i] = max(dp[i-1], dp[i-2] + val[i])   // include or exclude
dp[i][j] = dp[i-1][j-1] + 1              // match characters
dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j]  // path cost
```

### Step 3: Identify Base Cases
What are the smallest valid states?

```
dp[0] = 0      // empty input
dp[1] = val[0] // single element
```

### Step 4: Decide Iteration Order
Bottom-up: figure out which dp values you need to compute `dp[i]`.

### Step 5: Extract Answer
Usually `dp[n]`, `dp[m][n]`, or `max(dp[i])`.

---

## Common DP Patterns

### Pattern 1 — 1D DP (Linear)
State: `dp[i]` = answer for the first i elements.

```cpp
// Fibonacci-style
dp[i] = dp[i-1] + dp[i-2];

// Include/Exclude
dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
```

**Problems:** House Robber, Climbing Stairs, Fibonacci

---

### Pattern 2 — 2D DP (Grid/String)
State: `dp[i][j]` = answer considering row i and column j (or string prefix i and j).

```cpp
// Longest Common Subsequence
dp[i][j] = (s1[i] == s2[j]) ? dp[i-1][j-1] + 1 
                              : max(dp[i-1][j], dp[i][j-1]);

// Grid path
dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
```

**Problems:** LCS, Edit Distance, Unique Paths, Min Path Sum

---

### Pattern 3 — DFS + Memoization (On Graphs/Matrices)
When the state space is a graph. Recursion is natural; add a memo table.

```cpp
vector<vector<int>> dp(m, vector<int>(n, -1));

int dfs(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    
    int best = 0;
    for (auto [di, dj] : directions) {
        int ni = i + di, nj = j + dj;
        if (valid(ni, nj) && condition(ni, nj, i, j))
            best = max(best, dfs(ni, nj));
    }
    return dp[i][j] = 1 + best;
}
```

**Used in:** 0329 Longest Increasing Path in a Matrix

---

### Pattern 4 — DP with State Compression (Backtracking + Memo)
When path history matters, track visited states explicitly.

```cpp
vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxHealth+1, -1)));
vector<vector<bool>> vis(m, vector<bool>(n, false));

bool dfs(int i, int j, int health) {
    if (dp[i][j][health] != -1) return dp[i][j][health];
    vis[i][j] = true;
    bool ans = dfs(i+1, j, health) || dfs(i, j+1, health) || ...;
    vis[i][j] = false;  // backtrack
    return dp[i][j][health] = ans;
}
```

**Used in:** 3286 Safe Walk Through a Grid

---

## How to Identify DP Problems

Ask these questions in order:

```
1. Does the problem ask for min/max/count/feasibility?
2. Is there recursion with repeated subproblems?
3. Does each subproblem depend only on smaller subproblems?
   → YES to all: DP!
4. How many dimensions does the state need?
   → 1D: single index
   → 2D: two indices (grid, two strings, index + remaining budget)
   → 3D+: add more dimensions as needed
```

---

## How to Build Intuition

1. **Start with brute-force recursion** — write the naive recursive solution first
2. **Draw the recursion tree** — notice repeated subproblems visually
3. **Identify what changes** between recursive calls — that's your state
4. **Memoize** — add a cache, suddenly it's fast
5. **Convert to bottom-up** — reverse the recursion order
6. **Optimize space** — often only need the last 1-2 rows (1D optimization)

---

## DP Complexity

| Complexity | Depends On |
|---|---|
| Time | `O(states × transitions_per_state)` |
| Space | `O(states)` — can sometimes be reduced |

For 1D DP over n: **O(n)** time, **O(n)** space (often reducible to O(1))  
For 2D DP over m×n: **O(m×n)** time, **O(m×n)** space (often reducible to O(n))

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Thinking recursion = DP | Recursion is only DP if you memoize repeated subproblems |
| Wrong base case | Check n=0, n=1 manually |
| Wrong iteration order | Make sure `dp[i]` is computed before `dp[i+1]` needs it |
| Off-by-one errors | Carefully index: is `dp[i]` for "first i elements" or "element at index i"? |
| Forgetting to check bounds | Always guard array accesses in DFS-based DP |

---

## Problems in This Folder

| # | Problem | DP Type | Key Idea |
|---|---|---|---|
| 0329 | Longest Increasing Path in Matrix | DFS + Memo (2D) | From each cell, recurse into larger neighbors; cache path length |
| 2901 | Longest Unequal Adjacent Groups Subsequence II | 1D DP + path reconstruction | `dp[i]` = longest valid subsequence ending at `i`; track `nxt[i]` for path reconstruction; valid = same length + Hamming distance 1 |
| 3286 | Safe Walk Through Grid | DFS + Memo + Backtracking (3D) | State = (row, col, remaining_health); vis array for backtracking |

---

## Interview Tips

- **Always mention the state definition clearly** — interviewers love this
- Start with the **recursive solution**, then optimize with memoization
- Mention **space optimization** as a bonus (e.g., rolling array)
- Know the classics cold: Fibonacci, House Robber, Longest Common Subsequence, 0/1 Knapsack, Edit Distance, Coin Change
- DP on trees (rerooting), DP on intervals, DP with bitmask — advanced but asked at FAANG
- If you're stuck between Greedy and DP: write a greedy, test it on a counterexample. If counterexample exists → DP.
