struct heavy_light{
	int heavy[MAXN], root[MAXN], depth[MAXN];
	int pos[MAXN], ipos[MAXN], parent[MAXN],n;
	int dfs(int s, int f, vector<int> *G){
		parent[s] = f, heavy[s] = -1;
		int size = 1, maxSubtree = 0;
		for (auto u : G[s])
			if (u != f){
				depth[u] = depth[s] + 1;
				int subtree = dfs(u, s, G);
				if (subtree > maxSubtree)
					heavy[s] = u, maxSubtree = subtree;
				size += subtree;
			}
		return size;
	}
	void go(vector<int> *G, int _n){
		n = _n;
		int ROOT = 0;
		depth[ROOT] = 0;
		dfs(ROOT, -1, G);
		vector<pii> nodes;
		for (int i = 0; i < n; i++)
			if (parent[i] == -1 || heavy[parent[i]] != i)
				nodes.push_back(pii(depth[i], i));
		sort(all(nodes));
		for (int ii = 0, currentPos = 0; ii < nodes.size(); ++ii){
			int i = nodes[ii].s;
			for (int u = i; u != -1; u = heavy[u], currentPos++){
				root[u] = i, pos[u] = currentPos, ipos[currentPos] = u;
			}
		}
	}
	int lca(int u, int v, ST<T> &st){
		int ans = oo;
		for (; root[u] != root[v]; v = parent[root[v]]){
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
			ans = min(ans, 
				st.operation(1, 0, n - 1, pos[root[v]], pos[v]));
		}
		if (depth[u] > depth[v]) swap(u, v);
		ans = min(ans, st.operation(1, 0, n - 1, pos[u], pos[v]));
		return ans; // LCA at u
	}
	// The kth node (0 indexed) in the path from (u to root)
	int go_up(int u, int k){ 
		for (; pos[u] - pos[root[u]] < k; u = parent[root[u]])
			k -= pos[u] - pos[root[u]] + 1;
		return ipos[pos[u] - k];
	}
};
