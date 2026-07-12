# 🔢 Math & Strings

## What Is It?

**Math & Strings** problems require applying mathematical reasoning, number theory, or string manipulation to construct a solution — rather than relying on a standard data structure or algorithm pattern.

These problems test:
- Digit-level reasoning (breaking numbers into digits)
- Number properties (parity, divisibility, primes)
- String character operations (UPPER, LOWER, CONCAT, REPLACE)
- Greedy digit selection

---

## When to Use These Techniques

Signals in problems:
- "Integer" / "number" combined with digit operations
- "Maximize" / "minimize" a number by replacing digits
- String transformation (capitalize, reverse, format)
- No standard graph/tree/DP structure — purely mathematical logic
- Keywords: "digits", "replace", "concatenate", "maximize", "sum of digits"

---

## Core Digit Techniques

### Extracting Digits (Right to Left)
```cpp
while (n > 0) {
    int lastDigit = n % 10;  // extract last digit
    // process lastDigit
    n /= 10;                 // remove last digit
}
```

**To reconstruct a number from digits (reverse order):**
```cpp
ll result = 0;
ll place = 1;       // ones, tens, hundreds...
while (n > 0) {
    int d = n % 10;
    result += d * place;
    place *= 10;
    n /= 10;
}
// result = number with digits in original order
```

**Used in:** 3754 Concatenate Non-Zero Digits and Multiply by Sum

---

### Converting Integer to String (for digit manipulation)
```cpp
string s = to_string(num);

// Modify specific digits
for (char& c : s) {
    if (c == 'x') c = 'y';
}

int modified = stoi(s);
```

**Used in:** 1432 Max Difference from Changing Integer

---

### Greedy Digit Substitution
To **maximize** a number: find the leftmost digit that isn't 9, replace all occurrences of it with 9.

To **minimize** a number:
- If the first digit isn't 1 → replace all occurrences of first digit with 1
- Else find the leftmost digit (after position 0) that isn't 0 or 1 → replace all occurrences with 0

```cpp
string maximize(string s) {
    char target = 0;
    for (char c : s) {
        if (c != '9') { target = c; break; }
    }
    if (target)
        for (char& c : s)
            if (c == target) c = '9';
    return s;
}

string minimize(string s) {
    if (s[0] != '1') {
        char target = s[0];
        for (char& c : s) if (c == target) c = '1';
    } else {
        char target = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != '0' && s[i] != '1') { target = s[i]; break; }
        }
        if (target)
            for (char& c : s) if (c == target) c = '0';
    }
    return s;
}
```

**Used in:** 1432 Max Difference from Changing Integer

---

## Common String Operations (C++)

```cpp
string s = "hello";

s.size()                        // length
s.substr(start, len)            // substring
s[i]                            // character access
s += 'x'                        // append char
s += "xyz"                      // append string
to_string(42)                   // int → string
stoi("42")                      // string → int
stol, stoll                     // string → long, long long

// Character checks
isdigit(c)     // is '0'-'9'
isalpha(c)     // is letter
islower(c)     // is lowercase
isupper(c)     // is uppercase
tolower(c)     // convert to lowercase
toupper(c)     // convert to uppercase

// Find
s.find('x')                     // first occurrence
s.find("abc")                   // first occurrence of substring
s.rfind('x')                    // last occurrence

// Replace
s.replace(pos, len, "new")      // replace range
```

---

## Number Theory Patterns

### GCD and LCM
```cpp
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return (long long)a / gcd(a, b) * b; }

// C++17
#include <numeric>
__gcd(a, b);
```

### Prime Checking
```cpp
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; (long long)i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}
```

### Sieve of Eratosthenes (all primes up to n)
```cpp
vector<bool> sieve(n + 1, true);
sieve[0] = sieve[1] = false;
for (int i = 2; i * i <= n; i++)
    if (sieve[i])
        for (int j = i * i; j <= n; j += i)
            sieve[j] = false;
```

### Modular Arithmetic
```cpp
// Always keep values in range [0, MOD)
const int MOD = 1e9 + 7;
(a + b) % MOD
(a * b) % MOD
((a - b) % MOD + MOD) % MOD  // handle negative
```

---

## Digit DP
For problems counting numbers in range `[L, R]` with digit constraints:

```
f(n) = count of valid numbers in [0, n]
answer = f(R) - f(L - 1)

State: (position, tight constraint, other problem state)
```

This is an advanced DP pattern where the "problem" is about digit properties.

---

## Common Patterns Summary

| Pattern | When | Technique |
|---|---|---|
| Extract digits | Process individual digits | `n % 10`, `n /= 10` |
| Digit substitution | Maximize/minimize by replacing | `to_string()`, scan and replace |
| String rebuild | Construct result with conditions | `isdigit()`, `toupper()`, `tolower()` |
| Number theory | Primes, GCD, modular math | Sieve, Euclidean GCD |
| Digit concatenation | Build number from non-zero digits | Accumulate with `place *= 10` |

---

## How to Build Intuition

1. **Work with small examples first** — manually trace through a 3-4 digit number
2. **Think about digits separately** — what's the optimal choice for each digit position?
3. **Greedy from left to right** — most digit optimization problems are greedy (leftmost most significant)
4. **Use strings for digit manipulation** — easier than arithmetic in many cases
5. **Watch for overflow** — digit operations on 64-bit numbers can overflow `int`; use `long long`

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Integer overflow | Use `long long` / `typedef long long ll` |
| Modifying a copy not the original | Use `char&` in range-for: `for (char& c : s)` |
| Wrong digit order | Digits extracted right-to-left; reconstruct carefully |
| Edge case: all 9s | Check before attempting to find replacement digit |
| Leading zeros in minimization | Don't replace first digit with 0 |

---

## Complexity

These problems are usually **O(d)** where d = number of digits (log₁₀(n)), so effectively **O(log n)**. Very fast.

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 3754 | Concatenate Non-Zero Digits and Multiply by Sum | Digit extraction + reconstruction | Skip zeros; accumulate digit sum and digit-concatenated number in one pass using `place *= 10`; return `sum * x` |

---

## Interview Tips

- Math problems often have **elegant O(1) or O(log n)** solutions — avoid brute force
- Digit manipulation often converts to strings (`to_string`) — more readable code
- Greedy on digits: always act on the **leftmost** (most significant) digit first
- Know **GCD, LCM, modular exponentiation** — frequently needed as sub-steps
- Common math interview problems: Power of Two/Three, Reverse Integer, Palindrome Number, Happy Number, Count Primes
- String problems often combine multiple operations — write helper functions for clarity
