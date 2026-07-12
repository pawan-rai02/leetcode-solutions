# 🗺️ Graphs

## What Is It?

A **Graph** is a collection of **nodes (vertices)** connected by **edges**. Unlike trees, graphs can have cycles, disconnected components, and edges pointing in any direction.

```
Undirected Graph:          Directed Graph:
  1 — 2 — 3                 1 → 2 → 3
  |       |                 ↑       |
  4 ——————                  4 ←————
```

---

## Key Terminology

| Term | Meaning |
|---|---|
| **Vertex / Node** | A point in the graph |
| **Edge** | A connection between two nodes |
| **Directed (Digraph)** | Edges have a direction (one-way) |
| **Undirected** | Edges go both ways |
| **Weighted** | Edges have a cost/weight |
| **Component** | A group of nodes all reachable from each other |
| **Cycle** | A path that starts and ends at the same node |
| **DAG** | Directed Acyclic Graph — no cycles |
| **Degree** | Number of edges connected to a node |

---

## Graph Representations

### Adjacency List (preferred for sparse graphs)
```cpp
// Unweighted
vector<vector<int>> adj(n);
adj[u].push_back(v);
adj[v].push_back(u); // undirected

// Weighted
vector<vector<pair<int,int>>> adj(n);
adj[u].push_back({v, weight});
```

### Adjacency Matrix (for dense graphs or quick edge lookup)
```cpp
vector<vector<int>> mat(n, vector<int>(n, 0));
mat[u][v] = 1;  // or weight
```

---

## Core Traversals

### DFS (Depth-First Search)
Goes deep before backtracking. Uses recursion (or explicit stack).

```cpp
vector<bool> vis(n, false);

void dfs(int u, vector<vector<int>>& adj) {
    vis[u] = true;
    // process u

    for (int v : adj[u]) {
        if (!vis[v])
            dfs(v, adj);
    }
}
```

**Used for:** Connected components, cycle detection, topological sort, path finding, DFS on grid

---

### BFS (Breadth-First Search)
Explores level by level. Uses a queue. Gives **shortest path in unweighted graphs**.

```cpp
vector<bool> vis(n, false);
queue<int> q;
q.push(src);
vis[src] = true;

while (!q.empty()) {
    int u = q.front(); q.pop();
    // process u

    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            q.push(v);
        }
    }
}
```

**Used for:** Shortest path (unweighted), level-order traversal, bipartite check

---

## Common Problem Patterns

### Pattern 1 — Connected Components (DFS/BFS)
Count or identify disconnected subgraphs.

```cpp
int components = 0;
vector<bool> vis(n, false);

for (int i = 0; i < n; i++) {
    if (!vis[i]) {
        dfs(i, adj, vis);
        components++;
    }
}
```

**Used in:** 2492 Min Score Path (DFS finds all edges in connected component of node 1), 2685 Count Complete Components

---

### Pattern 2 — Minimum in a Connected Component
DFS/BFS through the entire component and track a property (min weight, max value, etc.).

```cpp
int res = INT_MAX;

void dfs(int src, vector<vector<pair<int,int>>>& adj, vector<bool>& vis, int& res) {
    vis[src] = true;
    for (auto [v, wt] : adj[src]) {
        res = min(res, wt);
        if (!vis[v]) dfs(v, adj, vis, res);
    }
}
```

**Key insight in 2492:** The answer is the minimum edge weight in the **entire connected component** containing node 1. Because you can always traverse back and forth along any edge in the component, you can reach any edge weight in that component.

**Used in:** 2492 Minimum Score of a Path Between Two Cities

---

### Pattern 3 — Complete Graph Component Check
A component with `n` nodes is complete if it has exactly `n*(n-1)/2` edges.

```cpp
void dfs(int u, ..., int& nodes, int& edges) {
    vis[u] = true;
    nodes++;
    edges += adj[u].size();  // count degree

    for (int v : adj[u])
        if (!vis[v]) dfs(v, ..., nodes, edges);
}

// After DFS on a component:
edges /= 2;  // each edge counted twice in undirected graph
if (edges == nodes * (nodes - 1) / 2)
    complete_components++;
```

**Used in:** 2685 Count the Number of Complete Components

---

### Pattern 4 — Union-Find / DSU (Disjoint Set Union)
Efficiently merge components and answer "are two nodes connected?" queries.

