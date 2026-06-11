class Solution {
public:
    static constexpr long long MOD = 1000000007LL;

    long long modPow(long long base, long long exp) {
        long long res = 1;
        while (exp) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;

        vector<vector<int>> g(n + 1);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        queue<int> q;
        vector<int> depth(n + 1, -1);

        q.push(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            maxDepth = max(maxDepth, depth[u]);

            for (int v : g[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }

        if (maxDepth == 0) return 0;

        return (int)modPow(2, maxDepth - 1);
    }
};