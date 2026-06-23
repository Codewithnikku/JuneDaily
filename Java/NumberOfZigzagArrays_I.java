import java.util.Arrays;

public class NumberOfZigzagArrays_I {
    int mod = 1_000_000_007;
    public int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        long[] up = new long[m];
        long[] down = new long[m];
        Arrays.fill(up, 1);
        Arrays.fill(down, 1);

        for (int i = 2; i <= n; i++) {
            long[] preDown = new long[m + 1];
            long[] suffUp = new long[m + 1];
            for (int j = 0; j < m; j++) {
                preDown[j + 1] = (preDown[j] + down[j]) % mod;
            }
            for (int j = m - 1; j >= 0; j--) {
                suffUp[j] = (suffUp[j + 1] + up[j]) % mod;
            }
            long[] newUp = new long[m];
            long[] newDown = new long[m];
            for (int j = 0; j < m; j++) {
                newUp[j] = preDown[j];
                newDown[j] = suffUp[j + 1];
            }

            up = newUp;
            down = newDown;
        }

        long ans = 0;
        for (int j = 0; j < m; j++) {
            ans = (ans + up[j] + down[j]) % mod;
        }

        return (int) ans;
    }

    public static void main(String[] args) { }
}