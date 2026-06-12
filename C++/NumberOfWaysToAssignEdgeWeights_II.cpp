#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    static const int MOD = 1000000007;
    vector<int> depth;
    vector<vector<int>> lift;
    vector<vector<int>> adj;

    int power(long long base, int exp) {
        long long res = 1;
        base %= MOD;

        while (exp > 0) {
            if (exp & 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }

        return (int)res;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int j = 17; j >= 0; --j) {
            if ((diff >> j) & 1) {
                u = lift[u][j];
            }
        }

        if (u == v) {
            return u;
        }

        for (int j = 17; j >= 0; --j) {
            if (lift[u][j] != lift[v][j]) {
                u = lift[u][j];
                v = lift[v][j];
            }
        }

        return lift[u][0];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;

        adj.assign(n + 1, {});
        depth.assign(n + 1, 0);
        lift.assign(n + 1, vector<int>(18, 1));

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        queue<int> q;
        vector<bool> vis(n + 1, false);

        q.push(1);
        vis[1] = true;
        lift[1][0] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nxt : adj[cur]) {
                if (vis[nxt]) continue;

                vis[nxt] = true;
                depth[nxt] = depth[cur] + 1;
                lift[nxt][0] = cur;
                q.push(nxt);
            }
        }

        for (int j = 1; j < 18; ++j) {
            for (int i = 1; i <= n; ++i) {
                lift[i][j] = lift[lift[i][j - 1]][j - 1];
            }
        }

        vector<int> ans;

        for (auto &qv : queries) {
            int u = qv[0];
            int v = qv[1];

            int p = lca(u, v);
            int dist = depth[u] + depth[v] - 2 * depth[p];

            ans.push_back(dist == 0 ? 0 : power(2, dist - 1));
        }

        return ans;
    }
};

int main(){
    
    return 0;
}