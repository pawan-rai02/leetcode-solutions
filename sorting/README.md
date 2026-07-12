# 📊 Sorting

> **Subtopic of:** Greedy, Intervals  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Sorting** is the arrangement of elements in a defined order (ascending, descending, or by a custom key). In competitive programming, sorting is almost always the **first step** that unlocks a greedy or two-pointer solution.

> Sorting trades O(n log n) upfront cost for O(n) or O(1) processing afterward.

---

## When Sorting Unlocks Solutions

| Problem Type | Sort By | Then Do |
|---|---|---|
| Greedy matching (cookies, players) | Value | Two-pointer matching |
| Interval problems | Start or end time | Greedy scan |
| Remove covered intervals | Start ASC, end DESC | Single scan |
| Find kth element | Value | Return index |
| Rank assignment | Value | Assign rank in order |
| Profit maximization | Difficulty / capacity | Sweep with running max |

---

## C++ Sorting Cheatsheet

```cpp
// Sort ascending (default)
sort(arr.begin(), arr.end());

// Sort descending
sort(arr.begin(), arr.end(), greater<int>());

// Sort with custom comparator (lambda)
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a[1] < b[1];  // sort by end time
});

// Sort pairs — by first, then second (default)
sort(pairs.begin(), pairs.end());

// Sort objects by custom key
sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
    return a.difficulty < b.difficulty;
});

// Partial sort — only sort top k elements
partial_sort(arr.begin(), arr.begin() + k, arr.end());

// Stable sort (preserves relative order of equals)
stable_sort(arr.begin(), arr.end());
```

---

## Sorting Algorithms Complexity

| Algorithm | Best | Average | Worst | Space | Stable? |
|---|---|---|---|---|---|
| QuickSort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| MergeSort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| HeapSort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| **std::sort** | O(n log n) | O(n log n) | O(n log n) | O(log n) | No |
| **std::stable_sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |

`std::sort` uses **introsort** (hybrid quicksort + heapsort + insertion sort) — fastest in practice.

---

## Core Patterns

### Pattern 1 — Sort + Greedy Scan
Sort first; then a single O(n) greedy pass gives the answer.

```cpp
sort(intervals.begin(), intervals.end()); // sort by start
int arrows = 1;
int arrowEnd = intervals[0][1];
for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] > arrowEnd) {
        arrows++;
        arrowEnd = intervals[i][1];
    } else {
        arrowEnd = min(arrowEnd, intervals[i][1]);
    }
}
```
**Used in:** 0452 Min Arrows to Burst Balloons

---

### Pattern 2 — Sort + Two-Pointer Matching
Sort both arrays; use two pointers to greedily match.

```cpp
sort(g.begin(), g.end());  // greed
sort(s.begin(), s.end());  // cookies
int i = n-1, j = m-1, res = 0;
while (i >= 0 && j >= 0) {
    if (s[j] >= g[i]) { res++; i--; j--; }
    else i--;
}
```
**Used in:** 0455 Assign Cookies, 2410 Max Matching Players

---

### Pattern 3 — Sort + Running Max (Best-So-Far)
Sort jobs by difficulty; sweep workers in order of ability.

```cpp
sort(jobs.begin(), jobs.end());    // by difficulty
sort(workers.begin(), workers.end());
int j = 0, best = 0;
for (int ability : workers) {
    while (j < jobs.size() && ability >= jobs[j].first)
        best = max(best, jobs[j++].second);
    result += best;
}
```
**Used in:** 0826 Most Profit Assigning Work

---

### Pattern 4 — Sort + Rank Assignment
Sort a copy; assign rank in order; map original → rank.

```cpp
vector<int> sorted = arr;
sort(sorted.begin(), sorted.end());
unordered_map<int, int> rank;
int r = 1;
for (int x : sorted)
    if (!rank.count(x)) rank[x] = r++;
for (int& x : arr) x = rank[x];
```
**Used in:** 1331 Rank Transform of an Array

---

### Pattern 5 — Sort by Start ASC, End DESC (Covering)
Custom comparator to handle tied start times correctly.

```cpp
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    if (a[0] != b[0]) return a[0] < b[0];  // start ASC
    return b[1] < a[1];                     // end DESC (larger end first)
});
// Then: if current end <= running max end, it's covered → skip
```
**Used in:** 1288 Remove Covered Intervals

---

## Custom Comparator Gotchas

```cpp
// Correct: strict weak ordering
[](auto& a, auto& b) { return a < b; }

// WRONG: returns true when equal → undefined behavior
[](auto& a, auto& b) { return a <= b; }

// Multi-key: first by x, then by y
[](auto& a, auto& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
```

**Rule:** Comparator must satisfy **strict weak ordering** — `comp(a, a)` must be `false`.

---

## When NOT to Sort

- When order of input matters for the answer (sorting would destroy it)
- When you need the original indices (save them before sorting)
- When n is too small and overhead isn't worth it

**Trick to preserve indices while sorting:**
```cpp
vector<int> idx(n);
iota(idx.begin(), idx.end(), 0);         // idx = [0, 1, 2, ..., n-1]
sort(idx.begin(), idx.end(), [&](int a, int b) {
    return arr[a] < arr[b];              // sort indices by arr value
});
// idx[0] = index of smallest element
```

---

## Complexity

| Step | Time |
|---|---|
| Sorting n elements | O(n log n) |
| Single scan after sort | O(n) |
| Total | O(n log n) |

Sorting is almost never the bottleneck. It enables O(n) solutions that would otherwise be O(n²).

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Using `<=` in comparator | Use `<` only (strict weak ordering) |
| Sorting when order matters | Save original indices or use stable sort |
| Wrong sort key for intervals | For arrows: sort by end. For merge: sort by start. For covered: sort by start ASC, end DESC |
| Forgetting to sort BOTH arrays | In two-pointer matching, both must be sorted |

---

## Problems in This Folder

| # | Problem | Sort Key | Pattern |
|---|---|---|---|
| 0057 | Insert Interval | Already sorted input | Three-phase merge scan (no sort needed) |
| 0452 | Min Arrows to Burst Balloons | By end time | Greedy: place arrow at end of first interval |
| 0455 | Assign Cookies | Both arrays ascending | Two-pointer match largest-to-largest |
| 0826 | Most Profit Assigning Work | Jobs by difficulty | Sweep with running best profit |
| 1288 | Remove Covered Intervals | Start ASC, End DESC | Skip if `curr_end <= running_max_end` |
| 1331 | Rank Transform of an Array | Value ascending | Assign rank, map back to original positions |
| 1846 | Max Element After Rearranging | Ascending | Clamp each element to `prev + 1` if gap too large |
| 2410 | Max Matching Players & Trainers | Both ascending | Two-pointer from largest — match strongest trainer to strongest player |
