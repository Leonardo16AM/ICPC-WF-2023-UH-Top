void tarjan(const vector<vector<int>> &adj){
    int n = adj.size(), t;
    vector<int> num(n), low(n), S;
    vector<bool> arts(n);
    vector<pair<int, int>> bridges;
    vector<vector<int>> comps; // biconnected components
    function<void(int, int)> dfs = [&](int u, int p){
        num[u] = low[u] = ++t;
        S.push_back(u);
        for (int v : adj[u])
            if (v != p){
                if (!num[v]){
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    if (num[u] <= low[v]){
                        if (num[u] != 1 || num[v] > 2) 
                        	arts[u] = true;
                        for (comps.push_back({u}); 
                        	comps.back().back() != v; 
                        	S.pop_back())
                            comps.back().push_back(S.back());
                    }
                    if (num[u] < low[v]) bridges.push_back({ u, v });
                }
                else low[u] = min(low[u], num[v]);
            }
    };
    for (int u = 0; u < n; ++u)
        if (!num[u]) t = 0, dfs(u, -1);
}