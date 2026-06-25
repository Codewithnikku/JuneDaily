var countMajoritySubarrays = function(nums, target) {
    const n = nums.length;
    const ans = 0;
    for(let i=0; i<n; i++) {
        const count = 0;
        for(let j=i; j<n; j++) {
            if(nums[j]==target) count++;
            if(count > (j-i+1)/2) ans++;
        }
    }
    return ans;
};