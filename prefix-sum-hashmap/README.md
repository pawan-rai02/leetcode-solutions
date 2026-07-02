# ➕ Prefix Sum + Hash Map

## What Is It?

**Prefix Sum** is a technique where you precompute the cumulative sum of an array up to each index. Combined with a **Hash Map**, it allows you to answer range sum queries and count subarrays with specific sum properties in **O(n)** time.

```
Array:       [1, -1, 2, 3, -2]
Prefix Sums: [0,  1,  0, 2, 5,  3]  (index 0 is 0, representing empty prefix)
```

The key identity:
```
sum(i..j) = prefix[j+1] - prefix[i]
```

---

## When to Use It

Signals in problems:
- Asks for **count of subarrays** with a specific sum (or difference)
- The array contains **both positive and negative** numbers (sliding window fails here!)
- Keywords: "subarray sum equals k", "number of subarrays", "majority element count", "balance"
- You need to track **differences** in cumulative counts
- The brute force is O(n²) subarrays × O(n) sum check = O(n³)

---

## Core Idea

Instead of computing `sum(i..j)` for every pair, maintain a running prefix sum.

For subarray `[i+1..j]` to have sum = target:
```
prefixSum[j] - prefixSum[i] = target
→ prefixSum[i] = prefixSum[j] - target
```

So for every `j`, check: **"how many previous prefix sums equal `prefixSum[j] - target`?"**

That's a hash map lookup!

---

## Template

```cpp
unordered_map<int, int> mp;
mp[0] = 1;      // empty prefix (sum = 0) seen once — CRUCIAL

int prefixSum = 0;
int count = 0;

for (int j = 0; j < n; j++) {
    prefixSum += nums[j];
    
    // How many past prefixes give us a subarray summing to target?
    count += mp[prefixSum - target];
    
    mp[prefixSum]++;  // record this prefix sum
}

return count;
```

**Why `mp[0] = 1` at the start?**  
Because a subarray starting at index 0 with `prefixSum[j] == target` needs `prefixSum[i] = 0`. Without `mp[0] = 1`, this case would be missed.

---

## Applying This to Majority Element Counting

The trick for majority elements: transform the array into `+1` and `-1`.

For "subarrays where `target` is the majority element":
- Replace `nums[i]` with `+1` if `nums[i] == target`, else `-1`
- A subarray has `target` as majority when its sum > 0
- Equivalently: `prefixSum[j] > prefixSum[i]`, i.e., `prefixSum[j] - prefixSum[i] >= 1`

```cpp
unordered_map<int, int> mp;
int cumSum = 0;
mp[0] = 1;

ll validLeftPoints = 0;
ll res = 0;

for (int j = 0; j < n; j++) {
    if (nums[j] == target) {
        // cumSum about to increase: all previous prefix sums <= current sum
        // are now valid left boundaries
        validLeftPoints += mp[cumSum];  // cumSum before increment
        cumSum += 1;
    } else {
        cumSum -= 1;
        // cumSum decreased: the prefix sums that WERE valid left boundaries
        // are no longer valid (they're now equal to current sum)
        validLeftPoints -= mp[cumSum];  // cumSum after decrement
    }
    
    mp[cumSum]++;
    res += validLeftPoints;
}
```

**Used in:** 3739 Count Subarrays with Majority Element II  
**Intuition:** `validLeftPoints` tracks how many starting indices make a valid majority subarray ending at the current `j`.

---

## Pattern Variations

### Count subarrays with sum = k (Subarray Sum Equals K)
```cpp
unordered_map<int, int> mp;
mp[0] = 1;
int prefix = 0, count = 0;

for (int x : nums) {
    prefix += x;
    count += mp[prefix - k];  // subarrays ending here with sum = k
    mp[prefix]++;
}
return count;
```

### Count subarrays with sum divisible by k
```cpp
prefix = ((prefix % k) + k) % k;  // normalize to positive
count += mp[prefix];               // same remainder = divisible difference
mp[prefix]++;
```

### Longest subarray with sum = k
```cpp
unordered_map<int, int> firstSeen;  // prefix → first index seen
firstSeen[0] = -1;
int prefix = 0, maxLen = 0;

for (int i = 0; i < n; i++) {
    prefix += nums[i];
    if (firstSeen.count(prefix - k))
        maxLen = max(maxLen, i - firstSeen[prefix - k]);
    if (!firstSeen.count(prefix))
        firstSeen[prefix] = i;  // only store first occurrence
}
```

---

## How to Build Intuition

1. **Think about what "target" means in terms of prefix sums**
   - Sum = k → `prefix[j] - prefix[i] = k` → look for `prefix[i] = prefix[j] - k`
   - Sum > 0 (majority) → `prefix[j] > prefix[i]`

2. **The hash map is a frequency store of past prefix sums**
   - For each new `prefix[j]`, query: how many past `prefix[i]` values satisfy our condition?

3. **Always initialize `mp[0] = 1`** before processing

4. **Think about when to query vs. when to update**
   - Query FIRST, update AFTER (to avoid using current element as both endpoints)

---

## Prefix Sum vs Sliding Window

| Technique | When to Use |
|---|---|
| **Sliding Window** | All positive numbers, shrinkable window |
| **Prefix Sum + HashMap** | Mixed positive/negative, exact count needed |

If numbers are negative → sliding window fails (shrinking doesn't guarantee sum decreases) → use prefix sum.

---

## Complexity

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(n²) or O(n³) | O(1) |
| Prefix Sum + HashMap | O(n) | O(n) |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Forgetting `mp[0] = 1` | This handles subarrays starting from index 0 |
| Querying after updating | Always query `mp[prefix - k]` BEFORE doing `mp[prefix]++` |
| Integer overflow for large arrays | Use `long long` for cumulative sums |
| Wrong mod handling (negative modulo) | Use `((x % k) + k) % k` to normalize |
| Storing wrong thing in map | Key = prefix sum. Value = count (or first index for longest) |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 3739 | Count Subarrays with Majority Element II | +1/-1 transform + prefix sum | Map `target → +1`, else `→ -1`; count prefix sums where `prefix[j] > prefix[i]` using running `validLeftPoints` |

---

## Interview Tips

- **"Subarray Sum Equals K" (LC 560)** is the canonical problem — know it perfectly
- The `mp[0] = 1` initialization is always the first thing to write — don't forget it
- The query-before-update order matters — always query first
- For majority problems: the `+1/-1` transform is a classic trick
- Prefix sum + hashmap handles **negative numbers** which sliding window cannot
- This technique also applies to: XOR-based problems (replace sum with XOR), character frequency balance, 2D grids
- Know the distinction: count subarrays vs. length of longest subarray (different things to store in map)
