# 🔗 Union-Find (Disjoint Set Union)

> **Subtopic of:** Graphs  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Union-Find** (also called **Disjoint Set Union / DSU**) is a data structure that efficiently tracks which elements belong to the same **group (component)**. It supports two core operations:

- **Find(x):** Which group does `x` belong to? (returns the representative/root)
- **Union(x, y):** Merge the groups containing `x` and `y`

```
Initial: {0} {1} {2} {3} {4}

union(0, 1) → {0,1} {2} {3} {4}
union(2, 3) → {0,1} {2,3} {4}
union(1, 3) → {0,1,2,3} {4}

find(0) == find(2)?  YES → same group
find(0) == find(4)?  NO  → different groups
```

---

## When to Use Union-Find

| Situation | Why DSU |
|---|---|
| Dynamic connectivity queries | "Are u and v connected?" in O(α(n)) |
| Merging components incrementally | Add edges one by one |
| Detect cycles in undirected graph | If `find(u) == find(v)` before `union(u, v)` → cycle |
| Kruskal's MST | Build MST by merging components |
| Number of connected components | Count how many roots have `parent[i] == i` |
| Group elements with shared property | Union elements satisfying a condition |

---

## Full Implementation

```cpp
struct DSU {
    vector<int> parent, rank;

    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    // Find root with PATH COMPRESSION
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // flatten tree
        return parent[x];
    }

    // Union with UNION BY RANK
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false; // already same set

        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int countComponents(int n) {
        int count = 0;
        for (int i = 0; i < n; i++)
            if (find(i) == i) count++;
        return count;
    }
};
```

---

## The Two Optimizations

### 1. Path Compression
When finding the root, make every node on the path point directly to the root. Flattens the tree.

```
Before find(4):     After find(4):
  1                   1
  |                 / | \
  2               2   3   4
  |
  3
  |
  4

find(4) returns 1. Now parent[4]=1, parent[3]=1, parent[2]=1.
```

```cpp
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); // RECURSIVE: compress on the way back up
    return parent[x];
}
```

### 2. Union by Rank
Always attach the shorter tree under the taller tree. Keeps tree height minimal.

```cpp
void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) swap(x, y);
    parent[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
}
```

**Together:** Path compression + union by rank → **O(α(n))** amortized per operation. α = inverse Ackermann function, effectively **O(1)** for all practical n.

---

## Pattern: Condition-Based Union

Merge elements that satisfy a certain condition.

```cpp
// Problem: are nodes u and v reachable from each other?
// Condition: union adjacent indices if |nums[i] - nums[i-1]| <= maxDiff

DSU dsu(n);
for (int i = 1; i < n; i++) {
    if (nums[i] - nums[i-1] <= maxDiff)
        dsu.unite(i, i-1);
}

// Answer queries
for (auto& q : queries) {
    ans.push_back(dsu.connected(q[0], q[1]));
}
```

**Used in:** 3532 Path Existence Queries in Graph I

---

## Pattern: Cycle Detection in Undirected Graph

```cpp
DSU dsu(n);
for (auto [u, v] : edges) {
    if (!dsu.unite(u, v))
        return true;  // cycle detected: u and v already connected
}
return false;
```

---

## Pattern: Count Connected Components

```cpp
DSU dsu(n);
for (auto [u, v] : edges)
    dsu.unite(u, v);

set<int> roots;
for (int i = 0; i < n; i++)
    roots.insert(dsu.find(i));

return roots.size();  // number of components
```

---

## Pattern: Kruskal's Minimum Spanning Tree

```cpp
sort(edges.begin(), edges.end()); // sort by weight
DSU dsu(n);
int mstWeight = 0;
for (auto [w, u, v] : edges) {
    if (dsu.unite(u, v))
        mstWeight += w;
}
```

---

## DSU vs DFS/BFS for Connectivity

| | DSU | DFS/BFS |
|---|---|---|
| Preprocessing | O(α(n)) per edge | O(V + E) one-time |
| Query (are u, v connected?) | O(α(n)) | O(V + E) each time |
| Edge additions after build | O(α(n)) per edge | Need full re-traversal |
| Best when | Many queries, dynamic edges | One-time full traversal |

**Use DSU when:** You'll add edges over time AND answer many connectivity queries.  
**Use DFS/BFS when:** You need to traverse the whole graph once.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Calling `find()` without path compression | Always use recursive `find` with `parent[x] = find(parent[x])` |
| Not calling `find()` before checking equality | `dsu.find(u) == dsu.find(v)`, not `parent[u] == parent[v]` |
| Forgetting to initialize `parent[i] = i` | Every element is its own root initially |
| Using DSU on directed graphs | DSU is for undirected graphs only |

---

## Complexity

| Operation | With Path Compression + Union by Rank |
|---|---|
| `find(x)` | O(α(n)) ≈ O(1) amortized |
| `unite(x, y)` | O(α(n)) ≈ O(1) amortized |
| Build DSU for n nodes, m edges | O(m × α(n)) |
| Space | O(n) |

α(n) is the inverse Ackermann function — grows so slowly that it's ≤ 4 for any n ≤ 10^600.

---

## Problems in This Folder

| # | Problem | DSU Pattern | Key Insight |
|---|---|---|---|
| 3532 | Path Existence Queries in Graph I | Condition-based union | Union adjacent `(i, i-1)` if `nums[i] - nums[i-1] <= maxDiff`; answer = `find(u) == find(v)` |
