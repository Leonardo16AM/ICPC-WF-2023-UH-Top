
struct tree
{
	int n;
	vector<vector<int>> adj;

	tree(int n) : n(n), adj(n) {}

	void add_edge(int s, int t)
	{
		adj[s].push_back(t);
		adj[t].push_back(s);
	}

	vector<int> pos, tour, depth;
	vector<vector<int>> table;

	int argmin(int i, int j)
	{
		return depth[i] < depth[j] ? i : j;
	}

	void rootify(int r)
	{
		pos.resize(n);
		function<void(int, int, int)> dfs = [&](int u, int p, int d)
		{
			pos[u] = depth.size();
			tour.push_back(u);
			depth.push_back(d);
			for (int v : adj[u])
				if (v != p)
				{
					dfs(v, u, d+1);
					tour.push_back(u);
					depth.push_back(d);
				}
		};
		dfs(r, r, 0);
		int logn = __lg(tour.size()); // log2
		table.resize(logn + 1, vector<int>(tour.size()));
		iota(table[0].begin(), table[0].end(), 0);
		for (int h = 0; h < logn; ++h)
			for (int i = 0; i + (1 << h) < (int) tour.size(); ++i)
				table[h + 1][i] = argmin(table[h][i], 
								table[h][i + (1 << h)]);
	}

	int lca(int u, int v)
	{
		int i = pos[u], j = pos[v];
		if (i > j) swap(i, j);
		int h = __lg(j - i); // = log2
		return i == j ? u : tour[argmin(table[h][i], 
								table[h][j - (1 << h)])];
	}
};
