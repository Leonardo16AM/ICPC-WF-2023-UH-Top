/** Notes:
    Split a tree in several path in a way that there is
    at most log(n) path from any node u to the root.

    pos     -> Position of node u in the list.
    ipos    -> Reverse of pos (Node on position i)

    No need to initialize for several uses.
**/

typedef vector<vector<int>> graph;

struct heavy_light{
    int n, heavy[maxn], root[maxn], depth[maxn];
    int pos[maxn], ipos[maxn], parent[maxn];

    int dfs(int s, int f, graph &G){
        parent[s] = f, heavy[s] = -1;
        int size = 1, maxSubtree = 0;

        for (auto u : G[s]) if (u != f){
            depth[u] = depth[s] + 1;
            int subtree = dfs(u, s, G);

            if (subtree > maxSubtree)
                heavy[s] = u, maxSubtree = subtree;

            size += subtree;
        }

        return size;
    }

    void go(graph &G, int ROOT=0){
        n = (int)G.size();

        depth[ROOT] = 0;
        dfs(ROOT, -1, G);

        for (int i = 0, currentPos = 0; i < n; ++i)
            if (parent[i] == -1 || heavy[parent[i]] != i)
                for (int u = i; u != -1; u = heavy[u], currentPos++)
                    root[u] = i, pos[u] = currentPos, ipos[currentPos] = u;
    }

    int lca(int u, int v, segment_tree &ST){
        int ans = oo;
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            ans = min(ans, ST.operation(1, 0, n, pos[root[v]], pos[v] + 1));
        }
        if (depth[u] > depth[v]) swap(u, v);
        ans = min(ans, ST.operation(1, 0, n, pos[u], pos[v] + 1));

        // LCA at u
        return ans;
    }

    int go_up(int u, int k){
        // The kth node (0 indexed) in the path from (u to root)
        for (;pos[u] - pos[root[u]] < k; u = parent[root[u]])
            k -= pos[u] - pos[root[u]] + 1;
        return ipos[pos[u] - k];
    }
};
