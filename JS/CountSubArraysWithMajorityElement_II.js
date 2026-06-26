var countMajoritySubarrays = function(nums, target) {
    const n = nums.length;
    const len = 2 * n + 2;

    const countAtSum = new Array(len).fill(0);
    const comulativeCount = new Array(len).fill(0);

    let idx = n + 1;
    countAtSum[idx] = 1;
    comulativeCount[idx] = 1;

    let ans = 0;

    for (const num of nums) {
        if (num === target)
            idx++;
        else
            idx--;

        countAtSum[idx]++;
        ans += comulativeCount[idx - 1];
        comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
    }

    return ans;
};