// Bipartite Matching
// Complexity: O(E sqrt V)
// ** using only dfs marking visited nodes and cleaning 
// them in bfs(in O(1)) might be faster **
struct hopcroft_karp{
	int n, m;
	vector<vector<int>> adj;
	vector<int> mu, mv, level, que; 
	// u is matched with mu[u] and v with mv[v], -1 if no match
	hopcroft_karp(int n, int m) : n(n), m(m), adj(n), 
	mu(n, -1), mv(m, -1), level(n), que(n) {}
	void add_edge(int u, int v) { adj[u].push_back(v); }
	void bfs(){
		int qf = 0, qt = 0;
		for (int u = 0; u < n; ++u){
			if (mu[u] == -1) que[qt++] = u, level[u] = 0;
			else level[u] = -1;
		}
		for (; qf < qt; ++qf){
			int u = que[qf];
			for (auto w : adj[u]){
				int v = mv[w];
				if (v != -1 && level[v] == -1)
					que[qt++] = v, level[v] = level[u] + 1;
			}
		}
	}
	bool dfs(int u){
		for (auto w : adj[u]){
			int v = mv[w];
			if (v == -1 || (level[v] == level[u] + 1 && dfs(v))) 
				// split this line for speed up :)
				return mu[u] = w, mv[w] = u, true;
		}
		level[u] = -1;
		return false;
	}
	int max_matching(){
		int match = 0;
		for (int c = 1; bfs(), c; match += c)
			for (int u = c = 0; u < n; ++u)
				if (mu[u] == -1) c += dfs(u);
		return match;
	}
	pair<vector<int>, vector<int>> min_vertex_cover(){
		max_matching();
		vector<int> L, R, inR(m);
		for (int u = 0; u < n; ++u){
			if (level[u] == -1) L.push_back(u);
			else if (mu[u] != -1) inR[mu[u]] = true;
		}
		for (int v = 0; v < m; ++v)
			if (inR[v]) R.push_back(v);
		return { L, R };
	}
};