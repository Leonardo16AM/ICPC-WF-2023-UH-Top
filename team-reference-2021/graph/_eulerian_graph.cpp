// Euler path undirected (path to use once all edges)
// the degree of all nodes must be even (euler cycle)
// or only exists two odd nodes (euler path)
vector<int> euler_path(const vector<vector<pair<int, int>>> &G, int s = 0){
	int n = G.size(), odd = 0, m = 0;
	for (int i = 0; i < n; ++i){
		odd += G[i].size() & 1;
		m += G[i].size();
	}
	vector<int> path;
	if (odd == 0 || (odd == 2 && (G[s].size() & 1) == 1)){
		vector<int> pos(n);
		vector<bool> mark(m / 2);
		function<void(int)> visit = [&](int u){
			for (int v, id; pos[u] < G[u].size(); ){
				tie(v, id) = G[u][pos[u]++];
				if (!mark[id]){
					mark[id] = true;
					visit(v);
				}
			}
			path.push_back(u);
		};
		visit(s);
		reverse(path.begin(), path.end());
		if (path.size() != m / 2 + 1) path.clear();
	}
	return path;
}
// Euler path directed (path to use once all edges)
// the in-degree - out-degree == 0 for all nodes (euler cycle)
// or only exists two nodes with |in-degree - out-degree| == 1 (euler path)
vector<int> euler_path(vector<vector<int>> G, int s = 0){
	int n = G.size(), m = 0;
	vector<int> deg(n);
	for (int u = 0; u < n; ++u){
		m += G[u].size();
		for (auto v : G[u])
			--deg[v];           //  in-deg
		deg[u] += G[u].size();  // out-deg
	}

	vector<int> path;
	int k = n - count(deg.begin(), deg.end(), 0);
	if (k == 0 || (k == 2 && deg[s] == 1)){
		function<void(int)> visit = [&](int u){
			while (!G[u].empty()){
				int v = G[u].back();
				G[u].pop_back();
				visit(v);
			}
			path.push_back(u);
		};
		visit(s);
		reverse(path.begin(), path.end());
		if (path.size() != m + 1) path.clear();
	}
	return path;
}
