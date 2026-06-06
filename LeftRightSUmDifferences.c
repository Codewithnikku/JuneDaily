#include<stdio.h>
#include<stdlib.h>

int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    int rightSum = 0;
    for (int i = 0; i < numsSize; i++) {
        rightSum += nums[i];
    }
    
    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        rightSum -= nums[i];
        
        int diff = leftSum - rightSum;
        ans[i] = diff < 0 ? -diff : diff;
        
        leftSum += nums[i];
    }
    
    return ans;
}

int main() {
    int nums[] = {10, 4, 8, 3};
    int n = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* result = leftRightDifference(nums, n, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}