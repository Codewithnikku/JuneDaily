import java.util.*;

class NWAEW_I {
    private static final long MOD = 1_000_000_007L;

    public int assignEdgeWeights(int[][] edges) {
        int n = edges.length + 1;

        List<Integer>[] graph = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] e : edges) {
            int u = e[0];
            int v = e[1];
            graph[u].add(v);
            graph[v].add(u);
        }

        Queue<Integer> q = new LinkedList<>();
        int[] depth = new int[n + 1];
        Arrays.fill(depth, -1);

        q.offer(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.isEmpty()) {
            int u = q.poll();
            maxDepth = Math.max(maxDepth, depth[u]);

            for (int v : graph[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.offer(v);
                }
            }
        }

        if (maxDepth == 0) return 0;

        return (int) modPow(2, maxDepth - 1);
    }

    private long modPow(long base, long exp) {
        long res = 1;

        while (exp > 0) {
            if ((exp & 1) == 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }

        return res;
    }
}

public class NumberOfWaysToAssignEdgeWeights_I {
    
}
