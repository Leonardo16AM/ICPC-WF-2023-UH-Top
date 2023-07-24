/*
	Minimum Arborescence (Chu-Liu/Edmonds)
	Tested: UVA 11183
	Complexity: O(mn)
*/

template<typename T>
struct minimum_aborescense
{
	struct edge
	{
		int src, dst;
		T weight;
	};

	vector<edge> edges;

	void add_edge(int u, int v, T w)
	{
		edges.push_back({ u, v, w });
	}

	T solve(int r)
	{
		int n = 0;
		for (auto e : edges)
			n = max(n, max(e.src, e.dst) + 1);

		int N = n;

		for (T res = 0;;)
		{
			vector<edge> in(N, { -1, -1, numeric_limits<T>::max() });
			vector<int> C(N, -1);
			for (auto e : edges) // cheapest comming edges
				if (in[e.dst].weight > e.weight)
					in[e.dst] = e;

			in[r] = {r, r, 0};
			for (int u = 0; u < N; ++u)
			{ // no comming edge ==> no aborescense
				if (in[u].src < 0)
					return numeric_limits<T>::max();
				res += in[u].weight;
			}

			vector<int> mark(N, -1); // contract cycles
			int index = 0;
			for (int i = 0; i < N; ++i)
			{
				if (mark[i] != -1)
					continue;
				int u = i;
				while (mark[u] == -1)
				{
					mark[u] = i;
					u = in[u].src;
				}
				if (mark[u] != i || u == r)
					continue;
				for (int v = in[u].src; u != v; v = in[v].src)
					C[v] = index;
				C[u] = index++;
			}

			if (index == 0)
				return res; // found arborescence
			for (int i = 0; i < N; ++i) // contract
				if (C[i] == -1)
					C[i] = index++;

			vector<edge> next;
			for (auto &e : edges)
				if (C[e.src] != C[e.dst] && C[e.dst] != C[r])
					next.push_back({ C[e.src], C[e.dst], 
						e.weight - in[e.dst].weight });
			edges.swap(next);
			N = index;
			r = C[r];
		}
	}
};
