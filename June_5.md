# Total waviness of Numbers in Range II

## Intuition

A number contributes to the **total waviness** whenever one of its digits becomes a local peak or local valley.

For any three consecutive digits:

- `a < b > c` → local peak
- `a > b < c` → local valley

Each occurrence increases the waviness by **1**.

A brute-force approach would evaluate every number in the range `[num1, num2]` and count its waviness individually. Since the range can be extremely large, this is computationally infeasible.

The key observation is that we don't need to enumerate every number. Instead, we can use **Digit DP** to count all valid numbers and simultaneously accumulate their total waviness contribution.

---

## Approach

### 1. Range Reduction

Define:

```cpp
F(n) = Total waviness of all numbers from 0 to n
```

Then:

```cpp
Answer = F(num2) - F(num1 - 1)
```

This transforms the problem into computing a prefix result.

---

### 2. Digit DP State

While building a number digit by digit, we maintain:

| State | Meaning |
|---------|---------|
| `pos` | Current digit position |
| `started` | Whether a non-leading-zero digit has appeared |
| `len` | Number of meaningful digits seen so far (0, 1, or ≥2) |
| `a` | Second-last digit |
| `b` | Last digit |
| `tight` | Whether current prefix is equal to the upper bound |

The DP returns:

```cpp
{
    count_of_numbers,
    total_waviness
}
```

---

### 3. Detecting a Wave

Once at least two previous digits exist, adding a new digit `d` forms:

```text
a  b  d
```

Digit `b` contributes one waviness if:

```cpp
(b > a && b > d) || (b < a && b < d)
```

which represents either:

- Local Maximum
- Local Minimum

---

### 4. DP Transition

For every possible next digit:

1. Extend the current state.
2. Recursively compute the remaining suffix.
3. If the new digit creates a wave, add:

```cpp
next.count * 1
```

because every number represented by that suffix inherits the newly formed wave.

---

### 5. Memoization

States with:

```cpp
tight == false
```

can be reused safely.

This reduces the complexity dramatically since the same digit configurations appear repeatedly.

---

## Why This Works

The DP processes every valid number up to `n` exactly once in a compressed state space.

For each digit insertion:

- all future completions are counted,
- waviness contributions are accumulated immediately,
- memoization avoids recomputation.

Thus every local peak/valley across all numbers is counted exactly once.

---

## Complexity Analysis

Let:

- `D = number of digits` (`≤ 19` for `long long`)

State count:

```text
D × 2 × 3 × 11 × 11
≈ 13,794 states
```

Each state tries at most:

```text
10 digits
```

### Time Complexity

```text
O(D × 2 × 3 × 11 × 11 × 10)
≈ O(10^4)
```

### Space Complexity

```text
O(D × 2 × 3 × 11 × 11)
≈ O(10^4)
```

Both are easily within limits.

