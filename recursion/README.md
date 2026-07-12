# 🔄 Recursion

> **Subtopic of:** Trees, Dynamic Programming  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Recursion** is a technique where a function calls itself with a smaller input until it reaches a **base case**. It's the natural way to solve problems with self-similar structure — especially trees, where every subtree is itself a tree.

```
maxDepth(root)
  = 1 + max(maxDepth(root->left), maxDepth(root->right))
         └─ same problem, smaller input
```

---

## When to Use Recursion

- The problem has **self-similar substructure** (trees, fractals, divide & conquer)
- You can define `solve(n)` in terms of `solve(n-1)` or `solve(smaller)`
- The problem involves **tree traversal** (every tree problem)
- You need to **explore all possibilities** (backtracking)
- Iterative solution is complex; recursion makes it elegant

---

## The Three Laws of Recursion

1. **Base case:** There must be a condition where recursion stops
2. **Progress:** Each recursive call must move closer to the base case
3. **Trust:** Assume the recursive call returns the correct answer for smaller inputs — use it

---

## Anatomy of a Recursive Function

```cpp
ReturnType solve(Input input) {
    // 1. BASE CASE — stop condition
    if (base_case_condition)
        return base_value;

    // 2. RECURSIVE CASE — break into smaller subproblems
    ReturnType left  = solve(smaller_input_1);
    ReturnType right = solve(smaller_input_2);

    // 3. COMBINE — use child results to produce current result
    return combine(left, right, current_input);
}
```

---

## Tree Recursion Patterns

### Pattern 1 — Compute and Return (Bottom-Up)
Each call returns a value; parent combines children's values.

```cpp
int maxDepth(TreeNode* root) {
    if (!root) return 0;                        // base case

    int left  = maxDepth(root->left);           // recurse
    int right = maxDepth(root->right);

    return 1 + max(left, right);                // combine
}
```
**Used in:** 0104 Max Depth, 0222 Count Nodes

---

### Pattern 2 — Side Effect (Update Global)
The function returns one thing (e.g., height) but updates a global variable as a side effect.

```cpp
int maxDia = 0;

int height(TreeNode* root) {
    if (!root) return 0;

    int L = height(root->left);
    int R = height(root->right);

    maxDia = max(maxDia, L + R);   // side effect: update diameter

    return 1 + max(L, R);          // primary return: height
}
```
**Used in:** 0543 Diameter, 0124 Max Path Sum

---

### Pattern 3 — Sentinel Value
Return a special value (like `-1`) to signal an error/invalid state upward.

```cpp
int height(TreeNode* root) {
    if (!root) return 0;

    int L = height(root->left);
    if (L == -1) return -1;         // propagate failure up immediately

    int R = height(root->right);
    if (R == -1) return -1;

    if (abs(L - R) > 1) return -1; // this node is unbalanced — signal failure

    return 1 + max(L, R);
}
```
**Used in:** 0110 Balanced Binary Tree

---

### Pattern 4 — Boolean Recursion
Both left and right sub-calls must be true (or one must be true).

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;   // both null → same
    if (!p || !q) return false;  // one null → not same
    if (p->val != q->val) return false;

    return isSameTree(p->left, q->left)
        && isSameTree(p->right, q->right);
}
```
**Used in:** 0100 Same Tree

---

### Pattern 5 — Return Found Node
Return a pointer/node if found, nullptr if not. Combine with "if found, propagate up."

```cpp
TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    auto left  = lca(root->left, p, q);
    auto right = lca(root->right, p, q);

    if (left && right) return root;   // both found → current is LCA
    return left ? left : right;        // propagate whichever was found
}
```
**Used in:** 0236 Lowest Common Ancestor

---

## Recursion vs Iteration

| | Recursion | Iteration |
|---|---|---|
| Code clarity | Often cleaner for trees | More verbose |
| Stack space | O(depth) — can overflow | O(1) with explicit stack |
| Performance | Slight overhead (function calls) | Marginally faster |
| Use case | Trees, divide & conquer | Graphs (BFS), simple loops |

**Rule of thumb:** Use recursion for trees. Use iteration for graphs (BFS) or when depth is very large.

---

## Call Stack Visualization

```
maxDepth(1)
  maxDepth(2)
    maxDepth(4) → returns 1
    maxDepth(5) → returns 1
  → returns 2
  maxDepth(3)
    maxDepth(6) → returns 1
  → returns 2
→ returns 3
```

Each function call is pushed on the call stack. When it returns, control goes back to the caller with the returned value.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Missing base case → infinite recursion | Always handle `if (!root) return ...` first |
| Wrong base case value | `return 0` for count/height; `return nullptr` for node; `return true` for match |
| Not using return value | `int left = recurse(root->left);` — don't forget to assign |
| Trusting the wrong thing | Trust the recursive call; don't try to simulate it mentally |
| Stack overflow on long chains | Consider iterative if depth > 10^4 |

---

## Complexity

| Pattern | Time | Space (stack) |
|---|---|---|
| Single recursion (one child each) | O(n) | O(n) — worst case skewed tree |
| Binary recursion (two children) | O(n) | O(h) — height of tree |
| Balanced tree | O(n) time, O(log n) space | |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0100 | Same Tree | Boolean recursion | Both left and right subtrees must match |
| 0104 | Max Depth | Return + combine | `1 + max(left, right)` |
| 0110 | Balanced Binary Tree | Sentinel (-1) | Propagate failure upward without extra pass |
| 0124 | Max Path Sum | Side effect + return | Return single arm; update global with both arms |
| 0222 | Count Complete Tree Nodes | Return + combine | `1 + count(left) + count(right)` |
| 0236 | Lowest Common Ancestor | Return found node | Both sides non-null → root is LCA |
| 0543 | Diameter of Binary Tree | Side effect + return | Return height; track diameter as `left + right` |
