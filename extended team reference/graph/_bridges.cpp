/*
	Tested: AIZU(judge.u-aizu.ac.jp) GRL_3_B
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

void bridge_components(const graph &g)
{
	vector<int> num(g.n), low(g.n), stk;
	vector<vector<int>> comps;

	function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
	{
		num[u] = low[u] = ++t;
		stk.push_back(u);
		for (int v : g.adj[u])
		{
			if (v == p) continue;
			if (num[v] == 0)
			{
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);
			}
			else low[u] = min(low[u], num[v]);
		}

		if (low[u] == num[u])
		{
			comps.push_back({});
			do
			{
				comps.back().push_back(stk.back());
				stk.pop_back();
			}
			while (comps.back().back() != u);
		}
	};

	for (int u = 0, t; u < g.n; ++u)
		if (num[u] == 0) dfs(u, -1, t = 0);
}
