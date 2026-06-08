import java.util.Arrays;

class MCBCWD{
    public int minimumCost(int[] cost) {
        Arrays.sort(cost);
        int ans = 0;
        
        for (int i = cost.length - 1, cnt = 0; i >= 0; i--, cnt++) {
            if (cnt % 3 != 2) {
                ans += cost[i];
            }
        }
        
        return ans;
    }
}

public class MinimumCostOfBuyingCanddatesWithDiscount {
    public static void main(String[] args) {
        MCBCWD mcbcwd = new MCBCWD();
        int[] cost = {1, 2, 3};
        System.out.println(mcbcwd.minimumCost(cost)); 
    }
}