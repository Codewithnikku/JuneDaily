import java.util.Arrays;

class TWNIR_II {
    static class Node {
        long cnt;
        long wav;

        Node(long cnt, long wav) {
            this.cnt = cnt;
            this.wav = wav;
        }
    }

    String s;
    Node[][][][][] dp;
    boolean[][][][][] vis;

    private Node dfs(int pos, int started, int len, int a, int b, boolean tight) {
        if (pos == s.length()) {
            return new Node(1, 0);
        }

        if (!tight && vis[pos][started][len][a][b]) {
            return dp[pos][started][len][a][b];
        }

        int limit = tight ? s.charAt(pos) - '0' : 9;
        long totalCnt = 0;
        long totalWav = 0;

        for (int d = 0; d <= limit; d++) {
            boolean nextTight = tight && (d == limit);

            if (started == 0 && d == 0) {
                Node nxt = dfs(pos + 1, 0, 0, 10, 10, nextTight);
                totalCnt += nxt.cnt;
                totalWav += nxt.wav;
            } else {
                if (started == 0) {
                    Node nxt = dfs(pos + 1, 1, 1, 10, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav;
                } else if (len == 1) {
                    Node nxt = dfs(pos + 1, 1, 2, b, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav;
                } else {
                    int add = ((b > a && b > d) || (b < a && b < d)) ? 1 : 0;
                    Node nxt = dfs(pos + 1, 1, 2, b, d, nextTight);
                    totalCnt += nxt.cnt;
                    totalWav += nxt.wav + nxt.cnt * add;
                }
            }
        }

        Node res = new Node(totalCnt, totalWav);

        if (!tight) {
            vis[pos][started][len][a][b] = true;
            dp[pos][started][len][a][b] = res;
        }

        return res;
    }

    private long solve(long n) {
        if (n < 0) return 0;

        s = Long.toString(n);
        int m = s.length();

        dp = new Node[m + 1][2][3][11][11];
        vis = new boolean[m + 1][2][3][11][11];

        return dfs(0, 0, 0, 10, 10, true).wav;
    }

    public long totalWaviness(long num1, long num2) {
        return solve(num2) - solve(num1 - 1);
    }
}

public class TotalWavinessofNumbersInRange_II {
    public static void main(String[] args) {
        TWNIR_II solver = new TWNIR_II();
        long num1 = 120;
        long num2 = 130;
        System.out.println(solver.totalWaviness(num1, num2));
    }
}
