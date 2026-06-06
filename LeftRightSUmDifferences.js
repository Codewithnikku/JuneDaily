var leftRightDifference = function(nums) {
    const n = nums.length;
    const ans = new Array(n);

    let rightSum = 0;
    for (const num of nums) {
        rightSum += num;
    }

    let leftSum = 0;
    for (let i = 0; i < n; i++) {
        rightSum -= nums[i];
        ans[i] = Math.abs(leftSum - rightSum);
        leftSum += nums[i];
    }

    return ans;
};

const nums = [10, 4, 8, 3];
console.log(leftRightDifference(nums));