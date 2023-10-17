/*
	Articulation points / Biconnected components
	Tested: SPOJ SUBMERGE
	Complexity: O(n + m)
*/

struct graph
{
	int n;
	vector<vector<int>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
		adj[dst].push_back(src);
	}
};

vector<int> arts(g.n);
vector<vector<int>> comps;

void biconnected_components(const graph &g)
{
	vector<int> num(g.n), low(g.n), S;
	function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
	{
		num[u] = low[u] = ++t;
		S.push_back(u);
		for (int v : g.adj[u])
		{
			if (v == p) continue;
			if (num[v] == 0)
			{
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);
				if (num[u] <= low[v])
				{
					if (num[u] != 1 || low[v] > 2) arts[u] = true;
					for (comps.push_back({u});
						comps.back().back() != v; S.pop_back())
					comps.back().push_back(S.back());
				}
			}
			else low[u] = min(low[u], num[v]);
		}
	};
	for (int u = 0, t; u < g.n; ++u)
		if (num[u] == 0)
			dfs(u, -1, t = 0);
}
