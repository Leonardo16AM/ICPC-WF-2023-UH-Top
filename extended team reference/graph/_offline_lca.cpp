/*
	Tested: SPOJ LCA
	Complexity: O((n + m) A(n))
*/

struct query
{
	int u, v, a;
};

struct tree
{
	int n;
	vector<vector<int>> adj;

	tree(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
		adj[dst].push_back(src);
	}

	void lca(vector<query> &queries)
	{
		vector<vector<query*>> Q(n);
		for (auto &q : queries)
		{
			Q[q.u].push_back(&q);
			Q[q.v].push_back(&q);
		}

		union_find uf(n);
		vector<int> anc(n), color(n);
		iota(anc.begin(), anc.end(), 0);

		function<void(int, int)> rec = [&](int u, int p)
		{
			for (int v : adj[u])
				if (v != p)
				{
					rec(v, u);
					uf.join(u, v);
					anc[uf.root(u)] = u;
				}
			color[u] = 1;
			for (auto it : Q[u])
			{
				if (it->u != u) swap(it->u, it->v);
				if (color[it->v] == 1) it->a = anc[uf.root(it->v)];
			}
		};

		rec(0, -1);
	}
};
