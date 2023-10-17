/*
	Vantage Point Tree (vp tree)

	Description:
	Vantage point tree is a metric tree.
	Each tree node has a point, radius, and two childs.
	The points of left descendants are contained in the ball B(p,r)
	and the points of right descendants are excluded from the ball.

	We can find k-nearest neighbors of a given point p efficiently
	by pruning search.

	Complexity:
	Construction: O(n log n)
	Search: O(log n)
*/

typedef complex<double> point;

namespace std
{
	bool operator <(point p, point q)
	{
		if (real(p) != real(q))
			return real(p) < real(q);
		return imag(p) < imag(q);
	}
}

struct vantage_point_tree
{
	struct node
	{
		point p;
		double th;
		node *l, *r;
	}*root;

	vector<pair<double, point>> aux;

	vantage_point_tree(vector<point> ps)
	{
		for (int i = 0; i < ps.size(); ++i)
			aux.push_back({ 0, ps[i] });
		root = build(0, ps.size());
	}

	node *build(int l, int r)
	{
		if (l == r)
			return 0;
		swap(aux[l], aux[l + rand() % (r - l)]);
		point p = aux[l++].second;
		if (l == r)
			return new node({ p });
		for (int i = l; i < r; ++i)
			aux[i].first = norm(p - aux[i].second);
		int m = (l + r) / 2;
		nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
		return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
	}

	priority_queue<pair<double, node*>> que;

	void k_nn(node *t, point p, int k)
	{
		if (!t)
			return;
		double d = abs(p - t->p);
		if (que.size() < k)
			que.push({ d, t });
		else if (que.top().first > d)
		{
			que.pop();
			que.push({ d, t });
		}
		if (!t->l && !t->r)
			return;
		if (d < t->th)
		{
			k_nn(t->l, p, k);
			if (t->th - d <= que.top().first)
				k_nn(t->r, p, k);
		}
		else
		{
			k_nn(t->r, p, k);
			if (d - t->th <= que.top().first)
				k_nn(t->l, p, k);
		}
	}

	vector<point> k_nn(point p, int k)
	{
		k_nn(root, p, k);
		vector<point> ans;
		for (; !que.empty(); que.pop())
			ans.push_back(que.top().second->p);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};
