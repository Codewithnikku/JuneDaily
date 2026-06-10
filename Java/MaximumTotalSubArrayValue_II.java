import java.util.*;

class SparseTable {
    private int[][] minTable;
    private int[][] maxTable;

    public SparseTable(int[] nums) {
        int n = nums.length;
        int w = 32 - Integer.numberOfLeadingZeros(n);

        minTable = new int[w][n];
        maxTable = new int[w][n];

        for (int i = 0; i < n; i++) {
            minTable[0][i] = nums[i];
            maxTable[0][i] = nums[i];
        }

        for (int i = 1; i < w; i++) {
            int len = 1 << i;
            int half = 1 << (i - 1);

            for (int j = 0; j + len <= n; j++) {
                minTable[i][j] = Math.min(
                    minTable[i - 1][j],
                    minTable[i - 1][j + half]
                );

                maxTable[i][j] = Math.max(
                    maxTable[i - 1][j],
                    maxTable[i - 1][j + half]
                );
            }
        }
    }

    public int query(int left, int right) {
        // range is [left, right)
        int len = right - left;
        int k = 31 - Integer.numberOfLeadingZeros(len);

        int mx = Math.max(
            maxTable[k][left],
            maxTable[k][right - (1 << k)]
        );

        int mn = Math.min(
            minTable[k][left],
            minTable[k][right - (1 << k)]
        );

        return mx - mn;
    }
}

class Solution {
    static class Node {
        int value;
        int left;
        int right;

        Node(int value, int left, int right) {
            this.value = value;
            this.left = left;
            this.right = right;
        }
    }

    public long maxTotalValue(int[] nums, int k) {
        int n = nums.length;
        long res = 0;

        SparseTable lut = new SparseTable(nums);

        PriorityQueue<Node> pq = new PriorityQueue<>(
            (a, b) -> Integer.compare(b.value, a.value)
        );

        for (int i = 0; i < n; i++) {
            pq.offer(new Node(lut.query(i, n), i, n));
        }

        while (!pq.isEmpty() && pq.peek().value > 0 && k-- > 0) {
            Node cur = pq.poll();

            res += cur.value;

            pq.offer(
                new Node(
                    lut.query(cur.left, cur.right - 1),
                    cur.left,
                    cur.right - 1
                )
            );
        }

        return res;
    }
}

public abstract class MaximumTotalSubArrayValue_II {
    
}
