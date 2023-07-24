vector<int> euler_path(const vector<vector<pair<int, int>>> &G, int s = 0)
{
    int n = G.size(), odd = 0, m = 0;
    for (int i = 0; i < n; ++i)
    {
        odd += G[i].size() & 1;
        m += G[i].size();
    }

    vector<int> path;
    if (odd == 0 || (odd == 2 && (G[s].size() & 1) == 1))
    {
        vector<int> pos(n);
        vector<bool> mark(m / 2);
        function<void(int)> visit = [&](int u) {

            for (int v, id; pos[u] < G[u].size();)
            {
                tie(v, id) = G[u][pos[u]++];
                if (!mark[id])
                {
                    mark[id] = true;
                    visit(v);
                }
            }
            path.push_back(u);
        };
        visit(s);
        reverse(path.begin(), path.end());

        if (path.size() != m / 2 + 1)
            path.clear();
    }
    return path;
}
