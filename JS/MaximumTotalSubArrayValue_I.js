/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxTotalValue = function(nums, k) {
    let mn = nums[0];
    let mx = nums[0];

    for (const x of nums) {
        if (x < mn) mn = x;
        if (x > mx) mx = x;
    }

    return k * (mx - mn);
};