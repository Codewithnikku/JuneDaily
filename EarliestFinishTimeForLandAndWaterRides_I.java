class EFTFLWR {
    public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
        long ans = Long.MAX_VALUE;

        int m = waterStartTime.length;
        int[][] water = new int[m][2];
        for (int i = 0; i < m; i++) {
            water[i][0] = waterStartTime[i];
            water[i][1] = waterDuration[i];
        }

        java.util.Arrays.sort(water, (a, b) -> Integer.compare(a[0], b[0]));

        int[] wStart = new int[m];
        long[] wPref = new long[m];
        long[] wSuff = new long[m];

        for (int i = 0; i < m; i++) {
            wStart[i] = water[i][0];
            wPref[i] = water[i][1];
            if (i > 0) wPref[i] = Math.min(wPref[i], wPref[i - 1]);
        }

        for (int i = m - 1; i >= 0; i--) {
            wSuff[i] = (long) water[i][0] + water[i][1];
            if (i + 1 < m) wSuff[i] = Math.min(wSuff[i], wSuff[i + 1]);
        }

        for (int i = 0; i < landStartTime.length; i++) {
            long x = (long) landStartTime[i] + landDuration[i];
            int p = upperBound(wStart, (int) x) - 1;

            long cur = Long.MAX_VALUE;
            if (p >= 0) cur = Math.min(cur, x + wPref[p]);
            if (p + 1 < m) cur = Math.min(cur, wSuff[p + 1]);

            ans = Math.min(ans, cur);
        }

        int n = landStartTime.length;
        int[][] land = new int[n][2];
        for (int i = 0; i < n; i++) {
            land[i][0] = landStartTime[i];
            land[i][1] = landDuration[i];
        }

        java.util.Arrays.sort(land, (a, b) -> Integer.compare(a[0], b[0]));

        int[] lStart = new int[n];
        long[] lPref = new long[n];
        long[] lSuff = new long[n];

        for (int i = 0; i < n; i++) {
            lStart[i] = land[i][0];
            lPref[i] = land[i][1];
            if (i > 0) lPref[i] = Math.min(lPref[i], lPref[i - 1]);
        }

        for (int i = n - 1; i >= 0; i--) {
            lSuff[i] = (long) land[i][0] + land[i][1];
            if (i + 1 < n) lSuff[i] = Math.min(lSuff[i], lSuff[i + 1]);
        }

        for (int i = 0; i < waterStartTime.length; i++) {
            long x = (long) waterStartTime[i] + waterDuration[i];
            int p = upperBound(lStart, (int) x) - 1;

            long cur = Long.MAX_VALUE;
            if (p >= 0) cur = Math.min(cur, x + lPref[p]);
            if (p + 1 < n) cur = Math.min(cur, lSuff[p + 1]);

            ans = Math.min(ans, cur);
        }

        return (int) ans;
    }

    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = (l + r) >>> 1;
            if (arr[mid] <= target) l = mid + 1;
            else r = mid;
        }
        return l;
    }
}

public class EarliestFinishTimeForLandAndWaterRides_I {
    public static void main(String[] args) {
        EFTFLWR eftflwr = new EFTFLWR();
        int[] landStartTime = {1, 4, 6};
        int[] landDuration = {2, 3, 1};
        int[] waterStartTime = {2, 5};
        int[] waterDuration = {3, 2};
        System.out.println(eftflwr.earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration));
    }
}
