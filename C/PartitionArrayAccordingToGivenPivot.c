int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int less = 0, equal = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < pivot)
            less++;
        else if (nums[i] == pivot)
            equal++;
    }

    int* ans = (int*)malloc(numsSize * sizeof(int));

    int i = 0;
    int j = less;
    int k = less + equal;

    for (int p = 0; p < numsSize; p++) {
        int x = nums[p];

        if (x < pivot)
            ans[i++] = x;
        else if (x == pivot)
            ans[j++] = x;
        else
            ans[k++] = x;
    }

    *returnSize = numsSize;
    return ans;
}