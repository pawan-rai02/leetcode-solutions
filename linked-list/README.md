# 🔗 Linked List

> **Subtopic of:** Heap / Priority Queue  
> Problems here also appear in their primary topic folder.

---

## What Is It?

A **Linked List** is a linear data structure where each element (**node**) stores a **value** and a **pointer to the next node**. Unlike arrays, nodes are not stored contiguously in memory.

```
Singly Linked List:
  1 → 2 → 3 → 4 → 5 → null

Doubly Linked List:
null ← 1 ↔ 2 ↔ 3 ↔ 4 ↔ 5 → null
```

---

## Key Properties

| Property | Linked List | Array |
|---|---|---|
| Access by index | O(n) | O(1) |
| Insert at head | O(1) | O(n) |
| Insert at tail | O(n) (or O(1) with tail ptr) | O(1) amortized |
| Insert in middle | O(1) after finding position | O(n) |
| Delete | O(1) after finding position | O(n) |
| Memory | Dynamic, scattered | Contiguous |

---

## LeetCode Node Definition

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

---

## Core Operations

### Traverse
```cpp
ListNode* curr = head;
while (curr) {
    // process curr->val
    curr = curr->next;
}
```

### Insert at Head
```cpp
ListNode* newNode = new ListNode(val);
newNode->next = head;
head = newNode;
```

### Insert at Tail
```cpp
ListNode* curr = head;
while (curr->next) curr = curr->next;
curr->next = new ListNode(val);
```

### Delete a Node (given previous)
```cpp
prev->next = prev->next->next;
```

### Reverse a Linked List
```cpp
ListNode* prev = nullptr, *curr = head;
while (curr) {
    ListNode* nextNode = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextNode;
}
return prev;  // new head
```

---

## The Dummy Head Trick

When operations might change the head, use a **dummy node** to simplify edge cases:

```cpp
ListNode dummy(0);
dummy.next = head;
ListNode* curr = &dummy;

// ... do operations ...

return dummy.next;  // actual head (might have changed)
```

**Used in:** Merge Two Lists, Remove Nth from End, etc.

---

## Fast & Slow Pointer (Floyd's)

Use two pointers at different speeds to solve many linked list problems:

```cpp
ListNode* slow = head;
ListNode* fast = head;

while (fast && fast->next) {
    slow = slow->next;       // moves 1 step
    fast = fast->next->next; // moves 2 steps
}
// When fast reaches end, slow is at middle
```

**Use cases:**
- **Middle of list** — `slow` lands at middle when `fast` hits end
- **Cycle detection** — if they ever meet, there's a cycle
- **Cycle start** — reset `slow` to head, move both 1 step; where they meet = cycle start

---

## Merge K Sorted Lists (Heap + Linked List)

This problem combines **Linked List traversal** with a **Min-Heap** to efficiently pick the next smallest node.

```cpp
// Min-heap ordered by node value
priority_queue<ListNode*, vector<ListNode*>, 
               [](ListNode* a, ListNode* b){ return a->val > b->val; }> pq;

// Push all list heads
for (auto list : lists)
    if (list) pq.push(list);

ListNode dummy(0);
ListNode* curr = &dummy;

while (!pq.empty()) {
    auto node = pq.top(); pq.pop();
    curr->next = node;
    curr = curr->next;
    if (node->next) pq.push(node->next);  // push the next from same list
}

return dummy.next;
```

**Time:** O(N log k) — N total nodes, k lists  
**Space:** O(k) — heap stores at most one node per list  
**Used in:** 0023 Merge K Sorted Lists

---

## Common Linked List Patterns

| Pattern | Problem | Technique |
|---|---|---|
| Reverse | Reverse Linked List | Three-pointer (prev, curr, next) |
| Find middle | Middle of Linked List | Fast & slow pointers |
| Cycle detection | Linked List Cycle | Fast & slow — if they meet |
| Merge sorted lists | Merge Two Sorted Lists | Two pointers + dummy head |
| Merge K sorted lists | Merge K Sorted Lists | Min-heap |
| Nth from end | Remove Nth From End | Two pointers (gap of N) |
| Palindrome check | Palindrome Linked List | Find middle + reverse second half |
| Intersection | Intersection of Two Linked Lists | Align lengths or two-pass |

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| Losing track of next before modifying | Always `ListNode* nxt = curr->next` before changing `curr->next` |
| Off-by-one in removal | Use dummy head or track previous node |
| Null pointer dereference | Check `if (curr && curr->next)` before accessing |
| Not handling empty list | First check `if (!head) return head` |
| Forgetting to null-terminate | After operations, ensure last node's `next = nullptr` |

---

## Complexity Reference

| Operation | Singly LL | Doubly LL |
|---|---|---|
| Access | O(n) | O(n) |
| Insert head | O(1) | O(1) |
| Insert tail | O(n) / O(1) with tail | O(1) with tail |
| Delete head | O(1) | O(1) |
| Delete tail | O(n) | O(1) |
| Search | O(n) | O(n) |

---

## Problems in This Folder

| # | Problem | Pattern | Key Insight |
|---|---|---|---|
| 0023 | Merge K Sorted Lists | Min-Heap + Linked List | Push all k heads into min-heap; always pick smallest; push that node's successor |
