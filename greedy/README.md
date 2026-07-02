# 💡 Greedy Algorithms

## What Is It?

A **Greedy** algorithm makes the **locally optimal choice at each step** with the hope that these local choices lead to a globally optimal solution.

There's no backtracking. No reconsideration. You make a decision and commit to it.

> "Always take the best option available right now."

---

## When to Use It

Signals in a problem:
- Asks for **minimum** or **maximum** of something
- Involves **sorting** as a first step
- You can **prove** that choosing the locally best option never hurts globally
- The problem has **no dependencies** between choices (unlike DP, where past choices affect future ones)
- Words like: "minimum number of", "maximum number of", "assign", "match", "distribute"

---

## Core Intuition

Greedy works when the problem has these two properties:

### 1. Greedy Choice Property
A globally optimal solution can always be arrived at by making a locally optimal (greedy) choice. You don't need to consider all possibilities.

### 2. Optimal Substructure
After making a greedy choice, the remaining subproblem has the same structure and can be solved optimally the same way.

**If you can't prove both** → suspect DP or backtracking instead.

---

## How to Verify a Greedy Approach

Ask yourself: **"If I always make the cheapest / largest / best choice, will I ever regret it?"**

- If NO → Greedy is safe
- If YES → You need DP (past choices affect future options)

**Exchange argument:** Assume a non-greedy solution is optimal. Show that swapping any non-greedy choice with the greedy choice doesn't make it worse. This proves greedy is valid.

---

## Common Greedy Patterns

### Pattern 1 — Sort + Greedy Scan
Sort to impose an order, then greedily scan.

```cpp
sort(arr.begin(), arr.end());
for (int i = 0; i < n; i++) {
    // make local best choice
}
```

**Used in:** Assign Cookies, Most Profit Assigning Work, Max Matching Players & Trainers, Arrows to Burst Balloons

---

### Pattern 2 — Two-Pointer Greedy Matching
Sort both arrays. Use two pointers to match optimally.

```cpp
sort(a.begin(), a.end());
sort(b.begin(), b.end());
int i = n - 1, j = m - 1, res = 0;
while (i >= 0 && j >= 0) {
    if (a[i] <= b[j]) { res++; i--; j--; }  // match
    else { i--; }                              // skip
}
```

**Used in:** 0455 Assign Cookies, 2410 Max Matching Players & Trainers  
**Intuition:** Match the biggest cookie to the greediest child. If the biggest cookie can't satisfy the greediest child, no cookie can.

---

### Pattern 3 — Interval Greedy
Sort intervals by end time (or start time), then greedily process.

```cpp
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a[1] < b[1]; // sort by end
});
// greedy scan
```

**Used in:** 0452 Min Arrows to Burst Balloons  
**Intuition:** Finish as early as possible to leave room for more intervals.

---

### Pattern 4 — Two-Pass Greedy (Left + Right)
Scan left-to-right to enforce one constraint, then right-to-left to enforce another.

```cpp
// Left pass: enforce left neighbor condition
for (int i = 1; i < n; i++)
    if (condition_left) arr[i] = arr[i-1] + 1;

// Right pass: enforce right neighbor condition
for (int i = n-2; i >= 0; i--)
    if (condition_right) arr[i] = max(arr[i], arr[i+1] + 1);
```

**Used in:** 0135 Candy  
**Intuition:** You can't handle both directions at once. Do each separately and combine with `max`.

---

### Pattern 5 — Reachability Greedy
Track maximum reachable index. If current index is beyond it, you're stuck.

```cpp
int maxReach = 0;
for (int i = 0; i < n; i++) {
    if (i > maxReach) return false;     // can't reach here
    maxReach = max(maxReach, i + nums[i]);
}
return true;
```

**Used in:** 0055 Jump Game

---

## How to Build Intuition

1. **Sort first** — most greedy problems need a sorted order to work
2. **Think about extremes** — "what's the best/worst I can pick right now?"
3. **Prove by contradiction** — "what if I made a different choice? Would it always be at least as good?"
4. **Identify the invariant** — what property holds true after each greedy step?
5. **Check: is there a dependency?** — If choosing X now means you CAN'T do Y later (in a complex way), greedy might not work

---

## Greedy vs Dynamic Programming

| | Greedy | DP |
|---|---|---|
| Makes choice | Once, irrevocably | Considers all possibilities |
| Subproblems | Don't overlap | Overlap and reuse |
| When | Greedy choice property holds | No greedy choice property |
| Speed | Faster (O(n log n) typically) | Slower (O(n²) or more) |
| Example | Assign Cookies | 0/1 Knapsack |

**Rule of thumb:** If you can sort + scan and it works → Greedy. If the order of choices matters (e.g., take item or not) → DP.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Not sorting first | Always consider sorting as step 1 |
| Greedy on wrong attribute | Sort by end time (not start time) for intervals |
| Using greedy when DP is needed | Test on edge cases — if greedy fails, switch to DP |
| Wrong comparison direction | For matching: match largest-to-largest or smallest-to-smallest |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0055 | Jump Game | Reachability greedy | Track `maxReach`; if `i > maxReach`, return false |
| 0135 | Candy | Two-pass greedy | Left pass (ascending), right pass (descending), take max |
| 0452 | Min Arrows Burst Balloons | Interval greedy | Sort by end; intersect overlapping ranges with 1 arrow |
| 0455 | Assign Cookies | Two-pointer greedy | Sort both; match biggest cookie to greediest child |
| 0826 | Most Profit Assigning Work | Sort + prefix max + two ptr | Sort jobs & workers; track best profit for each ability |
| 1846 | Max Element After Rearranging | Sort + greedy clamp | Sort, then set each element to min(arr[i], arr[i-1]+1) |
| 2410 | Max Matching Players & Trainers | Two-pointer greedy | Same as Assign Cookies — match strongest player to strongest trainer |

---

## Interview Tips

- **Greedy is your first guess** for optimization problems — it's simpler than DP
- Always **prove** your greedy before coding: "Why is the locally best choice globally safe?"
- Many "interval" problems are greedy (sorted by end time)
- "Assign X to Y optimally" problems are usually sort + two-pointer greedy
- If greedy gives Wrong Answer → move to DP
- Practice the **exchange argument** — it's the standard proof technique
