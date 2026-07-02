# 🏔️ Heap / Priority Queue

## What Is It?

A **Heap** is a complete binary tree that satisfies the **heap property**:
- **Min-Heap:** Parent ≤ children (root = smallest element)
- **Max-Heap:** Parent ≥ children (root = largest element)

A **Priority Queue** is the abstract data structure — a heap is the most common implementation.

Key operations:
| Operation | Time Complexity |
|---|---|
| Insert | O(log n) |
| Peek top (min/max) | O(1) |
| Remove top | O(log n) |
| Build heap from array | O(n) |

---

## When to Use It

Signals in problems:
- Need to **repeatedly get the minimum or maximum** element
- Need to **merge sorted structures** (lists, arrays)
- Keywords: **"k largest"**, **"k smallest"**, **"k-th element"**, **"merge k sorted"**
- Need to efficiently find the **next best candidate** from multiple sources
- **Scheduling** or **priority-based** processing

---

## C++ Syntax

```cpp
// Max-heap (default)
priority_queue<int> maxPQ;
maxPQ.push(5);
maxPQ.top();   // 5 (largest)
maxPQ.pop();

// Min-heap
priority_queue<int, vector<int>, greater<int>> minPQ;

// Custom comparator (min-heap by first element of pair)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

// Custom struct comparator
struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;  // min-heap: smaller val = higher priority
    }
};
priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
```

---

## Core Patterns

### Pattern 1 — Merge K Sorted Lists/Arrays
Use a min-heap to always extract the globally minimum element from k sources.

```
Algorithm:
1. Push the first element of each list into the heap
2. Extract min from heap → add to result
3. Push the next element from that list into the heap
4. Repeat until heap is empty
```

```cpp
// Heap stores (value, list_index, element_index)
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

// Initialize: push first element of each list
for (int i = 0; i < k; i++)
    if (!lists[i].empty())
        pq.push({lists[i][0], i, 0});

while (!pq.empty()) {
    auto [val, listIdx, elemIdx] = pq.top(); pq.pop();
    result.push_back(val);
    
    if (elemIdx + 1 < lists[listIdx].size())
        pq.push({lists[listIdx][elemIdx + 1], listIdx, elemIdx + 1});
}
```

**Used in:** 0023 Merge K Sorted Lists  
**Why heap?** Without a heap, finding the minimum across k lists takes O(k) per element. With a heap, it's O(log k).

**Total complexity:** O(N log k) where N = total elements, k = number of lists

---

### Pattern 2 — K Largest / K Smallest Elements
Use a **min-heap of size k** to maintain the k largest elements seen so far.

```cpp
priority_queue<int, vector<int>, greater<int>> minPQ; // min-heap

for (int x : nums) {
    minPQ.push(x);
    if (minPQ.size() > k)
        minPQ.pop();  // remove the smallest of the k+1 elements
}

return minPQ.top();  // k-th largest
```

**Key insight:** Maintain a window of the top-k elements. The heap's top is always the k-th largest.

---

### Pattern 3 — K-th Largest in a Stream
Same idea — maintain a min-heap of size k. New elements challenge the minimum.

```cpp
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.push(val);
        if (pq.size() > k) pq.pop();
        return pq.top();
    }
};
```

---

### Pattern 4 — Dijkstra / Shortest Path
Min-heap gives the next closest node efficiently.

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
pq.push({0, src});  // {distance, node}

while (!pq.empty()) {
    auto [dist, node] = pq.top(); pq.pop();
    
    for (auto [neighbor, weight] : graph[node]) {
        if (dist + weight < distTo[neighbor]) {
            distTo[neighbor] = dist + weight;
            pq.push({distTo[neighbor], neighbor});
        }
    }
}
```

---

### Pattern 5 — Two Heaps (Median Finder)
Use a max-heap for the lower half and a min-heap for the upper half.

```cpp
priority_queue<int> lo;                              // max-heap: lower half
priority_queue<int, vector<int>, greater<int>> hi;   // min-heap: upper half

void add(int num) {
    lo.push(num);
    hi.push(lo.top()); lo.pop();  // balance: top of lo goes to hi
    if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
}

double getMedian() {
    return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0;
}
```

---

## How to Build Intuition

1. **Ask: "Do I need the min/max of a changing collection?"** → Heap
2. **Ask: "Am I merging sorted data from multiple sources?"** → Min-heap
3. **Ask: "Do I need the k-th largest/smallest?"** → Min-heap of size k
4. **Ask: "Do I need to process in priority order?"** → Priority queue
5. **Compare: sorting vs. heap**
   - Sorting: O(n log n), gets ALL sorted
   - Heap: O(n log k), gets only TOP k efficiently

---

## When NOT to Use a Heap

- You need elements in sorted order all at once → just sort
- k = n → sorting is simpler
- You need random access → heap doesn't support this

---

## The Comparator Trick (C++)

```cpp
// Min-heap by second element of pair
auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
    return a.second > b.second;  // "greater" = min-heap
};
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
```

**Rule:** In the comparator for priority_queue, `return a > b` gives a **min-heap** (opposite of sort!).

---

## Complexity

| Operation | Heap | Brute Force |
|---|---|---|
| K-th largest | O(n log k) | O(n log n) |
| Merge K sorted lists | O(N log k) | O(N log N) |
| Continuous median | O(log n) per insert | O(n) per insert |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Using max-heap when min-heap needed | Use `greater<int>` as comparator |
| Custom comparator logic inverted | `a > b` in comparator = min-heap (opposite of sort) |
| Forgetting to push next element after popping | In merge k lists, always push the next node from the same list |
| Heap of size 0 — calling top() | Always check `!pq.empty()` before `pq.top()` |
| Memory leaks with pointers | Use `delete` or smart pointers for heap nodes |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0023 | Merge K Sorted Lists | Merge K sorted | Min-heap by node value; always push next node from same list |

---

## Interview Tips

- Heap = "always get the best element efficiently"
- Know both **min-heap** and **max-heap** in your language of choice
- The "K largest/smallest" family of problems is extremely common — know the min-heap-of-size-k trick
- **Merge K sorted** is the canonical heap problem — practice it until it's automatic
- Heaps appear in: Dijkstra, Prim's MST, scheduling, stream processing
- Know the **two-heap trick** for median finding — often asked at senior interviews
- In Python: `heapq` is a min-heap by default; negate values for max-heap
