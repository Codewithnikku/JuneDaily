import java.util.*;

class ETLWR_II {
    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        long ans = Math.min(
            solve(landStartTime, landDuration, waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration, landStartTime, landDuration)
        );
        return (int) ans;
    }

    private long solve(int[] s1, int[] d1, int[] s2, int[] d2) {
        int m = s2.length;

        int[][] rides = new int[m][2];
        for (int i = 0; i < m; i++) {
            rides[i][0] = s2[i];
            rides[i][1] = d2[i];
        }

        Arrays.sort(rides, (a, b) -> Integer.compare(a[0], b[0]));

        int[] starts = new int[m];
        long[] prefMinDur = new long[m];
        long[] suffMinFinish = new long[m];

        for (int i = 0; i < m; i++) {
            starts[i] = rides[i][0];
        }

        for (int i = 0; i < m; i++) {
            prefMinDur[i] = rides[i][1];
            if (i > 0) prefMinDur[i] = Math.min(prefMinDur[i], prefMinDur[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            suffMinFinish[i] = (long) rides[i][0] + rides[i][1];
            if (i + 1 < m) {
                suffMinFinish[i] = Math.min(suffMinFinish[i], suffMinFinish[i + 1]);
            }
        }

        long ans = Long.MAX_VALUE;

        for (int i = 0; i < s1.length; i++) {
            long t = (long) s1[i] + d1[i];
            int pos = upperBound(starts, (int) t);

            if (pos > 0) {
                ans = Math.min(ans, t + prefMinDur[pos - 1]);
            }

            if (pos < m) {
                ans = Math.min(ans, suffMinFinish[pos]);
            }
        }

        return ans;
    }

    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] <= target) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
}

public class EarliestFinishTimeForLandAndWaterRides_II {
    public static void main(String[] args) {
        ETLWR_II etlwr = new ETLWR_II();
        int[] landStartTime = {1, 2, 3};
        int[] landDuration = {2, 3, 1};
        int[] waterStartTime = {2, 3, 4};
        int[] waterDuration = {1, 2, 3};
        System.out.println(etlwr.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
    }
}