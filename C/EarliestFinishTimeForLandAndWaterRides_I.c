#include <stdio.h>

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

int main(){
    int landStartTime[] = {1, 4, 6};
    int landDuration[] = {2, 3, 1};
    int waterStartTime[] = {2, 5};
    int waterDuration[] = {3, 2};
    int landStartTimeSize = sizeof(landStartTime) / sizeof(landStartTime[0]);
    int landDurationSize = sizeof(landDuration) / sizeof(landDuration[0]);
    int waterStartTimeSize = sizeof(waterStartTime) / sizeof(waterStartTime[0]);
    int waterDurationSize = sizeof(waterDuration) / sizeof(waterDuration[0]);
    printf("%d\n", earliestFinishTime(landStartTime, landStartTimeSize, landDuration, landDurationSize, waterStartTime, waterStartTimeSize, waterDuration, waterDurationSize));
    return 0;
}