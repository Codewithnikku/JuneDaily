
# Earliest Finish Time for Land And Water Rides I

# Intuition

We need to complete exactly one **land ride** and one **water ride** in any order while minimizing the final finishing time.

A brute-force solution would try every possible pair of land and water rides, resulting in **O(n × m)** complexity, which is too slow for large inputs.

The key observation is that after finishing the first ride at time `x`, the second ride can fall into one of two categories:

1. Its start time is **≤ x**, so we can begin it immediately at time `x`.
2. Its start time is **> x**, so we must wait until its start time.

For a ride with start time `s` and duration `d`:

- If `s ≤ x`, finish time becomes `x + d`.
- If `s > x`, finish time becomes `s + d`.

To efficiently find the best second ride for every first ride, we sort rides by start time and precompute:

- **Prefix minimum duration** → best ride that can start immediately.
- **Suffix minimum (start + duration)** → best ride that requires waiting.

Using binary search, we can quickly determine which rides belong to each category and compute the optimal finishing time.

Since the order can be either:

- Land → Water
- Water → Land

we evaluate both directions and take the minimum answer.

---

# Approach

### Phase 1: Process Water Rides

1. Create pairs `(startTime, duration)` for all water rides.
2. Sort them by start time.
3. Build:
   - `wPref[i]` = minimum duration among rides from `0...i`.
   - `wSuff[i]` = minimum `(start + duration)` among rides from `i...m-1`.

These arrays allow us to instantly determine the best water ride after completing a land ride.

---

### Phase 2: Try Land → Water

For every land ride:

1. Compute its finishing time:

   ```text
   x = landStartTime + landDuration
   ```

2. Use binary search to find the last water ride whose start time is ≤ `x`.

3. Two possibilities exist:

   - Start immediately:
     
     ```text
     x + minimumDuration
     ```

   - Wait for a future ride:
     
     ```text
     minimum(start + duration)
     ```

4. Take the minimum of these two values.

---

### Phase 3: Process Land Rides

Repeat the same preprocessing for land rides:

- Sort by start time.
- Build prefix minimum duration array.
- Build suffix minimum finish-time array.

---

### Phase 4: Try Water → Land

For every water ride:

1. Compute when it finishes.
2. Binary search over land rides.
3. Evaluate:
   - Immediate start case.
   - Waiting case.
4. Update the global minimum answer.

---

# Why This Works

For any finishing time `x` of the first ride:

Every possible second ride must belong to exactly one of two groups:

### Case 1: Start Time ≤ x

The ride is already available when we finish the first ride.

Its finish time is:

```text
x + duration
```

To minimize this value, we only need the smallest duration among all such rides.

This is precisely what the prefix minimum array stores.

---

### Case 2: Start Time > x

We must wait until the ride becomes available.

Its finish time is:

```text
start + duration
```

To minimize this value, we only need the smallest `(start + duration)` among future rides.

This is exactly what the suffix minimum array provides.

---

Since binary search separates these two groups efficiently, every ride is evaluated optimally in logarithmic time.

Checking both possible orders guarantees that the globally earliest finish time is found.

---

# Complexity Analysis

Let:

- `n` = number of land rides
- `m` = number of water rides

### Time Complexity

- Sorting land rides: `O(n log n)`
- Sorting water rides: `O(m log m)`
- Binary search for each land ride: `O(n log m)`
- Binary search for each water ride: `O(m log n)`

Overall:

```text
O(n log n + m log m + n log m + m log n)
```

---

### Space Complexity

Additional arrays used:

- Prefix minimum arrays
- Suffix minimum arrays
- Sorted ride containers

Overall:

