#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int minimumCost(int* cost, int costSize) {
    qsort(cost, costSize, sizeof(int), compare);

    int ans = 0;

    for (int i = 0; i < costSize; i++) {
        if (i % 3 != 2) {
            ans += cost[i];
        }
    }

    return ans;
}


int main(){
    int cost[] = {1, 2, 3};
    int costSize = sizeof(cost) / sizeof(cost[0]);
    printf("%d\n", minimumCost(cost, costSize));
    return 0;
}

