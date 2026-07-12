# 📅 Intervals

## What Is It?

**Interval problems** deal with ranges `[start, end]` on a number line. You're typically given a list of intervals and asked to merge them, find overlaps, cover a range, or count intersections.

These problems are deceptively simple but require careful edge-case handling around overlap conditions.

---

## When to Use It

Signals in a problem:
- Input is a list of `[start, end]` pairs
- Keywords: "merge", "overlap", "insert", "meeting rooms", "cover", "arrow", "burst"
- Asks about time slots, calendar events, ranges, or segments

---

## The Fundamental Overlap Condition

Two intervals `[a, b]` and `[c, d]` **overlap** if and only if:
```
a <= d  AND  c <= b
```

They **do NOT overlap** if:
```
b < c   (first ends before second starts)
d < a   (second ends before first starts)
```

**Memorize this:** `b < c` means no overlap. Everything else = overlap.

---

## Merged Interval
When two intervals overlap, their merge is:
```
[ min(a, c), max(b, d) ]
```

---

## Core Patterns

### Pattern 1 — Sort + Merge (Merge Overlapping Intervals)
Sort by start time. Then greedily merge.

```cpp
sort(intervals.begin(), intervals.end());

vector<vector<int>> res;
res.push_back(intervals[0]);

for (int i = 1; i < intervals.size(); i++) {
    int currStart = intervals[i][0];
    int currEnd   = intervals[i][1];
    int lastEnd   = res.back()[1];
    
    if (currStart <= lastEnd) {
        // Overlap: extend the last interval
        res.back()[1] = max(lastEnd, currEnd);
    } else {
        // No overlap: add as new interval
        res.push_back(intervals[i]);
    }
}
```

**Used in:** LC 56 Merge Intervals

---

### Pattern 2 — Insert Interval
Given sorted non-overlapping intervals, insert a new one and merge.

```cpp
// Three phases:
// 1. Add all intervals that end before the new one starts
// 2. Merge all overlapping intervals with the new one
// 3. Add remaining intervals

for (auto& it : intervals) {
    if (it[1] < newStart) {
        // Completely before: add as-is
        res.push_back(it);
    } else if (it[0] > newEnd) {
        // Completely after: insert new interval, then add remaining
        if (!inserted) { res.push_back({newStart, newEnd}); inserted = true; }
        res.push_back(it);
    } else {
        // Overlapping: expand the new interval to cover both
        newStart = min(newStart, it[0]);
        newEnd   = max(newEnd,   it[1]);
    }
}
if (!inserted) res.push_back({newStart, newEnd});
```

**Used in:** 0057 Insert Interval

---

### Pattern 3 — Minimum Arrows / Points to Cover All Intervals
Sort by **end** time. Greedily try to pierce the maximum number of intervals with each arrow.

```cpp
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a[1] < b[1];  // sort by end
});

int arrows = 1;
int arrowPos = intervals[0][1];  // place first arrow at end of first interval

for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] > arrowPos) {
        // Current interval is not pierced by last arrow
        arrows++;
        arrowPos = intervals[i][1];  // new arrow at this interval's end
    }
}
```

**Used in:** 0452 Min Number of Arrows to Burst Balloons  
**Key insight:** Sort by end time. Place arrow as late as possible (at end) to maximize coverage of future intervals.

> Note: This problem is also in the Greedy folder because it uses a greedy strategy.

---

### Pattern 4 — Meeting Rooms (Can All Meetings Fit?)
Sort by start. Check if any two consecutive intervals overlap.

```cpp
sort(intervals.begin(), intervals.end());
for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] < intervals[i-1][1])
        return false;  // overlap found
}
return true;
```

---

### Pattern 5 — Minimum Meeting Rooms (How Many Rooms Needed?)
Use a min-heap of end times.

```cpp
sort(intervals.begin(), intervals.end());
priority_queue<int, vector<int>, greater<int>> pq;  // min-heap of end times

for (auto& interval : intervals) {
    if (!pq.empty() && pq.top() <= interval[0])
        pq.pop();  // reuse this room
    pq.push(interval[1]);  // assign room with this end time
}

return pq.size();  // number of rooms in use
```

---

## Overlap Edge Cases

| Case | Diagram | Overlaps? |
|---|---|---|
| `[1,3]` and `[2,4]` | `1--3` / `2--4` | ✅ Yes |
| `[1,3]` and `[3,5]` | `1--3` / `3--5` | Depends: `<=` means yes, `<` means no |
| `[1,2]` and `[3,4]` | `1-2` / `3-4` | ❌ No |

**Always clarify:** Are endpoints **inclusive** or **exclusive**?  
- `[1,3]` and `[3,5]` touch at 3 — usually this counts as overlap

---

## Sort Order Matters

| Goal | Sort by |
|---|---|
| Merge intervals | Start time |
| Minimum arrows / minimum removals | End time |
| Meeting rooms (conflict detection) | Start time |
| Insert interval | Already sorted input |

---

## How to Build Intuition

1. **Draw it** — always draw intervals on a number line first
2. **Sort first** — unsorted intervals are nearly impossible to reason about
3. **Think about the current interval vs. the last merged** — does it overlap?
4. **For covering problems:** sort by end time and be greedy — the earliest-ending valid interval leaves the most room
5. **Use `max` for merging end times** — `min` for start times

---

## Complexity

| Problem | Time | Space |
|---|---|---|
| Merge Intervals | O(n log n) | O(n) |
| Insert Interval | O(n) (if already sorted) | O(n) |
| Min Arrows | O(n log n) | O(1) |
| Meeting Rooms II | O(n log n) | O(n) |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Wrong overlap condition | `a[0] <= b[1] && b[0] <= a[1]` is the full condition |
| Forgetting to insert remaining interval | After loop, check if `inserted` is still false |
| Wrong sort key | Use end time for "minimum coverage" problems |
| Not handling single interval edge case | Always check if list has ≥ 1 element |
| Integer overflow in large ranges | Use `long long` if ranges can be up to 2^31 |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0057 | Insert Interval | Insert + Merge | Three-phase scan: before, overlapping, after |
| 1288 | Remove Covered Intervals | Sort + greedy scan | Sort by start ASC, end DESC; skip interval if fully inside the current max end |

---

## Interview Tips

- **Drawing** intervals is essential — do it before coding
- Know all 4 patterns cold (merge, insert, arrows, meeting rooms)
- Common in Google/Meta/Amazon interviews — often disguised as scheduling or calendar problems
- The overlap condition is easy to get wrong under pressure — practice it
- "Minimum number of intervals to remove to make non-overlapping" = sort by end, greedy (similar to arrows)
