# Earliest Finish Time for Land And Water Rides II

# Intuition

We need to complete exactly one **land ride** and one **water ride**, and the rides can be taken in either order.

A naive approach would check every possible pair of rides and simulate both orders, resulting in a time complexity of **O(n × m)**, which is too slow for large inputs.

The key observation is that after finishing the first ride at time `t`, the second ride falls into one of two categories:

1. **Its start time is less than or equal to `t`**
   - The ride is already available.
   - We can start immediately at time `t`.
   - Finish time becomes:

   ```text
   t + duration
   ```

2. **Its start time is greater than `t`**
   - We must wait for the ride to open.
   - Finish time becomes:

   ```text
   startTime + duration
   ```

Instead of checking every ride individually, we sort rides by start time and preprocess:

- A **Prefix Minimum Duration** array.
- A **Suffix Minimum Finish-Time** array.

This allows us to determine the optimal second ride in logarithmic time using binary search.

Since the order can be:

- Land → Water
- Water → Land

we evaluate both possibilities and take the minimum result.

---

# Approach

### Step 1: Define a Reusable Solver

Create a helper function:

```text
solve(firstRideType, secondRideType)
```

that computes the earliest finish time when all rides of the first type are taken before rides of the second type.

---

### Step 2: Sort the Second Ride Group

For the second ride category:

1. Store `(startTime, duration)` pairs.
2. Sort them by start time.

This enables binary search on start times.

---

### Step 3: Build Prefix Minimum Duration Array

For every index:

```text
prefMinDur[i]
```

stores the minimum duration among all rides from:

```text
0 ... i
```

This helps when the second ride can start immediately.

---

### Step 4: Build Suffix Minimum Finish-Time Array

For every index:

```text
suffMinFinish[i]
```

stores:

```text
minimum(startTime + duration)
```

among rides from:

```text
i ... m-1
```

This helps when waiting is required.

---

### Step 5: Evaluate Every First Ride

For each ride in the first category:

1. Compute its finishing time:

   ```text
   t = startTime + duration
   ```

2. Use binary search to find the first ride whose start time is greater than `t`.

3. Consider two possibilities:

   **Immediate Start**

   ```text
   t + prefMinDur[pos - 1]
   ```

   **Wait For Future Ride**

   ```text
   suffMinFinish[pos]
   ```

4. Update the answer with the smaller value.

---

### Step 6: Check Both Orders

Run the solver twice:

```text
Land → Water
Water → Land
```

and return the minimum result.

---

# Why This Works

For any finishing time `t` of the first ride:

Every possible second ride belongs to exactly one of two groups.

### Group 1: startTime ≤ t

The ride is already available.

Its finish time is:

```text
t + duration
```

To minimize this value, we only need the smallest duration among all such rides.

The prefix minimum array provides this instantly.

---

### Group 2: startTime > t

The ride has not started yet.

Its finish time is:

```text
startTime + duration
```

To minimize this value, we only need the smallest future finish time.

The suffix minimum array provides this instantly.

---

Binary search separates these two groups efficiently, ensuring that every ride is processed in logarithmic time rather than scanning all rides.

Since both ride orders are evaluated, the globally earliest finishing time is guaranteed to be found.

---

# Complexity Analysis

Let:

```text
n = number of land rides
m = number of water rides
```

### Time Complexity

For each solver call:

- Sorting: `O(m log m)`
- Prefix preprocessing: `O(m)`
- Suffix preprocessing: `O(m)`
- Binary search for every ride: `O(n log m)`

Thus:

```text
solve = O(m log m + n log m)
```

Since we run it twice:

```text
O(m log m + n log m + n log n + m log n)
```

---

### Space Complexity

Additional arrays used:

- Sorted rides
- Start-time array
- Prefix minimum array
- Suffix minimum array

Overall:

```text
O(n + m)
```

---