---
# Code:
```cpp []
class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node dp[20][2][3][11][11];
    bool vis[20][2][3][11][11];

    Node dfs(int pos, bool started, int len, int a, int b, bool tight) {
        if (pos == (int)s.size()) return {1, 0};

        if (vis[pos][started][len][a][b] && !tight)
            return dp[pos][started][len][a][b];

        int lim = tight ? s[pos] - '0' : 9;
        Node res{0, 0};

        for (int d = 0; d <= lim; d++) {
            bool ntight = tight && (d == lim);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, false, 0, 10, 10, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                if (!started) {
                    Node nxt = dfs(pos + 1, true, 1, 10, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else if (len == 1) {
                    Node nxt = dfs(pos + 1, true, 2, b, d, ntight);
                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav;
                } else {
                    int add =
                        ((b > a && b > d) || (b < a && b < d));

                    Node nxt = dfs(pos + 1, true, 2, b, d, ntight);

                    res.cnt += nxt.cnt;
                    res.wav += nxt.wav + nxt.cnt * add;
                }
            }
        }

        if (!tight) {
            vis[pos][started][len][a][b] = true;
            dp[pos][started][len][a][b] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n < 0) return 0;

        memset(vis, 0, sizeof(vis));
        s = to_string(n);

        return dfs(0, false, 0, 10, 10, true).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
```
```java []
class Solution {
    static class Node {
        long cnt;
        long wav;

        Node(long cnt, long wav) {
            this.cnt = cnt;
            this.wav = wav;
        }
    }

    String s;
    Node[][][][][] dp;
    boolean[][][][][] vis;

    private Node dfs(int pos, int started, int len, int a, int b, boolean tight) {
        if (pos == s.length()) {
            return new Node(1, 0);
        }

        if (!tight && vis[pos][started][len][a][b]) {
            return dp[pos][started][len][a][b];
        }

        int limit = tight ? s.charAt(pos) - '0' : 9;
        long totalCnt = 0;
        long totalWav = 0;

        for (int d = 0; d <= limit; d++) {
            boolean nextTight = tight && (d == limit);

            if (started == 0 && d == 0) {
                Node nxt = dfs(pos + 1, 0, 0, 10, 10, nextTight);
                totalCnt += nxt.cnt;
                totalWav += nxt.wav;
            } else {
                if (started == 0) {
                    Node nxt = dfs(pos + 1, 1, 1, 10, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav;
                } else if (len == 1) {
                    Node nxt = dfs(pos + 1, 1, 2, b, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav;
                } else {
                    int add = ((b > a && b > d) || (b < a && b < d)) ? 1 : 0;
                    Node nxt = dfs(pos + 1, 1, 2, b, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav + nxt.cnt * add;
                }
            }
        }

        Node res = new Node(totalCnt, totalWav);

        if (!tight) {
            vis[pos][started][len][a][b] = true;
            dp[pos][started][len][a][b] = res;
        }

        return res;
    }

    private long solve(long n) {
        if (n < 0) return 0;

        s = Long.toString(n);
        int m = s.length();

        dp = new Node[m + 1][2][3][11][11];
        vis = new boolean[m + 1][2][3][11][11];

        return dfs(0, 0, 0, 10, 10, true).wav;
    }

    public long totalWaviness(long num1, long num2) {
        return solve(num2) - solve(num1 - 1);
    }
}
```
```python []
class Solution(object):
    def totalWaviness(self, num1, num2):
        def solve(n):
            if n < 0:
                return 0

            s = str(n)
            memo = {}

            def dfs(pos, started, length, a, b, tight):
                if pos == len(s):
                    return (1, 0)

                if not tight:
                    key = (pos, started, length, a, b)
                    if key in memo:
                        return memo[key]

                limit = int(s[pos]) if tight else 9
                total_cnt = 0
                total_wav = 0

                for d in range(limit + 1):
                    ntight = tight and (d == limit)

                    if not started and d == 0:
                        cnt, wav = dfs(pos + 1, False, 0, 10, 10, ntight)
                        total_cnt += cnt
                        total_wav += wav
                    else:
                        if not started:
                            cnt, wav = dfs(pos + 1, True, 1, 10, d, ntight)
                            total_cnt += cnt
                            total_wav += wav
                        elif length == 1:
                            cnt, wav = dfs(pos + 1, True, 2, b, d, ntight)
                            total_cnt += cnt
                            total_wav += wav
                        else:
                            add = 1 if ((b > a and b > d) or (b < a and b < d)) else 0
                            cnt, wav = dfs(pos + 1, True, 2, b, d, ntight)
                            total_cnt += cnt
                            total_wav += wav + cnt * add

                res = (total_cnt, total_wav)

                if not tight:
                    memo[(pos, started, length, a, b)] = res

                return res

            return dfs(0, False, 0, 10, 10, True)[1]

        return solve(num2) - solve(num1 - 1)
```
```javascript []
var totalWaviness = function (num1, num2) {
  const solve = (n) => {
    if (n < 0) return 0;

    const s = n.toString();
    const memo = new Map();

    const dfs = (pos, started, len, a, b, tight) => {
      if (pos === s.length) {
        return [1n, 0n];
      }

      const key = `${pos},${started},${len},${a},${b}`;

      if (!tight && memo.has(key)) {
        return memo.get(key);
      }

      const limit = tight ? Number(s[pos]) : 9;

      let totalCnt = 0n;
      let totalWav = 0n;

      for (let d = 0; d <= limit; d++) {
        const nextTight = tight && d === limit;

        if (!started && d === 0) {
          const [cnt, wav] = dfs(pos + 1, false, 0, 10, 10, nextTight);
          totalCnt += cnt;
          totalWav += wav;
        } else {
          if (!started) {
            const [cnt, wav] = dfs(pos + 1, true, 1, 10, d, nextTight);
            totalCnt += cnt;
            totalWav += wav;
          } else if (len === 1) {
            const [cnt, wav] = dfs(pos + 1, true, 2, b, d, nextTight);
            totalCnt += cnt;
            totalWav += wav;
          } else {
            const add = (b > a && b > d) || (b < a && b < d) ? 1n : 0n;

            const [cnt, wav] = dfs(pos + 1, true, 2, b, d, nextTight);

            totalCnt += cnt;
            totalWav += wav + cnt * add;
          }
        }
      }

      const res = [totalCnt, totalWav];

      if (!tight) {
        memo.set(key, res);
      }

      return res;
    };

    return dfs(0, false, 0, 10, 10, true)[1];
  };

  return Number(solve(num2) - solve(num1 - 1));
};

```
```c []
typedef struct {
    long long cnt;
    long long wav;
} Node;

char s[25];
Node dp[20][2][3][11][11];
char vis[20][2][3][11][11];

Node dfs(int pos, int started, int len, int a, int b, int tight) {
    if (s[pos] == '\0') {
        Node res = {1, 0};
        return res;
    }

    if (!tight && vis[pos][started][len][a][b]) {
        return dp[pos][started][len][a][b];
    }

    int limit = tight ? (s[pos] - '0') : 9;

    Node res = {0, 0};

    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == limit);

        if (!started && d == 0) {
            Node nxt = dfs(pos + 1, 0, 0, 10, 10, ntight);
            res.cnt += nxt.cnt;
            res.wav += nxt.wav;
        } else {
            if (!started) {
                Node nxt = dfs(pos + 1, 1, 1, 10, d, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else if (len == 1) {
                Node nxt = dfs(pos + 1, 1, 2, b, d, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                int add = ((b > a && b > d) || (b < a && b < d));

                Node nxt = dfs(pos + 1, 1, 2, b, d, ntight);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + nxt.cnt * add;
            }
        }
    }

    if (!tight) {
        vis[pos][started][len][a][b] = 1;
        dp[pos][started][len][a][b] = res;
    }

    return res;
}

long long solve(long long n) {
    if (n < 0) return 0;

    memset(vis, 0, sizeof(vis));
    sprintf(s, "%lld", n);

    return dfs(0, 0, 0, 10, 10, 1).wav;
}

long long totalWaviness(long long num1, long long num2) {
    return solve(num2) - solve(num1 - 1);
}
```

---

### Key Takeaway

This problem is a classic example of **Digit DP with aggregated statistics**. Instead of merely counting numbers, the DP simultaneously tracks:

- how many numbers can be formed,
- how much waviness those numbers contribute.

This technique is broadly applicable to problems involving digit properties over very large ranges.
```