class MTSAV_I {
    public long maxTotalValue(int[] nums, int k) {
        int mn = nums[0];
        int mx = nums[0];

        for (int x : nums) {
            mn = Math.min(mn, x);
            mx = Math.max(mx, x);
        }

        return 1L * k * (mx - mn);
    }
}

public class MaximumTotalSubArrayValue_I {
    public static void main(String[] args) {
        
    }
}