# Code
```cpp []
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        auto solve = [&](vector<int>& s1, vector<int>& d1,
                         vector<int>& s2, vector<int>& d2) {
            int m = s2.size();
            vector<pair<int,int>> rides(m);
            for (int i = 0; i < m; i++) rides[i] = {s2[i], d2[i]};
            sort(rides.begin(), rides.end());

            vector<int> starts(m);
            vector<long long> prefMinDur(m), suffMinFinish(m);

            for (int i = 0; i < m; i++) starts[i] = rides[i].first;

            for (int i = 0; i < m; i++) {
                prefMinDur[i] = rides[i].second;
                if (i) prefMinDur[i] = min(prefMinDur[i], prefMinDur[i - 1]);
            }

            for (int i = m - 1; i >= 0; i--) {
                suffMinFinish[i] = 1LL * rides[i].first + rides[i].second;
                if (i + 1 < m) suffMinFinish[i] = min(suffMinFinish[i], suffMinFinish[i + 1]);
            }

            long long ans = LLONG_MAX;

            for (int i = 0; i < (int)s1.size(); i++) {
                long long t = 1LL * s1[i] + d1[i];
                int pos = upper_bound(starts.begin(), starts.end(), t) - starts.begin();

                if (pos > 0)
                    ans = min(ans, t + prefMinDur[pos - 1]);

                if (pos < m)
                    ans = min(ans, suffMinFinish[pos]);
            }

            return ans;
        };

        long long ans = min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        );

        return (int)ans;
    }
};
```
``` Java []
class Solution {
    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        long ans = Math.min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        );
        return (int) ans;
    }

    private long solve(int[] s1, int[] d1, int[] s2, int[] d2) {
        int m = s2.length;

        int[][] rides = new int[m][2];
        for (int i = 0; i < m; i++) {
            rides[i][0] = s2[i];
            rides[i][1] = d2[i];
        }

        Arrays.sort(rides, (a, b) -> Integer.compare(a[0], b[0]));

        int[] starts = new int[m];
        long[] prefMinDur = new long[m];
        long[] suffMinFinish = new long[m];

        for (int i = 0; i < m; i++) {
            starts[i] = rides[i][0];
        }

        for (int i = 0; i < m; i++) {
            prefMinDur[i] = rides[i][1];
            if (i > 0) prefMinDur[i] = Math.min(prefMinDur[i], prefMinDur[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            suffMinFinish[i] = (long) rides[i][0] + rides[i][1];
            if (i + 1 < m) {
                suffMinFinish[i] = Math.min(suffMinFinish[i], suffMinFinish[i + 1]);
            }
        }

        long ans = Long.MAX_VALUE;

        for (int i = 0; i < s1.length; i++) {
            long t = (long) s1[i] + d1[i];
            int pos = upperBound(starts, (int) t);

            if (pos > 0) {
                ans = Math.min(ans, t + prefMinDur[pos - 1]);
            }

            if (pos < m) {
                ans = Math.min(ans, suffMinFinish[pos]);
            }
        }

        return ans;
    }

    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] <= target) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
}
```
``` Python []
class Solution(object):
    def earliestFinishTime(self, landStartTime, landDuration, waterStartTime, waterDuration):
        def solve(s1, d1, s2, d2):
            rides = sorted(zip(s2, d2))
            m = len(rides)

            starts = [0] * m
            prefMinDur = [0] * m
            suffMinFinish = [0] * m

            for i in range(m):
                starts[i] = rides[i][0]

            for i in range(m):
                prefMinDur[i] = rides[i][1]
                if i > 0:
                    prefMinDur[i] = min(prefMinDur[i], prefMinDur[i - 1])

            for i in range(m - 1, -1, -1):
                suffMinFinish[i] = rides[i][0] + rides[i][1]
                if i + 1 < m:
                    suffMinFinish[i] = min(suffMinFinish[i], suffMinFinish[i + 1])

            ans = float('inf')

            for i in range(len(s1)):
                t = s1[i] + d1[i]

                l, r = 0, m
                while l < r:
                    mid = (l + r) // 2
                    if starts[mid] <= t:
                        l = mid + 1
                    else:
                        r = mid
                pos = l

                if pos > 0:
                    ans = min(ans, t + prefMinDur[pos - 1])

                if pos < m:
                    ans = min(ans, suffMinFinish[pos])

            return ans

        return min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        )
```
``` Javascript []
/**
 * @param {number[]} landStartTime
 * @param {number[]} landDuration
 * @param {number[]} waterStartTime
 * @param {number[]} waterDuration
 * @return {number}
 */
var earliestFinishTime = function(landStartTime, landDuration, waterStartTime, waterDuration) {

    function solve(s1, d1, s2, d2) {
        const m = s2.length;

        const rides = new Array(m);
        for (let i = 0; i < m; i++) {
            rides[i] = [s2[i], d2[i]];
        }

        rides.sort((a, b) => a[0] - b[0]);

        const starts = new Int32Array(m);
        const pref = new Int32Array(m);
        const suff = new Int32Array(m);

        starts[0] = rides[0][0];
        pref[0] = rides[0][1];

        for (let i = 1; i < m; i++) {
            starts[i] = rides[i][0];
            const d = rides[i][1];
            pref[i] = d < pref[i - 1] ? d : pref[i - 1];
        }

        suff[m - 1] = rides[m - 1][0] + rides[m - 1][1];

        for (let i = m - 2; i >= 0; i--) {
            const v = rides[i][0] + rides[i][1];
            suff[i] = v < suff[i + 1] ? v : suff[i + 1];
        }

        let ans = Number.MAX_SAFE_INTEGER;

        for (let i = 0, n = s1.length; i < n; i++) {
            const t = s1[i] + d1[i];

            let l = 0, r = m;
            while (l < r) {
                const mid = (l + r) >>> 1;
                if (starts[mid] <= t) l = mid + 1;
                else r = mid;
            }

            if (l) {
                const v = t + pref[l - 1];
                if (v < ans) ans = v;
            }

            if (l < m && suff[l] < ans) {
                ans = suff[l];
            }
        }

        return ans;
    }

    const a = solve(
        landStartTime,
        landDuration,
        waterStartTime,
        waterDuration
    );

    const b = solve(
        waterStartTime,
        waterDuration,
        landStartTime,
        landDuration
    );

    return a < b ? a : b;
};

```
``` C []
typedef struct {
    int start;
    int duration;
} Ride;

int compare(const void* a, const void* b) {
    return ((Ride*)a)->start - ((Ride*)b)->start;
}

int upperBound(int* arr, int n, long long target) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

long long solve(int* s1, int* d1, int n,
                int* s2, int* d2, int m) {
    Ride* rides = (Ride*)malloc(sizeof(Ride) * m);

    for (int i = 0; i < m; i++) {
        rides[i].start = s2[i];
        rides[i].duration = d2[i];
    }

    qsort(rides, m, sizeof(Ride), compare);

    int* starts = (int*)malloc(sizeof(int) * m);
    long long* pref = (long long*)malloc(sizeof(long long) * m);
    long long* suff = (long long*)malloc(sizeof(long long) * m);

    for (int i = 0; i < m; i++) {
        starts[i] = rides[i].start;
    }

    for (int i = 0; i < m; i++) {
        pref[i] = rides[i].duration;
        if (i > 0 && pref[i - 1] < pref[i]) {
            pref[i] = pref[i - 1];
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        suff[i] = (long long)rides[i].start + rides[i].duration;
        if (i + 1 < m && suff[i + 1] < suff[i]) {
            suff[i] = suff[i + 1];
        }
    }

    long long ans = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        long long t = (long long)s1[i] + d1[i];

        int pos = upperBound(starts, m, t);

        if (pos > 0) {
            long long v = t + pref[pos - 1];
            if (v < ans) ans = v;
        }

        if (pos < m && suff[pos] < ans) {
            ans = suff[pos];
        }
    }

    free(rides);
    free(starts);
    free(pref);
    free(suff);

    return ans;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize,
                       int* landDuration, int landDurationSize,
                       int* waterStartTime, int waterStartTimeSize,
                       int* waterDuration, int waterDurationSize) {

    long long a = solve(
        landStartTime, landDuration, landStartTimeSize,
        waterStartTime, waterDuration, waterStartTimeSize
    );

    long long b = solve(
        waterStartTime, waterDuration, waterStartTimeSize,
        landStartTime, landDuration, landStartTimeSize
    );

    return (int)(a < b ? a : b);
}
```

# Key Techniques Used

- Sorting
- Binary Search (Upper Bound)
- Prefix Minimum Array
- Suffix Minimum Array
- Greedy Optimization
- Two-Pass Evaluation
- Preprocessing for Fast Queries

```