var pivotArray = function(nums, pivot) {
    const n = nums.length;
    let less = 0, equal = 0;

    for (let i = 0; i < n; i++) {
        if (nums[i] < pivot) less++;
        else if (nums[i] === pivot) equal++;
    }

    const ans = new Array(n);

    let i = 0;
    let j = less;
    let k = less + equal;

    for (let p = 0; p < n; p++) {
        const x = nums[p];

        if (x < pivot) {
            ans[i++] = x;
        } else if (x === pivot) {
            ans[j++] = x;
        } else {
            ans[k++] = x;
        }
    }

    return ans;
};