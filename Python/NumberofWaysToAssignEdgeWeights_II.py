from collections import deque

class Solution(object):
    def assignEdgeWeights(self, edges, queries):
        MOD = 1000000007
        n = len(edges) + 1

        adj = [[] for _ in range(n + 1)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        depth = [0] * (n + 1)
        lift = [[1] * 18 for _ in range(n + 1)]
        vis = [False] * (n + 1)

        q = deque([1])
        vis[1] = True

        while q:
            cur = q.popleft()
            for nxt in adj[cur]:
                if vis[nxt]:
                    continue
                vis[nxt] = True
                depth[nxt] = depth[cur] + 1
                lift[nxt][0] = cur
                q.append(nxt)

        for j in range(1, 18):
            for i in range(1, n + 1):
                lift[i][j] = lift[lift[i][j - 1]][j - 1]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u

            diff = depth[u] - depth[v]

            for j in range(17, -1, -1):
                if (diff >> j) & 1:
                    u = lift[u][j]

            if u == v:
                return u

            for j in range(17, -1, -1):
                if lift[u][j] != lift[v][j]:
                    u = lift[u][j]
                    v = lift[v][j]

            return lift[u][0]

        ans = []

        for u, v in queries:
            p = lca(u, v)
            dist = depth[u] + depth[v] - 2 * depth[p]
            ans.append(0 if dist == 0 else pow(2, dist - 1, MOD))

        return ans