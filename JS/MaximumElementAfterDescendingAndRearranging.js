/**
 * @param {number[]} arr
 * @return {number}
 */
var maximumElementAfterDecrementingAndRearranging = function(arr) {
    const n = arr.length; let ans = 1;
    const count = new Array(n + 1).fill(0);
    for (const a of arr) { const idx = Math.min(a, n); count[idx]++; }
    for (let i = 2; i <= n; i++) { const curr = ans + count[i]; ans = Math.min(i, curr); }
    return ans;
};