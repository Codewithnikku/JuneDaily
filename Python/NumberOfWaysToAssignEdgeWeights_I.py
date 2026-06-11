class Solution(object):
    MOD = 1000000007

    def assignEdgeWeights(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: int
        """
        n = len(edges) + 1

        graph = [[] for _ in range(n + 1)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        depth = [-1] * (n + 1)
        depth[1] = 0

        q = [1]
        front = 0
        max_depth = 0

        while front < len(q):
            u = q[front]
            front += 1

            max_depth = max(max_depth, depth[u])

            for v in graph[u]:
                if depth[v] == -1:
                    depth[v] = depth[u] + 1
                    q.append(v)

        if max_depth == 0:
            return 0

        return pow(2, max_depth - 1, self.MOD)