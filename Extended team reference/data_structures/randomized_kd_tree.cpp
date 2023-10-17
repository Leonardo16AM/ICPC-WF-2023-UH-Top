
typedef complex<double> point;

struct randomized_kd_tree
{
	struct node
	{
		point p;
		int d, s;
		node *l, *r;
		bool is_left_of(node *x)
		{
			if (x->d)
				return real(p) < real(x->p);
			else
				return imag(p) < imag(x->p);
		}
	}*root;

	randomized_kd_tree() : root(0) {}

	int size(node *t)
	{
		return t ? t->s : 0;
	}

	node *update(node *t)
	{
		t->s = 1 + size(t->l) + size(t->r);
		return t;
	}

	pair<node*, node*> split(node *t, node *x)
	{
		if (!t)
			return {0, 0};
		if (t->d == x->d)
		{
			if (t->is_left_of(x))
			{
				auto p = split(t->r, x);
				t->r = p.first;
				return {update(t), p.second};
			}
			else
			{
				auto p = split(t->l, x);
				t->l = p.second;
				return {p.first, update(t)};
			}
		}
		else
		{
			auto l = split(t->l, x);
			auto r = split(t->r, x);
			if (t->is_left_of(x))
			{
				t->l = l.first;
				t->r = r.first;
				return {update(t), join(l.second, r.second, t->d)};
			}
			else
			{
				t->l = l.second;
				t->r = r.second;
				return {join(l.first, r.first, t->d), update(t)};
			}
		}
	}

	node *join(node *l, node *r, int d)
	{
		if (!l)
			return r;
		if (!r)
			return l;
		if (rand() % (size(l) + size(r)) < size(l))
		{
			if (l->d == d)
			{
				l->r = join(l->r, r, d);
				return update(l);
			}
			else
			{
				auto p = split(r, l);
				l->l = join(l->l, p.first, d);
				l->r = join(l->r, p.second, d);
				return update(l);
			}
		}
		else
		{
			if (r->d == d)
			{
				r->l = join(l, r->l, d);
				return update(r);
			}
			else
			{
				auto p = split(l, r);
				r->l = join(p.first, r->l, d);
				r->r = join(p.second, r->r, d);
				return update(r);
			}
		}
	}

	node *insert(node *t, node *x)
	{
		if (rand() % (size(t) + 1) == 0)
		{
			auto p = split(t, x);
			x->l = p.first;
			x->r = p.second;
			return update(x);
		}
		else
		{
			if (x->is_left_of(t))
				t->l = insert(t->l, x);
			else
				t->r = insert(t->r, x);
			return update(t);
		}
	}

	void insert(point p)
	{
		root = insert(root, new node({ p, rand() % 2 }));
	}

	node *remove(node *t, node *x)
	{
		if (!t)
			return t;
		if (t->p == x->p)
			return join(t->l, t->r, t->d);
		if (x->is_left_of(t))
			t->l = remove(t->l, x);
		else
			t->r = remove(t->r, x);
		return update(t);
	}

	void remove(point p)
	{
		node n = { p };
		root = remove(root, &n);
	}

	void closest(node *t, point p, pair<double, node*> &ub)
	{
		if (!t)
			return;
		double r = norm(t->p - p);
		if (r < ub.first)
			ub = {r, t};
		node *first = t->r, *second = t->l;
		double w = t->d ? real(p - t->p) : imag(p - t->p);
		if (w < 0)
			swap(first, second);
		closest(first, p, ub);
		if (ub.first > w * w)
			closest(second, p, ub);
	}

	point closest(point p)
	{
		pair<double, node*> ub(1.0 / 0.0, 0);
		closest(root, p, ub);
		return ub.second->p;
	}

	// verification
	int height(node *n)
	{
		return n ? 1 + max(height(n->l), height(n->r)) : 0;
	}

	int height()
	{
		return height(root);
	}

	int size_rec(node *n)
	{
		return n ? 1 + size_rec(n->l) + size_rec(n->r) : 0;
	}

	int size_rec()
	{
		return size_rec(root);
	}

	void display(node *n, int tab = 0)
	{
		if (!n)
			return;
		display(n->l, tab + 2);
		for (int i = 0; i < tab; ++i)
			cout << " ";
		cout << n->p << " (" << n->d << ")" << endl;
		display(n->r, tab + 2);
	}

	void display()
	{
		display(root);
	}
};
