# 🌳 Trees

## What Is It?

A **Tree** is a hierarchical data structure consisting of nodes, where each node has a value and zero or more child nodes. The topmost node is the **root**. Trees with at most 2 children per node are **Binary Trees**.

Most tree problems on LeetCode use **Binary Trees** or **Binary Search Trees (BSTs)**.

```
         1          ← root
        / \
       2   3
      / \
     4   5
```

---

## Key Terminology

| Term | Meaning |
|---|---|
| **Root** | Topmost node (no parent) |
| **Leaf** | Node with no children |
| **Height** | Length of longest path from node to a leaf |
| **Depth** | Length of path from root to node |
| **Subtree** | A node and all its descendants |
| **Ancestor** | Any node on the path from root to a node |
| **Diameter** | Longest path between any two nodes (may not pass through root) |

---

## When to Use Tree Techniques

- Problem gives you a `TreeNode*` structure
- Asks about **depth**, **height**, **diameter**, **paths**, **subtrees**
- Involves **traversal**: inorder, preorder, postorder, level-order
- Asks about **BST** properties: sorted order, valid BST, search
- Asks for **LCA** (Lowest Common Ancestor)

---

## Core Traversals

### DFS Traversals (Recursive)
The foundation of almost every tree problem.

```cpp
void dfs(TreeNode* root) {
    if (!root) return;
    
    // Preorder: process BEFORE children
    process(root);
    dfs(root->left);
    dfs(root->right);
    
    // Inorder: process BETWEEN children
    // dfs(root->left); process(root); dfs(root->right);
    
    // Postorder: process AFTER children
    // dfs(root->left); dfs(root->right); process(root);
}
```

| Traversal | Order | Use Case |
|---|---|---|
| **Preorder** | Root → Left → Right | Copy tree, print top-down |
| **Inorder** | Left → Root → Right | BST gives sorted order |
| **Postorder** | Left → Right → Root | Delete tree, compute subtree values |

---

### BFS Traversal (Level Order)
Use a queue. Process nodes level by level.

```cpp
void bfs(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int sz = q.size();           // nodes at current level
        for (int i = 0; i < sz; i++) {
            auto node = q.front(); q.pop();
            process(node);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
}
```

---

## Common Problem Patterns

### Pattern 1 — Return Value from Subtrees (Postorder)
Compute something about a subtree and return it upward.

```cpp
int solve(TreeNode* root) {
    if (!root) return 0;  // base case
    
    int left  = solve(root->left);   // get info from left
    int right = solve(root->right);  // get info from right
    
    // Use left + right + current node to compute answer
    return 1 + max(left, right);
}
```

**Used in:** Max Depth, Diameter, Balance Check, Min/Max in subtree

---

### Pattern 2 — Global Variable Updated During DFS
The answer doesn't fit neatly as a return value — maintain a global variable.

```cpp
int result = 0;

int dfs(TreeNode* root) {
    if (!root) return 0;
    
    int left  = dfs(root->left);
    int right = dfs(root->right);
    
    result = max(result, left + right);  // update global answer
    
    return 1 + max(left, right);         // return height to parent
}
```

**Used in:** 0543 Diameter of Binary Tree  
**Key insight:** The diameter at any node = `left_height + right_height`. But the return value is the height (not the diameter), because the parent needs height.

---

### Pattern 3 — Path Problems
Find a path (sum, max, any path between any two nodes).

```cpp
int maxPath = INT_MIN;

int dfs(TreeNode* root) {
    if (!root) return 0;
    
    int left  = max(0, dfs(root->left));   // don't take negative paths
    int right = max(0, dfs(root->right));
    
    maxPath = max(maxPath, left + right + root->val);  // path through root
    
    return root->val + max(left, right);  // best single path upward
}
```

**Used in:** Maximum Path Sum (LC 124)

---

### Pattern 4 — BST Properties
In BST: left subtree values < root < right subtree values.
Inorder traversal gives sorted order.

