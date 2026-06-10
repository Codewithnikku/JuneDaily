long long maxTotalValue(int* nums, int numsSize, int k) {
    int mn = nums[0];
    int mx = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < mn) mn = nums[i];
        if (nums[i] > mx) mx = nums[i];
    }

    return 1LL * k * (mx - mn);
}