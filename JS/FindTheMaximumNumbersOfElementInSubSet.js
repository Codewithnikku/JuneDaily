/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumLength = function(nums) {
    const freq = new Map();
    for (let num of nums) {
        freq.set(num, (freq.get(num) || 0) + 1);
    }

    let ans = 0;
    if (freq.has(1)) {
        const ones = freq.get(1);
        ans = (ones % 2 === 0) ? ones - 1 : ones;
        freq.delete(1);
    }

    const memo = new Map();
    function dfs(num) {
        if (!freq.has(num)) return 0;
        if (memo.has(num)) return memo.get(num);

        let count;
        if (freq.get(num) >= 2) {
            count = 2 + dfs(num * num);
        } else {
            count = 1;
        }
        if (count % 2 === 0) count--;
        memo.set(num, count);
        return count;
    }

    for (let num of freq.keys()) {
        ans = Math.max(ans, dfs(num));
    }
    return ans;
};
