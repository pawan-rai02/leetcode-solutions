# 👆👆 Two Pointers

> **Subtopic of:** Sliding Window, Greedy  
> Problems here also appear in their primary topic folder.

---

## What Is It?

**Two Pointers** is a technique that uses two indices (`left` and `right`, or `i` and `j`) moving through data to solve problems more efficiently than nested loops.

Instead of O(n²) brute force, two pointers achieve **O(n)** or **O(n log n)** by ensuring each pointer moves in only one direction.

---

## When to Use Two Pointers

| Situation | Pattern |
|---|---|
| Sorted array + pair/triplet sum | Opposite-end pointers |
| Contiguous subarray / substring | Sliding window (same-direction) |
| Matching elements from two sorted arrays | Same-direction on both |
| Remove duplicates in-place | Slow + fast pointers |
| Partition / Dutch flag | Two-boundary pointers |

---

## The Four Pointer Configurations

### Configuration 1 — Opposite Ends (Converging)
Both pointers start at opposite ends and move toward each other.

```cpp
int left = 0, right = n - 1;
while (left < right) {
    if (condition(arr[left], arr[right])) {
        // found answer
        left++; right--;
    } else if (need_larger) {
        left++;
    } else {
        right--;
    }
}
```
**Used in:** Two Sum II (sorted), Trapping Rain Water, Container With Most Water

---

### Configuration 2 — Same Direction (Sliding Window)
Both pointers move right; `right` expands, `left` shrinks when invalid.

```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // add nums[right] to window state

    while (/* window invalid */) {
        // remove nums[left] from state
        left++;
    }

    // [left..right] is valid — update answer
}
```
**Used in:** 0076 Min Window Substring, 0992 Subarrays with K Distinct

---

### Configuration 3 — Two Sorted Arrays (Matching)
One pointer per array, both move right, matching elements greedily.

```cpp
sort(a); sort(b);
int i = 0, j = 0, res = 0;
while (i < n && j < m) {
    if (a[i] <= b[j]) {
        res++;       // match found
        i++; j++;
    } else {
        i++;         // a[i] too large — skip to smaller
    }
}
```
**Used in:** 0455 Assign Cookies, 2410 Max Matching Players & Trainers

---

### Configuration 4 — Pointer + Sorted Sweep (Best-So-Far)
Sort one array; sweep through the other with a running max.

```cpp
sort(jobs);   // by difficulty
sort(worker); // by ability
int i = 0, best = 0;
for (int ability : worker) {
    while (i < jobs.size() && ability >= jobs[i].difficulty)
        best = max(best, jobs[i++].profit);
    res += best;
}
```
**Used in:** 0826 Most Profit Assigning Work

---

## Two Pointers vs Sliding Window

They're closely related. The distinction:

| | Two Pointers (matching) | Sliding Window |
|---|---|---|
| Arrays | Two separate arrays | One array/string |
| Movement | Both move forward | Right always forward; left shrinks conditionally |
| Goal | Pair/match elements | Find optimal subarray/window |

---

## Intuition for Choosing Direction

- **Sorted + find pair with sum = target** → opposite ends (move based on sum vs target)
- **Both arrays sorted, match elements** → same direction, one pointer each
- **One array, contiguous window** → sliding window (same direction)
- **Find first satisfying position** → binary search (not two pointers)

---

## Complexity

| Pattern | Time | Space |
|---|---|---|
| Two pointers (any) | O(n) or O(n log n) with sort | O(1) |
| Brute force alternative | O(n²) | O(1) |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Not sorting before matching | Two-array matching requires both sorted |
| Moving wrong pointer | If sum too small: advance `left` (or `i`); too large: retreat `right` |
| Using greedy direction incorrectly | For match-best: match largest-to-largest (or smallest-to-smallest) |
| Off-by-one in match logic | Test on `[1], [1]` single-element inputs |

---

## Problems in This Folder

| # | Problem | Pattern | Key Detail |
|---|---|---|---|
| 0076 | Min Window Substring | Sliding window (shrink when valid) | Shrink when all required chars found; track min window |
| 0455 | Assign Cookies | Two sorted arrays — match smallest | Match smallest sufficient cookie to least greedy child |
| 0826 | Most Profit Assigning Work | Sort + sweep with running max | Sort jobs by difficulty; sweep workers by ability |
| 0992 | Subarrays with K Distinct | Sliding window (atMost trick) | `exactly(k) = atMost(k) - atMost(k-1)` |
| 2410 | Max Matching Players & Trainers | Two sorted arrays — match largest | Match strongest trainer to strongest player first |
