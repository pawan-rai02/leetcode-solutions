# 🌊 BFS — Breadth-First Search

> **Subtopic of:** Trees, Graphs  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Breadth-First Search (BFS)** explores nodes **level by level**, using a **queue**. It visits all neighbors at the current depth before going deeper.

```
Tree:          BFS visits in order:
    1          Level 0:  1
   / \         Level 1:  2, 3
  2   3        Level 2:  4, 5, 6
 / \   \
4   5   6
```

---

## When to Use BFS

| Situation | Why BFS |
|---|---|
| Shortest path in **unweighted** graph | BFS guarantees fewest edges |
| Level-by-level processing | BFS naturally groups by depth |
| "Right/left side view" | Take last/first node at each level |
| Width / layer questions | Process level size each iteration |
| Multi-source shortest path | Push all sources into queue at start |

---

## Core Template

```cpp
queue<TreeNode*> q;
q.push(root);

while (!q.empty()) {
    int levelSize = q.size();          // freeze the level count

    for (int i = 0; i < levelSize; i++) {
        auto node = q.front(); q.pop();

        // ──── process node ────
        
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

**Key insight:** `int levelSize = q.size()` at the top of each outer loop freezes the count of nodes at the current level. Inner loop processes exactly that many nodes before moving to the next level.

---

## Common BFS Patterns

### Pattern 1 — Level-Order Collection
Collect all values per level.

```cpp
vector<vector<int>> res;
while (!q.empty()) {
    int sz = q.size();
    vector<int> level;
    while (sz--) {
        auto node = q.front(); q.pop();
        level.push_back(node->val);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    res.push_back(level);
}
```

---

### Pattern 2 — Zigzag Level Order
Alternate reversing each level.

```cpp
bool rev = false;
while (!q.empty()) {
    int sz = q.size();
    vector<int> level;
    while (sz--) {
        auto node = q.front(); q.pop();
        level.push_back(node->val);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    if (rev) reverse(level.begin(), level.end());
    res.push_back(level);
    rev = !rev;
}
```

**Used in:** 0103 Zigzag Level Order Traversal

---

### Pattern 3 — Right/Left Side View
Take the last (or first) node at each level.

```cpp
while (!q.empty()) {
    int sz = q.size();
    int rightmost = -1;
    while (sz--) {
        auto node = q.front(); q.pop();
        rightmost = node->val;          // keep overwriting → last = rightmost
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    res.push_back(rightmost);
}
```

**Used in:** 0199 Right Side View

---

### Pattern 4 — BFS with Node Index (Width Calculation)
Assign array-style indices to nodes: left child = `2*i + 1`, right child = `2*i + 2`.

```cpp
deque<pair<TreeNode*, unsigned long long>> dq;
dq.push_back({root, 0});

while (!dq.empty()) {
    int sz = dq.size();
    unsigned long long offset = dq.front().second;  // normalize to avoid overflow
    auto [first, i1] = dq.front();
    auto [last,  i2] = dq.back();
    maxWidth = max(maxWidth, (int)(i2 - i1 + 1));

    while (sz--) {
        auto [node, idx] = dq.front(); dq.pop_front();
        idx -= offset;                               // normalize
        if (node->left)  dq.push_back({node->left,  2*idx + 1});
        if (node->right) dq.push_back({node->right, 2*idx + 2});
    }
}
```

**Used in:** 0662 Maximum Width of Binary Tree  
**Why normalize?** Indices can overflow `long long` for deep trees. Subtracting the leftmost index each level keeps values small.

---

### Pattern 5 — BFS with Position Tracking (Vertical Order)
Track `(row, col)` for each node.

```cpp
// col → [(row, val)]
map<int, vector<pair<int,int>>> mp;
queue<pair<TreeNode*, pair<int,int>>> q;
q.push({root, {0, 0}});

while (!q.empty()) {
    auto [node, pos] = q.front(); q.pop();
    auto [row, col] = pos;
    mp[col].push_back({row, node->val});
    if (node->left)  q.push({node->left,  {row+1, col-1}});
    if (node->right) q.push({node->right, {row+1, col+1}});
}
// Then sort each column by row, then value
```

**Used in:** 0987 Vertical Order Traversal

---

## BFS vs DFS for Trees

| | BFS | DFS |
|---|---|---|
| Order | Level by level | Branch by branch |
| Data structure | Queue | Recursion stack |
| Best for | Level, width, shortest path | Height, paths, subtrees |
| Space | O(width) — can be large | O(height) — O(log n) balanced |

---

## Complexity

| | Time | Space |
|---|---|---|
| BFS on tree/graph | O(V + E) | O(W) — max width |
| Level order (n nodes) | O(n) | O(n) worst case (complete tree last level) |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Not saving `q.size()` before loop | Always save: `int sz = q.size();` before inner loop |
| Forgetting null checks | Always `if (node->left) q.push(...)` |
| Using BFS when DFS needed | BFS = layer-wise; DFS = subtree-wise |
| Overflow in width indexing | Use `unsigned long long` + normalize by subtracting leftmost index |

---

## Problems in This Folder

| # | Problem | BFS Pattern | Key Detail |
|---|---|---|---|
| 0103 | Zigzag Level Order Traversal | Level collect + reverse | Toggle `rev` flag each level |
| 0199 | Binary Tree Right Side View | Level last node | Overwrite `temp` in inner loop → last = rightmost |
| 0662 | Maximum Width of Binary Tree | BFS + index numbering | `2*i+1`, `2*i+2`; normalize to prevent overflow |
| 0987 | Vertical Order Traversal | BFS + (row, col) tracking | Use `map<col, [(row,val)]>`; sort each column |