```cpp
// BST search
TreeNode* search(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return search(root->left, val);
    return search(root->right, val);
}
```

---

## How to Think About Tree Problems

1. **Think Recursively** — "What does each node need from its children? What does it return to its parent?"
2. **Identify the base case** — Usually `if (!root) return 0;` or `if (!root) return nullptr;`
3. **Decide: postorder or preorder?**
   - Postorder: compute something from children first → use it at current node
   - Preorder: pass information down from parent → use at children
4. **Do you need a global variable?** — When the answer involves combining left and right paths (can't be returned as-is to parent)
5. **Level-order for level-based questions** — Anything asking about "which level", "left-right view", "zigzag"

---

## The Return Value Trick

This is the most important concept for binary tree problems:

> The recursive function often returns **one thing** (e.g., height) but updates **another thing** (e.g., diameter) as a side effect.

| Problem | Returns to Parent | Updates Globally |
|---|---|---|
| Max Depth | height | — |
| Diameter | height | max diameter |
| Max Path Sum | max single path | max path sum |
| Check Balance | height (-1 if unbalanced) | — |

---

## Complexity

| Operation | Time | Space |
|---|---|---|
| DFS traversal | O(n) | O(h) — recursion stack |
| BFS traversal | O(n) | O(w) — max width of tree |
| BST search | O(h) | O(h) |

Where n = nodes, h = height (O(log n) balanced, O(n) skewed), w = max width.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Forgetting null check | Always `if (!root) return ...;` as first line |
| Confusing height and depth | Height = bottom-up. Depth = top-down |
| Returning wrong thing | Be clear: does parent need height? Path sum? Count? |
| Off-by-one in height | Height of leaf = 1 (not 0) if counting nodes; 0 if counting edges |
| Ignoring skewed trees | Always test on left-skewed and right-skewed inputs |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0100 | Same Tree | Recursive DFS | Simultaneously recurse both trees; check `val + left + right` match |
| 0103 | Binary Tree Zigzag Level Order | BFS + reverse flag | BFS level-order; alternate reversing the level vector |
| 0104 | Maximum Depth of Binary Tree | Postorder | `1 + max(leftH, rightH)` — height builds bottom-up |
| 0110 | Balanced Binary Tree | Postorder + sentinel | Return `-1` from DFS to propagate "unbalanced" upward |
| 0124 | Binary Tree Maximum Path Sum | Postorder + Global | Return best single-arm; update global with `left + right + val` |
| 0199 | Binary Tree Right Side View | BFS | At each level, track the last node seen (right-most) |
| 0222 | Count Complete Tree Nodes | Recursive counting | `1 + count(left) + count(right)` — O(n) simple recursion |
| 0236 | Lowest Common Ancestor | Postorder | If both subtrees return non-null → current node is LCA |
| 0543 | Diameter of Binary Tree | Postorder + Global | Return height to parent; update global diameter = `left + right` |
| 0653 | Two Sum IV (BST) | DFS + HashSet | Traverse BST; for each node check if `k - val` is in seen set |
| 0662 | Maximum Width of Binary Tree | BFS + index numbering | Assign indices (left=`2i+1`, right=`2i+2`); width = `last - first + 1` |
| 0701 | Insert into BST | Iterative BST walk | Walk down using BST property until `nullptr`; insert there |
| 0987 | Vertical Order Traversal | BFS + sorted map | BFS tracking `(row, col)`; group by col, sort by row then value |

---

## Interview Tips

- **Always clarify:** Is this a BST or a general binary tree?
- **Mention both recursive and iterative** approaches — shows depth of knowledge
- For diameter/path problems: the trick is "return height but track diameter globally"
- Know **Morris Traversal** for O(1) space inorder (bonus knowledge)
- Practice on:
  - Balanced Binary Tree (LC 110)
  - Lowest Common Ancestor (LC 236)
  - Binary Tree Maximum Path Sum (LC 124)
  - Serialize/Deserialize Binary Tree (LC 297)
- Level-order problems are easy wins — always use a queue with level size tracking
