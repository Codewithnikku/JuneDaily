import java.util.*;

class MBH {
    public int maxBuilding(int n, int[][] restrictions) {

        Arrays.sort(restrictions, (a, b) -> Integer.compare(a[0], b[0]));

        int len = restrictions.length;

        if (len == 0) {
            return n - 1;
        }

        boolean isLast = restrictions[len - 1][0] == n;

        int m = len + 1 + (isLast ? 0 : 1);

        int[][] h = new int[m][2];

        h[0][0] = 1;
        h[0][1] = 0;

        for (int i = 0; i < len; i++) {
            int diff = restrictions[i][0] - h[i][0];
            int ht = h[i][1] + diff;

            h[i + 1][0] = restrictions[i][0];
            h[i + 1][1] = Math.min(ht, restrictions[i][1]);
        }

        if (!isLast) {
            int diff = n - h[len][0];
            int ht = h[len][1] + diff;

            h[len + 1][0] = n;
            h[len + 1][1] = Math.min(ht, n - 1);
        }

        for (int i = m - 2; i >= 0; i--) {
            int diff = h[i + 1][0] - h[i][0];
            int ht = h[i + 1][1] + diff;

            h[i][1] = Math.min(h[i][1], ht);
        }

        int ans = 0;

        for (int i = 1; i < m; i++) {
            int left = h[i - 1][0];
            int right = h[i][0];

            int h1 = h[i - 1][1];
            int h2 = h[i][1];

            int dist = right - left;

            int peak = (dist + h1 + h2) / 2;

            ans = Math.max(ans, peak);
        }

        return ans;
    }
}

public class MaximumBuildingHeight {
    public static void main(String[] args) {
        
    }
}