```text
O(n + m)
```
# Code: 
 ```cpp []
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        long long ans = LLONG_MAX;

        int m = waterStartTime.size();
        vector<pair<int, int>> water(m);
        for (int i = 0; i < m; i++) water[i] = {waterStartTime[i], waterDuration[i]};
        sort(water.begin(), water.end());

        vector<int> wStart(m);
        vector<long long> wPref(m), wSuff(m);

        for (int i = 0; i < m; i++) {
            wStart[i] = water[i].first;
            wPref[i] = water[i].second;
            if (i) wPref[i] = min(wPref[i], wPref[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            wSuff[i] = 1LL * water[i].first + water[i].second;
            if (i + 1 < m) wSuff[i] = min(wSuff[i], wSuff[i + 1]);
        }

        for (int i = 0; i < (int)landStartTime.size(); i++) {
            long long x = 1LL * landStartTime[i] + landDuration[i];
            int p = upper_bound(wStart.begin(), wStart.end(), x) - wStart.begin() - 1;

            long long cur = LLONG_MAX;
            if (p >= 0) cur = min(cur, x + wPref[p]);
            if (p + 1 < m) cur = min(cur, wSuff[p + 1]);

            ans = min(ans, cur);
        }

        int n = landStartTime.size();
        vector<pair<int, int>> land(n);
        for (int i = 0; i < n; i++) land[i] = {landStartTime[i], landDuration[i]};
        sort(land.begin(), land.end());

        vector<int> lStart(n);
        vector<long long> lPref(n), lSuff(n);

        for (int i = 0; i < n; i++) {
            lStart[i] = land[i].first;
            lPref[i] = land[i].second;
            if (i) lPref[i] = min(lPref[i], lPref[i - 1]);
        }

        for (int i = n - 1; i >= 0; i--) {
            lSuff[i] = 1LL * land[i].first + land[i].second;
            if (i + 1 < n) lSuff[i] = min(lSuff[i], lSuff[i + 1]);
        }

        for (int j = 0; j < (int)waterStartTime.size(); j++) {
            long long x = 1LL * waterStartTime[j] + waterDuration[j];
            int p = upper_bound(lStart.begin(), lStart.end(), x) - lStart.begin() - 1;

            long long cur = LLONG_MAX;
            if (p >= 0) cur = min(cur, x + lPref[p]);
            if (p + 1 < n) cur = min(cur, lSuff[p + 1]);

            ans = min(ans, cur);
        }

        return (int)ans;
    }
};

```
```java []
class Solution {
    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        long ans = Long.MAX_VALUE;

        int m = waterStartTime.length;
        int[][] water = new int[m][2];
        for (int i = 0; i < m; i++) {
            water[i][0] = waterStartTime[i];
            water[i][1] = waterDuration[i];
        }

        java.util.Arrays.sort(water, (a, b) -> Integer.compare(a[0], b[0]));

        int[] wStart = new int[m];
        long[] wPref = new long[m];
        long[] wSuff = new long[m];

        for (int i = 0; i < m; i++) {
            wStart[i] = water[i][0];
            wPref[i] = water[i][1];
            if (i > 0) wPref[i] = Math.min(wPref[i], wPref[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            wSuff[i] = (long) water[i][0] + water[i][1];
            if (i + 1 < m) wSuff[i] = Math.min(wSuff[i], wSuff[i + 1]);
        }

        for (int i = 0; i < landStartTime.length; i++) {
            long x = (long) landStartTime[i] + landDuration[i];
            int p = upperBound(wStart, (int) x) - 1;

            long cur = Long.MAX_VALUE;
            if (p >= 0) cur = Math.min(cur, x + wPref[p]);
            if (p + 1 < m) cur = Math.min(cur, wSuff[p + 1]);

            ans = Math.min(ans, cur);
        }

        int n = landStartTime.length;
        int[][] land = new int[n][2];
        for (int i = 0; i < n; i++) {
            land[i][0] = landStartTime[i];
            land[i][1] = landDuration[i];
        }

        java.util.Arrays.sort(land, (a, b) -> Integer.compare(a[0], b[0]));

        int[] lStart = new int[n];
        long[] lPref = new long[n];
        long[] lSuff = new long[n];

        for (int i = 0; i < n; i++) {
            lStart[i] = land[i][0];
            lPref[i] = land[i][1];
            if (i > 0) lPref[i] = Math.min(lPref[i], lPref[i - 1]);
        }

        for (int i = n - 1; i >= 0; i--) {
            lSuff[i] = (long) land[i][0] + land[i][1];
            if (i + 1 < n) lSuff[i] = Math.min(lSuff[i], lSuff[i + 1]);
        }

        for (int i = 0; i < waterStartTime.length; i++) {
            long x = (long) waterStartTime[i] + waterDuration[i];
            int p = upperBound(lStart, (int) x) - 1;

            long cur = Long.MAX_VALUE;
            if (p >= 0) cur = Math.min(cur, x + lPref[p]);
            if (p + 1 < n) cur = Math.min(cur, lSuff[p + 1]);

            ans = Math.min(ans, cur);
        }

        return (int) ans;
    }

    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = (l + r) >>> 1;
            if (arr[mid] <= target) l = mid + 1;
            else r = mid;
        }
        return l;
    }
}
```
```python []
from bisect import bisect_right

class Solution(object):
    def earliestFinishTime(self, landStartTime, landDuration, waterStartTime, waterDuration):
        ans = float('inf')

        water = sorted(zip(waterStartTime, waterDuration))
        m = len(water)

        wStart = [0] * m
        wPref = [0] * m
        wSuff = [0] * m

        for i in range(m):
            wStart[i] = water[i][0]
            wPref[i] = water[i][1]
            if i:
                wPref[i] = min(wPref[i], wPref[i - 1])

        for i in range(m - 1, -1, -1):
            wSuff[i] = water[i][0] + water[i][1]
            if i + 1 < m:
                wSuff[i] = min(wSuff[i], wSuff[i + 1])

        for s, d in zip(landStartTime, landDuration):
            x = s + d
            p = bisect_right(wStart, x) - 1

            cur = float('inf')
            if p >= 0:
                cur = min(cur, x + wPref[p])
            if p + 1 < m:
                cur = min(cur, wSuff[p + 1])

            ans = min(ans, cur)

        land = sorted(zip(landStartTime, landDuration))
        n = len(land)

        lStart = [0] * n
        lPref = [0] * n
        lSuff = [0] * n

        for i in range(n):
            lStart[i] = land[i][0]
            lPref[i] = land[i][1]
            if i:
                lPref[i] = min(lPref[i], lPref[i - 1])

        for i in range(n - 1, -1, -1):
            lSuff[i] = land[i][0] + land[i][1]
            if i + 1 < n:
                lSuff[i] = min(lSuff[i], lSuff[i + 1])

        for s, d in zip(waterStartTime, waterDuration):
            x = s + d
            p = bisect_right(lStart, x) - 1

            cur = float('inf')
            if p >= 0:
                cur = min(cur, x + lPref[p])
            if p + 1 < n:
                cur = min(cur, lSuff[p + 1])

            ans = min(ans, cur)

        return int(ans)
```
```javascript []
/**
 * @param {number[]} landStartTime
 * @param {number[]} landDuration
 * @param {number[]} waterStartTime
 * @param {number[]} waterDuration
 * @return {number}
 */
var earliestFinishTime = function(landStartTime, landDuration, waterStartTime, waterDuration) {
    let ans = Infinity;

    const water = waterStartTime.map((s, i) => [s, waterDuration[i]]);
    water.sort((a, b) => a[0] - b[0]);

    const m = water.length;
    const wStart = new Array(m);
    const wPref = new Array(m);
    const wSuff = new Array(m);

    for (let i = 0; i < m; i++) {
        wStart[i] = water[i][0];
        wPref[i] = water[i][1];
        if (i) wPref[i] = Math.min(wPref[i], wPref[i - 1]);
    }

    for (let i = m - 1; i >= 0; i--) {
        wSuff[i] = water[i][0] + water[i][1];
        if (i + 1 < m) wSuff[i] = Math.min(wSuff[i], wSuff[i + 1]);
    }

    for (let i = 0; i < landStartTime.length; i++) {
        const x = landStartTime[i] + landDuration[i];
        let l = 0, r = m;

        while (l < r) {
            const mid = (l + r) >> 1;
            if (wStart[mid] <= x) l = mid + 1;
            else r = mid;
        }

        const p = l - 1;
        let cur = Infinity;

        if (p >= 0) cur = Math.min(cur, x + wPref[p]);
        if (p + 1 < m) cur = Math.min(cur, wSuff[p + 1]);

        ans = Math.min(ans, cur);
    }

    const land = landStartTime.map((s, i) => [s, landDuration[i]]);
    land.sort((a, b) => a[0] - b[0]);

    const n = land.length;
    const lStart = new Array(n);
    const lPref = new Array(n);
    const lSuff = new Array(n);

    for (let i = 0; i < n; i++) {
        lStart[i] = land[i][0];
        lPref[i] = land[i][1];
        if (i) lPref[i] = Math.min(lPref[i], lPref[i - 1]);
    }

    for (let i = n - 1; i >= 0; i--) {
        lSuff[i] = land[i][0] + land[i][1];
        if (i + 1 < n) lSuff[i] = Math.min(lSuff[i], lSuff[i + 1]);
    }

    for (let i = 0; i < waterStartTime.length; i++) {
        const x = waterStartTime[i] + waterDuration[i];
        let l = 0, r = n;

        while (l < r) {
            const mid = (l + r) >> 1;
            if (lStart[mid] <= x) l = mid + 1;
            else r = mid;
        }

        const p = l - 1;
        let cur = Infinity;

        if (p >= 0) cur = Math.min(cur, x + lPref[p]);
        if (p + 1 < n) cur = Math.min(cur, lSuff[p + 1]);

        ans = Math.min(ans, cur);
    }

    return ans;
};
```
```C []
typedef struct {
    int start;
    int duration;
} Ride;

int cmp(const void *a, const void *b) {
    return ((Ride *)a)->start - ((Ride *)b)->start;
}

int upperBound(int *arr, int n, int target) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target) l = mid + 1;
        else r = mid;
    }
    return l;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize, int* landDuration, int landDurationSize, int* waterStartTime, int waterStartTimeSize, int* waterDuration, int waterDurationSize) {
    long long ans = (long long)1e18;

    int m = waterStartTimeSize;
    Ride *water = malloc(m * sizeof(Ride));

    for (int i = 0; i < m; i++) {
        water[i].start = waterStartTime[i];
        water[i].duration = waterDuration[i];
    }

    qsort(water, m, sizeof(Ride), cmp);

    int *wStart = malloc(m * sizeof(int));
    long long *wPref = malloc(m * sizeof(long long));
    long long *wSuff = malloc(m * sizeof(long long));

    for (int i = 0; i < m; i++) {
        wStart[i] = water[i].start;
        wPref[i] = water[i].duration;
        if (i) wPref[i] = wPref[i] < wPref[i - 1] ? wPref[i] : wPref[i - 1];
    }

    for (int i = m - 1; i >= 0; i--) {
        wSuff[i] = (long long)water[i].start + water[i].duration;
        if (i + 1 < m) wSuff[i] = wSuff[i] < wSuff[i + 1] ? wSuff[i] : wSuff[i + 1];
    }

    for (int i = 0; i < landStartTimeSize; i++) {
        long long x = (long long)landStartTime[i] + landDuration[i];
        int p = upperBound(wStart, m, (int)x) - 1;

        long long cur = (long long)1e18;
        if (p >= 0) cur = x + wPref[p];
        if (p + 1 < m && wSuff[p + 1] < cur) cur = wSuff[p + 1];

        if (cur < ans) ans = cur;
    }

    int n = landStartTimeSize;
    Ride *land = malloc(n * sizeof(Ride));

    for (int i = 0; i < n; i++) {
        land[i].start = landStartTime[i];
        land[i].duration = landDuration[i];
    }

    qsort(land, n, sizeof(Ride), cmp);

    int *lStart = malloc(n * sizeof(int));
    long long *lPref = malloc(n * sizeof(long long));
    long long *lSuff = malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        lStart[i] = land[i].start;
        lPref[i] = land[i].duration;
        if (i) lPref[i] = lPref[i] < lPref[i - 1] ? lPref[i] : lPref[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        lSuff[i] = (long long)land[i].start + land[i].duration;
        if (i + 1 < n) lSuff[i] = lSuff[i] < lSuff[i + 1] ? lSuff[i] : lSuff[i + 1];
    }

    for (int i = 0; i < waterStartTimeSize; i++) {
        long long x = (long long)waterStartTime[i] + waterDuration[i];
        int p = upperBound(lStart, n, (int)x) - 1;

        long long cur = (long long)1e18;
        if (p >= 0) cur = x + lPref[p];
        if (p + 1 < n && lSuff[p + 1] < cur) cur = lSuff[p + 1];

        if (cur < ans) ans = cur;
    }

    free(water);
    free(wStart);
    free(wPref);
    free(wSuff);
    free(land);
    free(lStart);
    free(lPref);
    free(lSuff);

    return (int)ans;
}
```
# Key Techniques Used

- Sorting
- Binary Search (Upper Bound)
- Prefix Minimum Array
- Suffix Minimum Array
- Greedy Observation
- Two-Pass Optimization
- Range Minimum Preprocessing

```