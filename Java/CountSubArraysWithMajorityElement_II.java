public class CountSubArraysWithMajorityElement_II {
    public long countMajoritySubarrays(int[] nums, int target) {
        int n = nums.length;
        int len = 2 * n + 2;
        long[] countAtSum = new long[len];
        long[] comulativeCount = new long[len];
        int idx = n + 1;
        countAtSum[idx] = 1;
        comulativeCount[idx] = 1;
        long ans = 0;
        for (int num : nums) {
            if (num == target)
                idx++;
            else
                idx--;
            countAtSum[idx]++;
            ans += comulativeCount[idx-1];
            comulativeCount[idx] = comulativeCount[idx - 1] + countAtSum[idx];
        }
        return ans;
    }
}
