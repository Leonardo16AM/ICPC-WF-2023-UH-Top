/*
	Bridges / Bridges connected components

	Description:
	- Let G = (V, E). If G-(u,v) is disconnected, (u,v) in V is said to
	be a bridge.
	- Bridge-blocks or bridge-connected components are the components of
	G formed by deleting all the bridges. The bridge-blocks partition V
	in equivalences classes such that two vertices are in the same class
	if and only if there is a (not necessarily simple) cycle of G
	containing both of them.
	The algorithm finds all briges and bridge-blocks.

	Complexity: O(n + m)

	Tested: http://codeforces.com/gym/100114/problem/J
*/

struct graph
{
	int n;
	vector<vector<int>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int>& operator[](int u) { return adj[u]; }
};

vector<vector<int>> bridge_blocks(graph &adj)
{
	int n = adj.n;

	vector<int> num(n), low(n), stk;
	vector<vector<int>> comps;
	vector<pair<int, int>> bridges;

	function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
	{
		num[u] = low[u] = ++t;
		stk.push_back(u);

		// remove if there isn't parallel edges
		sort(adj[u].begin(), adj[u].end()); 

		for (int i = 0, sz = adj[u].size(); i < sz; ++i)
		{
			int v = adj[u][i];

			if (v == p)
			{
				if (i + 1 < sz && adj[u][i + 1] == v)
					low[u] = min(low[u], num[v]);
				continue;
			}

			if (!num[v])
			{
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);

				if (low[v] == num[v])
					bridges.push_back({u, v});
			}
			else low[u] = min(low[u], num[v]);
		}

		if (num[u] == low[u])
		{
			comps.push_back({});
			for (int v = -1; v != u; stk.pop_back())
				comps.back().push_back(v = stk.back());
		}
	};

	for (int u = 0, t; u < n; ++u)
		if (!num[u]) dfs(u, -1, t = 0);

	// this is for build the bridge-block tree
	function<graph()> build_tree = [&]()
	{
		vector<int> id(n);

		for (int i = 0; i < (int) comps.size(); ++i)
			for (int u : comps[i]) id[u] = i;

		graph tree(comps.size());

		for (auto &e : bridges)
			tree.add_edge(id[e.first], id[e.second]);

		return tree;
	};

	return comps;
}
