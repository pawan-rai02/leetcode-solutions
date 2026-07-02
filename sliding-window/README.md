# 🪟 Sliding Window

## What Is It?

The **Sliding Window** technique uses two pointers (`left` and `right`) that define a "window" — a contiguous subarray or substring. You slide this window across the data structure, expanding or shrinking it to satisfy a condition, instead of recomputing from scratch for every possible subarray (which would be O(n²) or worse).

The core idea: **maintain a valid window and move it efficiently**.

---

## When to Use It

Look for these signals in the problem statement:
- Words like **"subarray"**, **"substring"**, **"contiguous"**
- Asks for **minimum / maximum length** of a window satisfying a condition
- Asks to **count subarrays/substrings** satisfying a condition
- The answer involves a **range of elements**, not individual elements
- The input is an **array or string**
- Brute force would be O(n²) — sliding window brings it to O(2n)

---

## Core Intuition

> Think of a window on a train. You can open it (expand right), close it (shrink left), and slide it forward.

Instead of checking every possible `[i, j]` pair (O(n²)), you:
1. Expand the window by moving `right`
2. When the window violates a condition, shrink from `left`
3. At each step, record or count valid windows

This gives **O(n)** time because each element enters and leaves the window at most once.

---

## Two Types of Sliding Windows

### 1. Fixed-Size Window
The window size `k` is given. Simple sliding.

```
Pattern:
- Initialize window with first k elements
- Slide: add nums[right], remove nums[left], left++
```

**Example:** Maximum sum of subarray of size k.

```cpp
int maxSum(vector<int>& nums, int k) {
    int windowSum = 0, maxSum = 0;
    for (int i = 0; i < k; i++) windowSum += nums[i];
    maxSum = windowSum;
    for (int i = k; i < nums.size(); i++) {
        windowSum += nums[i] - nums[i - k];
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}
```

---

### 2. Variable-Size Window (Shrinkable)
The window grows and shrinks based on a condition. This is the most common interview type.

```
Pattern:
right = 0, left = 0
while right < n:
    add nums[right] to window state

    while window is INVALID:
        remove nums[left] from window state
        left++

    // window [left..right] is now valid
    update answer
    right++
```

**Key insight:** "Valid" means the window satisfies the problem constraint.

---

## Common Question Patterns

### Pattern 1 — Minimum Window (find smallest window satisfying condition)
> "Minimum window substring", "Smallest subarray with sum ≥ k"

```cpp
int left = 0, minLen = INT_MAX;
for (int right = 0; right < n; right++) {
    // Expand: include s[right]
    
    while (/* window is valid */) {
        minLen = min(minLen, right - left + 1);
        // Shrink: remove s[left]
        left++;
    }
}
```

**Trick:** Shrink when VALID (to minimize).

---

### Pattern 2 — Maximum Window (find largest window satisfying condition)
> "Longest subarray with at most k distinct", "Longest substring without repeating chars"

```cpp
int left = 0, maxLen = 0;
for (int right = 0; right < n; right++) {
    // Expand: include nums[right]
    
    while (/* window is INVALID */) {
        // Shrink: remove nums[left]
        left++;
    }
    
    maxLen = max(maxLen, right - left + 1);
}
```

**Trick:** Shrink when INVALID (to maintain validity).

---

### Pattern 3 — Count of Valid Subarrays
> "Number of subarrays with at most k distinct integers"

```cpp
// atMost(k) - atMost(k-1) = exactly k
int solve(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    int left = 0, count = 0;
    for (int right = 0; right < n; right++) {
        mp[nums[right]]++;
        while (mp.size() > k) {
            mp[nums[left]]--;
            if (mp[nums[left]] == 0) mp.erase(nums[left]);
            left++;
        }
        count += (right - left + 1); // all subarrays ending at right
    }
    return count;
}
```

**Why `right - left + 1`?** Every subarray ending at `right` and starting from `left` to `right` is valid. That's `(right - left + 1)` subarrays.

---

## The "Exactly K" Trick

Many problems ask for subarrays with **exactly k** of something. Direct sliding window won't work (can't maintain a valid window easily). The trick:

```
exactly(k) = atMost(k) - atMost(k - 1)
```

This is used in:
- **0992** — Subarrays with exactly K distinct integers
- Number of subarrays with exactly K odd numbers

---

## How to Build Intuition

1. **Ask: "Is the answer a contiguous range?"** → Candidate for sliding window
2. **Ask: "Can I expand the right pointer always?"** → Yes, for all subarrays
3. **Ask: "When do I shrink left?"** → When the window becomes invalid
4. **Define "valid" precisely** — this drives the entire logic
5. **Decide what to count/record** — min length? max length? total count?

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Forgetting to shrink when needed | Always check validity inside while loop |
| Off-by-one in window size | `right - left + 1` is the window size |
| Not removing element from map when freq = 0 | Always erase from map when count hits 0 |
| Wrong order of shrink vs. update answer | For min: update BEFORE shrinking. For max: update AFTER shrinking |

---

## Complexity

| | Time | Space |
|---|---|---|
| Sliding Window | O(n) | O(1) to O(k) |
| Brute Force | O(n²) | O(1) |

Each element is added once and removed once → total operations = 2n = **O(n)**.

---

## Problems in This Folder

| # | Problem | Pattern | Key Idea |
|---|---|---|---|
| 0076 | Minimum Window Substring | Min window | Shrink when all chars found |
| 0992 | Subarrays with K Distinct Integers | Count, exactly-k | `atMost(k) - atMost(k-1)` |
| 1358 | Substrings Containing All Three Characters | Count min windows | Shrink when all 3 found, add `n - right` |
| 3737 | Count Subarrays with Majority Element I | Brute-force O(n²) | Nested loops counting freq vs others |

---

## Interview Tips

- If you see **"at most"**, sliding window is almost always the answer
- If you see **"exactly"**, think `atMost(k) - atMost(k-1)`
- If you see **"minimum/maximum length"**, think shrinkable window
- Always confirm: is the data **monotonic** in some sense as you expand? (Required for window to work)
- Practice recognizing the "state" of a window — frequency map, sum, count of distinct, etc.
