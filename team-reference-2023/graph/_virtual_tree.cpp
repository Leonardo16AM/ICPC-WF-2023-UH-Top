// Compute the lca of two nodes and the distance 
// between them
// Compress a subset of k nodes into a tree with 
// the same structure
// Notes: mp are only necessary for compress
//        after compress every node u is mapped 
//        to mp[u]
// Complexity: O(n log n) build, O(1) lca, 
// O(k log k) compress
struct virtual_tree{
	vector<int> tour, depth, pos, mp;
	vector<vector<int>> table;
	virtual_tree(vector<vector<int>> &adj){
		pos = mp = vector<int>(adj.size());
		function<void(int, int, int)> dfs 
			= [&](int u, int p, int d){
			pos[u] = tour.size();
			tour.push_back(u);
			depth.push_back(d);
			for (int v : adj[u])
				if (v != p){
					dfs(v, u, d+1);
					tour.push_back(u);
					depth.push_back(d);
				}			
		};
		dfs(0, -1, 0);
		int t = tour.size(), lg = __lg(t);
		table.resize(lg+1, vector<int>(t));
		iota(table[0].begin(), table[0].end(), 0);
		for (int j = 0; j < lg; ++j)
			for (int i = 0; i + (1<<(j+1)) <= t; ++i)
				table[j+1][i] = argmin(table[j][i], 
					table[j][i+(1<<j)]);
	}
	inline int argmin(int i, int j) 
	{ return depth[i] < depth[j] ? i : j; }
	inline int lca(int u, int v){
		int i = pos[u], j = pos[v];
		if (i > j) swap(i, j);
		int l = __lg(j - i);
		return i == j ? u : tour[argmin(table[l][i], 
			table[l][j-(1<<l)])];
	}

	inline int dist(int u, int v){
		return depth[pos[u]] + depth[pos[v]] - 2*depth[pos[lca(u, v)]];
	}
	vector<vector<pair<int, int>>> compress(vector<int> &a){
		auto cmp = [&](const int &x, const int &y) 
		{ return pos[x] < pos[y]; };
		auto c = a;
		sort(c.begin(), c.end(), cmp);
		for (int i = 1, sz = c.size(); i < sz; ++i)
			c.push_back(lca(c[i-1], c[i]));
		sort(c.begin(), c.end(), cmp);
		c.erase(unique(c.begin(), c.end()), c.end());
		vector<vector<pair<int, int>>> g(c.size());
		vector<int> s;
		// u become mp[u]
		for (auto &u : c){
			mp[u] = &u-&c[0];
			while (!s.empty() && lca(s.back(), u) != s.back())
				s.pop_back();
			if (!s.empty()){
				int d = dist(s.back(), u);
				g[mp[s.back()]].push_back({ mp[u], d });
				g[mp[u]].push_back({ mp[s.back()], d });
			}
			s.push_back(u);
		}
		return g;
	}
};