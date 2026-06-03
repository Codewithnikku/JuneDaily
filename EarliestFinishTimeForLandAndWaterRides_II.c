#include <stdlib.h>
#include <limits.h>

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

int main() {
    int landStartTime[] = {1, 2, 3};
    int landDuration[] = {2, 3, 1};
    int waterStartTime[] = {2, 3, 4};
    int waterDuration[] = {1, 2, 3};

    printf("%d\n", earliestFinishTime(landStartTime, sizeof(landStartTime) / sizeof(int),
                                     landDuration, sizeof(landDuration) / sizeof(int),
                                     waterStartTime, sizeof(waterStartTime) / sizeof(int),
                                     waterDuration, sizeof(waterDuration) / sizeof(int)));
    return 0;
}