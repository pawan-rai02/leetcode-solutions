# 🔍 DFS — Depth-First Search

> **Subtopic of:** Trees, Graphs, Dynamic Programming  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Depth-First Search (DFS)** explores as far as possible down one branch before backtracking. It uses the **call stack** (recursion) or an **explicit stack**.

```
Tree:          DFS preorder visits:
    1          1 → 2 → 4 → 5 → 3 → 6
   / \
  2   3        DFS postorder visits:
 / \   \       4 → 5 → 2 → 6 → 3 → 1
4   5   6
```

---

## When to Use DFS

| Situation | Why DFS |
|---|---|
| Tree height / depth | DFS naturally computes depth |
| Subtree properties | DFS returns values from children to parent |
| Path between nodes | DFS explores complete paths |
| Connected components | DFS marks all reachable nodes |
| Cycle detection | DFS tracks "in progress" nodes |
| Memoization on graphs | DFS + cache avoids recomputation |

---

## Three Flavors

### Preorder (Root → Left → Right)
Process current node **before** children.
```cpp
void dfs(TreeNode* root) {
    if (!root) return;
    process(root);          // ← HERE
    dfs(root->left);
    dfs(root->right);
}
```
**Use:** Print tree top-down, copy tree, serialize.

---

### Inorder (Left → Root → Right)
Process current node **between** children.
```cpp
void dfs(TreeNode* root) {
    if (!root) return;
    dfs(root->left);
    process(root);          // ← HERE
    dfs(root->right);
}
```
**Use:** BST gives **sorted order** via inorder. Validate BST.

---

### Postorder (Left → Right → Root)
Process current node **after** children.
```cpp
int dfs(TreeNode* root) {
    if (!root) return 0;
    int left  = dfs(root->left);   // collect from children first
    int right = dfs(root->right);
    return process(left, right, root); // ← HERE
}
```
**Use:** Height, diameter, path sum, LCA — anything needing child info first.

---

## Core Templates

### Template A — Return Value Up (Postorder)
```cpp
int dfs(TreeNode* root) {
    if (!root) return 0;                    // base case

    int left  = dfs(root->left);
    int right = dfs(root->right);

    return 1 + max(left, right);            // height
}
```
**Used in:** Max Depth (0104), Count Nodes (0222)

---

### Template B — Return Value + Update Global
```cpp
int globalResult = 0;

int dfs(TreeNode* root) {
    if (!root) return 0;

    int left  = dfs(root->left);
    int right = dfs(root->right);

    globalResult = max(globalResult, left + right);  // update global

    return 1 + max(left, right);                      // return height
}
```
**Used in:** Diameter (0543), Max Path Sum (0124)

---

### Template C — DFS on Graph (with visited array)
```cpp
vector<bool> vis(n, false);

void dfs(int u, vector<vector<int>>& adj) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v])
            dfs(v, adj);
    }
}
```
**Used in:** Min Score Path (2492), Complete Components (2685)

---

### Template D — DFS + Memoization
```cpp
vector<vector<int>> dp(m, vector<int>(n, -1));

int dfs(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];   // return cached

    // explore neighbors
    int best = 0;
    for (auto [di, dj] : dirs) {
        int ni = i + di, nj = j + dj;
        if (valid(ni, nj) && condition(ni, nj, i, j))
            best = max(best, dfs(ni, nj));
    }

    return dp[i][j] = 1 + best;            // cache and return
}
```
**Used in:** Longest Increasing Path in Matrix (0329)

---

### Template E — DFS + Backtracking
```cpp
vector<vector<bool>> vis(m, vector<bool>(n, false));

bool dfs(int i, int j, int state) {
    if (/* base case */) return true;
    if (vis[i][j]) return false;

    vis[i][j] = true;             // mark

    bool ans = dfs(i+1, j, state) || dfs(i, j+1, state) || ...;

    vis[i][j] = false;            // ← unmark (backtrack)

    return ans;
}
```
**Used in:** Safe Walk Through Grid (3286)

---

## DFS on Trees — The Return Value Trick

The most important concept: **what you return vs. what you track globally are different things.**

| Problem | Returned to Parent | Tracked Globally |
|---|---|---|
| Max Depth | height | — |
| Diameter | height | max(left + right) |
| Max Path Sum | max single-arm | max(left + right + val) |
| Balanced Check | height (or -1) | — |
| LCA | found node or nullptr | — |

---

## DFS Complexity

| Case | Time | Space |
|---|---|---|
| Tree DFS | O(n) | O(h) — recursion depth |
| Graph DFS | O(V + E) | O(V) |
| DFS + Memo | O(states) | O(states) |

Where h = height (O(log n) balanced, O(n) skewed).

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Missing null check | First line: `if (!root) return 0;` |
| Wrong return value | Decide clearly: does parent need height? count? bool? |
| Not marking visited in graphs | Always `vis[u] = true` before recursing |
| Forgetting to unmark in backtracking | `vis[u] = false` after recursion returns |
| Stack overflow on deep trees | Use iterative DFS (explicit stack) for production code |

---

## Problems in This Folder

| # | Problem | DFS Type | Key Insight |
|---|---|---|---|
| 0100 | Same Tree | Preorder | Recurse both trees simultaneously; all three conditions must match |
| 0104 | Max Depth Binary Tree | Postorder (return) | `1 + max(left, right)` |
| 0110 | Balanced Binary Tree | Postorder + sentinel | Return `-1` to propagate imbalance upward |
| 0124 | Max Path Sum | Postorder + global | Return best single-arm; update global with `l + r + val` |
| 0236 | Lowest Common Ancestor | Postorder | Both subtrees non-null → current is LCA |
| 0329 | Longest Increasing Path | DFS + Memo (2D) | Cache path length from each cell |
| 0543 | Diameter | Postorder + global | Return height; update `max_dia = l + r` |
| 0653 | Two Sum IV (BST) | Preorder + hashset | DFS tree; check complement in set |
| 2492 | Min Score Path | Graph DFS | DFS from node 1; track min edge weight in component |
| 2685 | Complete Components | Graph DFS | Count nodes+edges per component; check completeness |
| 3286 | Safe Walk Through Grid | DFS + Memo + Backtrack | 3D state (i, j, health); vis for backtrack |
