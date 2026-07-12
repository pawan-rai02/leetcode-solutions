# 🔍 Binary Search Tree (BST)

> **Subtopic of:** Trees  
> Problems here also appear in their primary topic folder.

---

## What Is It?

A **Binary Search Tree (BST)** is a binary tree where every node satisfies:
- All nodes in the **left subtree** have values **< node.val**
- All nodes in the **right subtree** have values **> node.val**

```
        8
       / \
      3   10
     / \    \
    1   6    14
       / \   /
      4   7 13

BST property: 1 < 3 < 4 < 6 < 7 < 8 < 10 < 13 < 14
Inorder traversal gives sorted order!
```

---

## Key BST Properties

| Property | Value |
|---|---|
| Inorder traversal | Always sorted (ascending) |
| Search | O(h) — O(log n) balanced, O(n) skewed |
| Insert | O(h) |
| Delete | O(h) |
| Min element | Leftmost node |
| Max element | Rightmost node |
| Successor | Leftmost in right subtree |
| Predecessor | Rightmost in left subtree |

---

## Core BST Operations

### Search
```cpp
TreeNode* search(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return search(root->left, val);
    return search(root->right, val);
}
```

### Insert (Recursive)
```cpp
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);   // found insertion spot
    if (val < root->val)
        root->left  = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}
```

### Insert (Iterative)
```cpp
void insert(TreeNode* root, int val) {
    TreeNode* curr = root, *prev = nullptr;
    while (curr) {
        prev = curr;
        if (val < curr->val) curr = curr->left;
        else curr = curr->right;
    }
    if (val < prev->val) prev->left  = new TreeNode(val);
    else                  prev->right = new TreeNode(val);
}
```
**Used in:** 0701 Insert into a BST

---

### Validate BST
```cpp
bool isValid(TreeNode* root, long min_val, long max_val) {
    if (!root) return true;
    if (root->val <= min_val || root->val >= max_val) return false;
    return isValid(root->left,  min_val, root->val)
        && isValid(root->right, root->val, max_val);
}
// Call: isValid(root, LLONG_MIN, LLONG_MAX)
```

---

### Delete Node
```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val)      root->left  = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left)  return root->right;
        if (!root->right) return root->left;
        // Find inorder successor (leftmost of right subtree)
        TreeNode* suc = root->right;
        while (suc->left) suc = suc->left;
        root->val   = suc->val;
        root->right = deleteNode(root->right, suc->val);
    }
    return root;
}
```

---

## BST vs General Binary Tree

| Operation | BST | General Binary Tree |
|---|---|---|
| Search | O(log n) balanced | O(n) — must visit all |
| Find min/max | O(h) — go left/right | O(n) |
| Inorder = sorted | ✅ Always | ❌ Not necessarily |
| Insert position | Deterministic | Varies |

---

## Two Sum in a BST

Classic pattern: DFS the BST and use a **HashSet** to check for the complement.

```cpp
unordered_set<int> seen;

bool findTarget(TreeNode* root, int k) {
    if (!root) return false;

    if (seen.count(k - root->val))
        return true;        // found pair

    seen.insert(root->val);

    return findTarget(root->left, k)
        || findTarget(root->right, k);
}
```

**Why not use BST property for two-sum?** The BST property doesn't directly help you find `k - x` without a full scan, so a hashset is the practical approach.

**Used in:** 0653 Two Sum IV (BST)

---

## BST Iterator Pattern (Inorder)

When you need to traverse BST in sorted order without sorting:

```cpp
stack<TreeNode*> st;
TreeNode* curr = root;

// Initialization: push all leftmost nodes
while (curr) {
    st.push(curr);
    curr = curr->left;
}

// next()
int next() {
    auto node = st.top(); st.pop();
    int val = node->val;
    // Push right subtree's leftmost path
    curr = node->right;
    while (curr) {
        st.push(curr);
        curr = curr->left;
    }
    return val;
}
```

---

## Common BST Interview Patterns

| Pattern | Key Insight |
|---|---|
| Search/insert/delete | Use BST property: go left if smaller, right if larger |
| Validate BST | Pass range `[min, max]` — don't just compare with parent |
| Kth smallest element | Inorder traversal = sorted order |
| Convert sorted array to BST | Always pick the **middle** as root |
| LCA in BST | If both are less → go left; both greater → go right; else current node |
| Floor/Ceiling in BST | Binary search but save candidates on the way down |

---

## Balanced BST vs Unbalanced

```
Balanced BST (height = O(log n)):     Skewed BST (height = O(n)):
        4                              1
       / \                              \
      2   6                              2
     / \ / \                              \
    1  3 5  7                              3
                                            \
                                             4
All ops: O(log n)                All ops: O(n) — degenerates to linked list
```

To guarantee balance, use **AVL trees** or **Red-Black trees** (C++ `std::set` / `std::map` use Red-Black trees internally).

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Validating BST by only comparing with parent | Use `[min, max]` range passed down |
| Forgetting BST inorder = sorted | Use this property for "kth smallest" etc. |
| Skipping BST property in search | Always eliminate half the tree — don't DFS both children |
| Not handling both `left=null` and `right=null` on delete | Check each child separately |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0653 | Two Sum IV (Input is a BST) | DFS + HashSet | Traverse tree; check if `k - val` is in seen set |
| 0701 | Insert into a BST | Iterative BST walk | Walk left/right based on value; link new node to the `prev` pointer |
