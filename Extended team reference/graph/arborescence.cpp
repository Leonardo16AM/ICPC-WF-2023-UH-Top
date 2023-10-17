/*
	Minimum Arborescence
	Tested: UVA 11183
	Complexity: O(m log n)
*/

template<typename T>
struct edge
{
	int src, dst;
	T weight;
};

template<typename T>
struct skew_heap
{
	struct node
	{
		node *ch[2];
		edge<T> key;
		T delta;
	}*root;

	skew_heap() : root(nullptr) {}

	void propagate(node *a)
	{
		a->key.weight += a->delta;
		if (a->ch[0])
			a->ch[0]->delta += a->delta;
		if (a->ch[1])
			a->ch[1]->delta += a->delta;
		a->delta = 0;
	}

	node *merge(node *a, node *b)
	{
		if (!a || !b)
			return a ? a : b;
		propagate(a);
		propagate(b);
		if (a->key.weight > b->key.weight)
			swap(a, b);
		a->ch[1] = merge(b, a->ch[1]);
		swap(a->ch[0], a->ch[1]);
		return a;
	}

	void push(edge<T> key)
	{
		node *n = new node();
		n->ch[0] = n->ch[1] = 0;
		n->key = key;
		n->delta = 0;
		root = merge(root, n);
	}

	void pop()
	{
		propagate(root);
		root = merge(root->ch[0], root->ch[1]);
	}

	edge<T> top()
	{
		propagate(root);
		return root->key;
	}

	bool empty()
	{
		return !root;
	}

	void add(T delta)
	{
		root->delta += delta;
	}

	void merge(skew_heap x)
	{
		root = merge(root, x.root);
	}
};

template<typename T>
struct minimum_aborescense
{
	vector<edge<T>> edges;

	void add_edge(int src, int dst, T weight)
	{
		edges.push_back({ src, dst, weight });
	}

	T solve(int r)
	{
		int n = 0;
		for (auto e : edges)
			n = max(n, max(e.src, e.dst) + 1);

		union_find uf(n);
		vector<skew_heap<T>> heap(n);
		for (auto e : edges)
			heap[e.dst].push(e);

		T score = 0;
		vector<int> seen(n, -1);
		seen[r] = r;
		for (int s = 0; s < n; ++s)
		{
			vector<int> path;
			for (int u = s; seen[u] < 0;)
			{
				path.push_back(u);
				seen[u] = s;
				if (heap[u].empty())
					return numeric_limits<T>::max();

				edge<T> min_e = heap[u].top();
				score += min_e.weight;
				heap[u].add(-min_e.weight);
				heap[u].pop();

				int v = uf.root(min_e.src);
				if (seen[v] == s)
				{
					skew_heap<T> new_heap;
					while (1)
					{
						int w = path.back();
						path.pop_back();
						new_heap.merge(heap[w]);
						if (!uf.join(v, w))
							break;
					}
					heap[uf.root(v)] = new_heap;
					seen[uf.root(v)] = -1;
				}
				u = uf.root(v);
			}
		}

		return score;
	}
};
