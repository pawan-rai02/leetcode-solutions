# 📦 Hash Map (Hash Table)

## What Is It?

A **Hash Map** (also called Hash Table, `unordered_map` in C++, `dict` in Python) is a data structure that stores **key-value pairs** and provides **O(1) average-time** lookup, insertion, and deletion.

It works by applying a **hash function** to the key to compute an index into an internal array (bucket).

```
Key  →  Hash Function  →  Bucket Index  →  Value
 5   →      h(5)       →       2        →   "five"
```

---

## When to Use It

Signals in problems:
- Need to **check existence** of an element quickly
- Need to **count frequencies** of elements
- Need to **find a complement** (e.g., `target - nums[i]`)
- Need to **group elements** by some property
- Brute force is O(n²) — a hash map can reduce to O(n)
- Keywords: "two sum", "pair", "duplicate", "frequency", "count", "anagram", "complement"

---

## Core Operations (C++)

```cpp
unordered_map<int, int> mp;

mp[key] = value;            // insert / update
mp[key]++;                  // increment count

mp.count(key);              // 1 if exists, 0 if not (O(1))
mp.find(key) != mp.end();   // same as above
mp[key];                    // access — creates with default 0 if not found!

mp.erase(key);              // remove

// iterate
for (auto& [k, v] : mp) { ... }
```

---

## Core Patterns

### Pattern 1 — Complement Lookup (Two Sum Pattern)
The most classic hash map pattern. Instead of checking all pairs O(n²), for each element, check if its complement already exists.

```cpp
unordered_map<int, int> mp;  // value → index

for (int i = 0; i < n; i++) {
    int complement = target - nums[i];
    
    if (mp.count(complement))
        return {i, mp[complement]};  // found pair!
    
    mp[nums[i]] = i;  // store for future lookups
}
```

**Key insight:** Instead of "for each i, for each j, check if i+j=target" (O(n²)),
you ask "for each i, does `target - nums[i]` already exist?" (O(n)).

**Used in:** 0001 Two Sum

---

### Pattern 2 — Frequency Counting
Count occurrences of each element, then use counts to make decisions.

```cpp
unordered_map<int, int> freq;
for (int x : nums) freq[x]++;

// Now use freq[x] to answer questions
for (auto& [val, count] : freq) {
    if (count > n / 2) return val;  // majority element
}
```

**Used in:** Majority Element, Top K Frequent, Anagram grouping

---

### Pattern 3 — HashMap + Math/Logic
Use the hash map to store counts, then apply mathematical logic.

```cpp
// 3020: Longest valid subset [x, x², x⁴, x⁸, ...]
unordered_map<ll, int> mp;
for (int x : nums) mp[x]++;

for (auto& [num, freq] : mp) {
    ll curr = num;
    int len = 0;
    while (mp.count(curr) && mp[curr] > 1) {
        len += 2;        // can include curr and curr (pair)
        curr = curr * curr;
    }
    // check if last element can appear once
    if (mp.count(curr)) len += 1;
    else len -= 1;        // reduce because no valid endpoint
    res = max(res, len);
}
```

**Used in:** 3020 Find Maximum Number of Elements in Subset

---

### Pattern 4 — HashMap as Set (existence only)
Use `unordered_set` when you only care about existence, not counts.

```cpp
unordered_set<int> seen;
for (int x : nums) {
    if (seen.count(x)) return true;  // duplicate!
    seen.insert(x);
}
```

**Used in:** Duplicate detection, longest consecutive sequence

---

## How to Build Intuition

1. **Ask: "Am I searching for something that depends on a previous element?"** → Hash map to cache seen elements
2. **Ask: "Do I need to count something?"** → Hash map as frequency table
3. **Ask: "Can I trade space for time?"** → Hash map gives O(1) lookup at the cost of O(n) space
4. **Think about what to store as the key** — the value being searched? The element? Its index?
5. **Think about what to store as the value** — index? frequency? some computed value?

---

## unordered_map vs map (C++)

| | `unordered_map` | `map` |
|---|---|---|
| Underlying structure | Hash table | Red-Black Tree |
| Lookup | O(1) average | O(log n) |
| Order | Unordered | Sorted by key |
| Use when | Speed matters | Sorted order needed |
| Worst case | O(n) (hash collision) | O(log n) guaranteed |

**Default choice:** Use `unordered_map` unless you need sorted order.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| `mp[key]` creates entry with 0 | Use `mp.count(key)` to check existence first |
| Using `map` when `unordered_map` is fine | Use `unordered_map` for O(1) average |
| Not erasing zero-count entries | Always `mp.erase(key)` when count reaches 0 (e.g., in sliding window) |
| Hash collision causing TLE | Use custom hash or `map` for safety in competitive programming |
| Storing wrong key/value | Clearly define what key and value represent before coding |

---

## Complexity

| Operation | `unordered_map` | `map` |
|---|---|---|
| Insert | O(1) avg | O(log n) |
| Lookup | O(1) avg | O(log n) |
| Delete | O(1) avg | O(log n) |
| Space | O(n) | O(n) |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0001 | Two Sum | Complement lookup | For each element, check if `target - nums[i]` was seen before |
| 3020 | Max Elements in Subset | Frequency + math | Count each value; greedily build chain `x → x² → x⁴ → ...` |

---

## Interview Tips

- Two Sum is the **canonical hash map problem** — know it cold
- HashMap is often the key to reducing O(n²) to O(n)
- Frequency maps appear in: anagrams, majority element, sliding window with distinct counts
- Know the difference between `unordered_map`, `unordered_set`, `map`, `set`
- When asked about duplicates, first instinct should be hash set
- For prefix sum problems, hash maps store `prefix_sum → first_index_seen`
- The "complement lookup" pattern generalizes: `target - x`, `target / x`, `target XOR x` — all use hash maps
