class LRSD {
    public int[] leftRightDifference(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];

        int rightSum = 0;
        for (int num : nums) {
            rightSum += num;
        }

        int leftSum = 0;
        for (int i = 0; i < n; i++) {
            rightSum -= nums[i];
            ans[i] = Math.abs(leftSum - rightSum);
            leftSum += nums[i];
        }

        return ans;
    }
}


public class LeftRightSUmDifferences {
    public static void main(String[] args) {
        LRSD lrds = new LRSD();
        int[] nums = {10, 4, 8, 3};

        int[] result = lrds.leftRightDifference(nums);

        for (int x : result) {
            System.out.print(x + " ");
        }
    }
}