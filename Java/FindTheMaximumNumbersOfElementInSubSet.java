import java.util.HashMap;

public class FindTheMaximumNumbersOfElementInSubSet {
    public int maximumLength(int[] nums) {
        HashMap<Long, Integer> freq = new HashMap<>();
        for (int num : nums) {
            freq.put((long) num, freq.getOrDefault((long) num, 0) + 1);
        }

        int ans = 0;
        if (freq.containsKey(1L)) {
            int ones = freq.get(1L);
            ans = (ones % 2 == 0) ? ones - 1 : ones;
            freq.remove(1L);
        }

        HashMap<Long, Integer> memo = new HashMap<>();
        for (long num : freq.keySet()) {
            ans = Math.max(ans, dfs(num, freq, memo));
        }
        return ans;
    }

    private int dfs(long num, HashMap<Long, Integer> freq, HashMap<Long, Integer> memo) {
        if (!freq.containsKey(num)) return 0;
        if (memo.containsKey(num)) return memo.get(num);

        int count;
        if (freq.get(num) >= 2) {
            count = 2 + dfs(num * num, freq, memo);
        } else {
            count = 1;
        }

        if (count % 2 == 0) count--; // adjust
        memo.put(num, count);
        return count;
    }
}