```cpp
struct DSU {
    vector<int> parent, rank;

    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;  // union by rank
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

**When to use:** When you need to dynamically merge sets and check connectivity without DFS overhead.  
**Time:** O(α(n)) per operation (nearly O(1) amortized)

**Used in:** 3532 Path Existence Queries — union adjacent indices whose values differ by ≤ maxDiff, then answer connectivity queries

---

### Pattern 5 — Topological Sort (DAG ordering)
Order nodes so every edge goes from earlier to later.

**Kahn's Algorithm (BFS):**
```cpp
vector<int> indegree(n, 0);
for (auto [u, v] : edges) indegree[v]++;

queue<int> q;
for (int i = 0; i < n; i++)
    if (indegree[i] == 0) q.push(i);

vector<int> order;
while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);
    for (int v : adj[u]) {
        if (--indegree[v] == 0) q.push(v);
    }
}
// If order.size() != n → cycle exists
```

---

### Pattern 6 — Shortest Path

| Algorithm | When to Use | Complexity |
|---|---|---|
| BFS | Unweighted graph | O(V + E) |
| Dijkstra | Non-negative weights | O((V + E) log V) |
| Bellman-Ford | Negative weights | O(V × E) |
| Floyd-Warshall | All-pairs shortest paths | O(V³) |

**Dijkstra:**
```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
pq.push({0, src});
vector<int> dist(n, INT_MAX);
dist[src] = 0;

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;  // stale entry

    for (auto [v, wt] : adj[u]) {
        if (dist[u] + wt < dist[v]) {
            dist[v] = dist[u] + wt;
            pq.push({dist[v], v});
        }
    }
}
```

---

## Union-Find vs DFS/BFS

| | DFS/BFS | Union-Find |
|---|---|---|
| Build-time | Build graph first | Build incrementally |
| Query type | Single traversal | Many connectivity queries |
| Edge additions | Restart DFS | O(α(n)) update |
| Use case | Full graph exploration | Dynamic connectivity queries |

---

## How to Build Intuition

1. **Is the problem about connections?** → Graph
2. **Need shortest path?** → BFS (unweighted) or Dijkstra (weighted)
3. **Need all nodes in a component?** → DFS/BFS
4. **Many connectivity queries?** → Union-Find (DSU)
5. **Need ordering with dependencies?** → Topological sort
6. **Cycle detection?** → DFS with color marking (white/gray/black) or Union-Find

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Not marking visited before recursion | Mark `vis[u] = true` before pushing to queue / before recursing |
| Using directed edges for undirected problem | Add both `adj[u].push_back(v)` and `adj[v].push_back(u)` |
| Counting edges twice | In undirected graphs, `sum(degrees) / 2 = edge count` |
| Forgetting path compression in DSU | Always use `parent[x] = find(parent[x])` |
| Dijkstra with negative weights | Use Bellman-Ford instead |

---

## Complexity

| Algorithm | Time | Space |
|---|---|---|
| DFS/BFS | O(V + E) | O(V) |
| Dijkstra | O((V + E) log V) | O(V) |
| Union-Find (with opt.) | O(α(n)) per op | O(n) |
| Topological Sort | O(V + E) | O(V) |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 2492 | Minimum Score of Path Between Two Cities | DFS on component | Min edge weight = min weight in entire component containing node 1; DFS and track global min |
| 2685 | Count Complete Components | DFS + component analysis | Component is complete if `edges == nodes*(nodes-1)/2`; count degrees via DFS |
| 3532 | Path Existence Queries in Graph I | Union-Find (DSU) | Union adjacent indices if diff ≤ maxDiff; answer = `find(u) == find(v)` |

---

## Interview Tips

- Graphs are **extremely common** at FAANG — know DFS, BFS, Dijkstra, and Union-Find cold
- Always draw the graph before coding
- Clarify: **directed or undirected? Weighted? Can there be cycles?**
- **BFS = shortest path** in unweighted graphs — this is a fact to state in interviews
- Union-Find is the most elegant solution for dynamic connectivity problems
- Grid problems (LC 200 Number of Islands, LC 130 Surrounded Regions) are graph problems on an implicit grid graph
- Know: Topological sort for course scheduling, Bipartite check for coloring problems
- Common patterns: islands (DFS), shortest path in maze (BFS), redundant connection (Union-Find), course schedule (topological sort)
