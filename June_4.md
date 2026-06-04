# Total Waviness of Numbers in Range I

## Intuition

When I first read this problem, the key insight is — **we don't need any fancy math or DP**. 

The constraint `num2 ≤ 10⁵` is the biggest hint. That's only 100,000 numbers, and each has at most **6 digits**. So the absolute worst case is `100,000 × 6 = 600,000` operations — that's nothing for a computer.

The moment you see small constraints like this, **don't overthink it**. A clean linear scan beats a complicated formula every time in interviews.

---

## What is Waviness? (Breaking it down for clarity)

Think of digits in a number like a **mountain range**:

```
Number: 1 8 3 9 2
Index:  0 1 2 3 4
            ↑   ↑
           peak peak  (8 > 1,3) and (9 > 3,2)
```

- **Peak** → middle digit is strictly greater than BOTH neighbors → like a mountain top
- **Valley** → middle digit is strictly less than BOTH neighbors → like a dip/trench
- **First and last digits are IGNORED** → no neighbors on both sides
- **Less than 3 digits → waviness is 0** → needs at least one "middle" digit

---

## Approach (Step by Step)

**Step 1:** Loop through every number from `num1` to `num2`.

**Step 2:** Convert the number to a string — this lets us access each digit by index cleanly without modular arithmetic tricks.

**Step 3:** Loop through only the **interior digits** (index `1` to `len-2`). Skip first and last — the problem tells us to.

**Step 4:** For each interior digit, check:
- Is it a **peak**? → `s[i] > s[i-1]` AND `s[i] > s[i+1]`
- Is it a **valley**? → `s[i] < s[i-1]` AND `s[i] < s[i+1]`

**Step 5:** If either is true, increment total.

> 💡 **Why string conversion?** Comparing characters `'0'-'9'` works perfectly since their ASCII values preserve numeric order. No need to extract digits with `% 10`.

---

## Dry Run

**Example:** `num1 = 198, num2 = 202`

| Number | Digits | Interior Check | Waviness |
|--------|--------|----------------|----------|
| 198 | 1, **9**, 8 | 9 > 1 and 9 > 8 → Peak ✅ | 1 |
| 199 | 1, **9**, 9 | 9 > 1 but 9 = 9 → Neither ❌ | 0 |
| 200 | 2, **0**, 0 | 0 < 2 but 0 = 0 → Neither ❌ | 0 |
| 201 | 2, **0**, 1 | 0 < 2 and 0 < 1 → Valley ✅ | 1 |
| 202 | 2, **0**, 2 | 0 < 2 and 0 < 2 → Valley ✅ | 1 |

**Total = 3 ✅**

---

## Complexity Analysis

| | Complexity | Reasoning |
|---|---|---|
| **Time** | $$O((num2 - num1) \times d)$$ | For each number, we scan at most `d` digits where `d ≤ 6` |
| **Space** | $$O(d)$$ | Only storing the digit string of current number, `d ≤ 6` |

Since `d` is a constant (max 6), this is effectively **O(n)** time and **O(1)** space.

---

## Common Mistakes to Avoid

- ❌ **Checking first/last digits** → Problem explicitly says they can never be peaks/valleys
- ❌ **Using `>=` instead of `>`** → The condition is **strictly** greater/less than
- ❌ **Off-by-one in loop bounds** → Loop from `i = 1` to `i < len - 1`, not `i < len`

---

## Code

```cpp []
class Solution {
public:
    int totalWaviness(int num1, int num2) {
        int total = 0;
        for (int n = num1; n <= num2; n++) {
            string s = to_string(n);
            int len = s.size();
            for (int i = 1; i < len - 1; i++) {
                if ((s[i] > s[i - 1] && s[i] > s[i + 1]) ||
                    (s[i] < s[i - 1] && s[i] < s[i + 1]))
                    total++;
            }
        }
        return total;
    }
};
```
```java []
class Solution {
    public int totalWaviness(int num1, int num2) {
        int total = 0;
        for (int n = num1; n <= num2; n++) {
            String s = Integer.toString(n);
            int len = s.length();
            for (int i = 1; i < len - 1; i++) {
                if ((s.charAt(i) > s.charAt(i-1) && s.charAt(i) > s.charAt(i+1)) ||
                    (s.charAt(i) < s.charAt(i-1) && s.charAt(i) < s.charAt(i+1)))
                    total++;
            }
        }
        return total;
    }
}
```
```python []
class Solution(object):
    def totalWaviness(self, num1, num2):
        total = 0
        for n in range(num1, num2 + 1):
            s = str(n)
            for i in range(1, len(s) - 1):
                if (s[i] > s[i-1] and s[i] > s[i+1]) or \
                   (s[i] < s[i-1] and s[i] < s[i+1]):
                    total += 1
        return total
```
```javascript []
var totalWaviness = function(num1, num2) {
    let total = 0;
    for (let n = num1; n <= num2; n++) {
        const s = String(n);
        for (let i = 1; i < s.length - 1; i++) {
            if ((s[i] > s[i-1] && s[i] > s[i+1]) ||
                (s[i] < s[i-1] && s[i] < s[i+1]))
                total++;
        }
    }
    return total;
};
```
```c []
int totalWaviness(int num1, int num2) {
    int total = 0;
    for (int n = num1; n <= num2; n++) {
        char s[7];
        sprintf(s, "%d", n);
        int len = strlen(s);
        for (int i = 1; i < len - 1; i++) {
            if ((s[i] > s[i-1] && s[i] > s[i+1]) ||
                (s[i] < s[i-1] && s[i] < s[i+1]))
                total++;
        }
    }
    return total;
}
```

---

> **Key Takeaway for Students:** Always check the constraints first. Small bounds (`≤ 10⁵`) are a green light for brute-force iteration. Readable, correct code always beats a clever but bug-prone solution.