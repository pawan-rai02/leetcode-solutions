# ↩️ Backtracking

> **Subtopic of:** Dynamic Programming, DFS  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Backtracking** is a refined brute-force technique where you explore all possible solutions, but **undo choices** (backtrack) as soon as you know they can't lead to a valid solution.

It's essentially DFS with an **undo step**.

```
Decision tree:
      Start
     /     \
  Choice A  Choice B
   /   \      /   \
  A1    A2   B1    B2
   ✗    ✓    ✗     ✓

When A1 fails → backtrack → try A2
When B1 fails → backtrack → try B2
```

---

## When to Use Backtracking

| Problem Type | Example |
|---|---|
| Generate all permutations / combinations / subsets | Permutations, Power Set |
| Solve constraint puzzles | Sudoku, N-Queens |
| Find all valid paths in a grid | Maze solving, word search |
| Find if a valid path exists | Safe walk, path with constraints |
| Word search in a grid | Word Search II |

---

## Core Template

```cpp
void backtrack(state, current_choice) {
    // Base case: valid solution found
    if (goal_reached(state)) {
        record_answer();
        return;
    }

    for (choice : possible_choices) {
        if (is_valid(choice, state)) {

            make_choice(choice, state);      // ← CHOOSE
            backtrack(state, next_choice);   // ← EXPLORE
            undo_choice(choice, state);      // ← UN-CHOOSE (backtrack)
        }
    }
}
```

**The three steps: Choose → Explore → Un-choose**

---

## Grid Backtracking Template

The most common pattern: explore a 2D grid, mark visited, explore neighbors, unmark.

```cpp
vector<vector<bool>> vis(m, vector<bool>(n, false));
int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

bool dfs(int i, int j, /* other state */) {
    // 1. Check bounds and stopping conditions
    if (out_of_bounds(i, j)) return false;
    if (vis[i][j]) return false;       // already in current path

    // 2. Update state
    some_state -= grid[i][j];
    if (state_invalid) { /* undo and */ return false; }
    if (reached_goal)  return true;

    // 3. Mark visited
    vis[i][j] = true;

    // 4. Explore all directions
    bool ans = false;
    for (auto [di, dj] : dirs)
        ans = ans || dfs(i+di, j+dj, state);

    // 5. UNMARK — the backtrack step
    vis[i][j] = false;

    return ans;
}
```
**Used in:** 3286 Safe Walk Through Grid

---

## Why the `vis` Array Instead of Modifying the Grid?

Two approaches:
1. **Modify the grid** in-place (mark as visited), restore after returning
2. **Separate `vis` array** — mark before recursing, unmark after

```cpp
// Approach 1: modify grid
char temp = grid[i][j];
grid[i][j] = '#';       // mark
dfs(i+1, j);
grid[i][j] = temp;      // restore

// Approach 2: separate vis array (cleaner)
vis[i][j] = true;
dfs(i+1, j);
vis[i][j] = false;      // unmark
```

**Use approach 2 when:** the grid contains important values you don't want to overwrite (e.g., health costs).

---

## Backtracking + Memoization

When the same state is visited multiple times in the backtracking tree, memoize it.

```cpp
vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(H+1, -1)));
vector<vector<bool>> vis(m, vector<bool>(n, false));

bool dfs(int i, int j, int health) {
    if (/* invalid */) return false;

    if (dp[i][j][health] != -1)     // state already computed
        return dp[i][j][health];

    vis[i][j] = true;               // mark for current path

    bool ans = dfs(i+1,j,h) || dfs(i-1,j,h) || dfs(i,j+1,h) || dfs(i,j-1,h);

    vis[i][j] = false;              // unmark (backtrack)

    return dp[i][j][health] = ans;  // cache result
}
```

**Key insight:** The `vis` array prevents cycles **within a single path**. The `dp` cache prevents **redundant exploration of the same (i, j, health) state** across different paths.

**Used in:** 3286 Safe Walk Through Grid

---

## Pruning

Pruning is cutting off branches early to skip impossible solutions:

```cpp
if (remaining < 0) return false;   // prune: can't recover
if (current_length >= best_found) continue;  // prune: won't improve
```

Good pruning transforms exponential backtracking into practical solutions.

---

## Classic Backtracking Problems (Practice These)

| Problem | Key Insight |
|---|---|
| Permutations (LC 46) | Swap elements, recurse, swap back |
| Combinations (LC 77) | Choose or skip each element |
| N-Queens (LC 51) | Check row/col/diagonal before placing |
| Sudoku Solver (LC 37) | Try digits 1-9; backtrack if conflict |
| Word Search (LC 79) | DFS on grid; mark/unmark visited |
| Subsets (LC 78) | Include or exclude each element |

---

## Time Complexity

Backtracking is typically **exponential** in the worst case, but pruning makes it practical:

| Problem | Worst Case |
|---|---|
| Permutations of n | O(n!) |
| Subsets of n | O(2^n) |
| N-Queens | O(n!) |
| Grid DFS with backtrack | O(4^(m×n)) worst, much less with pruning |

With memoization, redundant states are eliminated, often reducing to **O(states × branching)**.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Forgetting to unmark/undo | Always pair `mark` with `unmark` after recursion |
| Marking before checking validity | Check bounds/validity first; then mark |
| Missing the backtrack step entirely | This turns backtracking into plain DFS — you'll revisit nodes incorrectly |
| Not pruning at all | Add early-exit conditions; otherwise TLE |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 3286 | Safe Walk Through Grid | Grid DFS + Backtrack + Memo | `vis[i][j]` tracks current path (unmark after return); `dp[i][j][health]` caches computed states |
