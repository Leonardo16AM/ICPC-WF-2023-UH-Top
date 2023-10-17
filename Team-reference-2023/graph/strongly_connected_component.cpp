// returns which nodes that belong to each scc
vector<vector<int>> strongly_connected_components(const vector<vector<int>> &g){
	int n = g.size();
	vector<vector<int>> scc;
	vector<int> S, B, I(n, -1);
	function<void(int)> dfs = [&](int u){
		B.push_back(I[u] = S.size());
		S.push_back(u);
		for (int v : g[u]){
			if (!~I[v]) dfs(v);
			else while (I[v] < B.back()) B.pop_back();
		}
		if (I[u] == B.back()){
			scc.push_back({});
			B.pop_back();
			while (I[u] < (int)S.size()){
				scc.back().push_back(S.back());
				I[S.back()] = n + scc.size();
				S.pop_back();
			}
		}
	};
	for (int u = 0; u < n; ++u)	if (!~I[u]) dfs(u);
	return scc;
}