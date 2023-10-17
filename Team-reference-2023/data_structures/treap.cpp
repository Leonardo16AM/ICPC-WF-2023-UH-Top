// capacity MUST be correct if you use new_node
template<class node, bool persistent, int capacity = 0>
struct treap{
	inline int size(node *u) { return u ? u->nod.sz : 0; }
	inline void push(node *u){
		if (u->lazy()){
			if (u->l) u->l = clone(u->l), u->l->apply(u->lazy);
			if (u->r) u->r = clone(u->r), u->r->apply(u->lazy);
			u->lazy = typename node::lazy_container();
		}
	}
	node* update(node *u){
		u->nod = typename node::node_container(u->key);
		if (u->l) u->nod = node::merge(u->l->nod, u->nod);
		if (u->r) u->nod = node::merge(u->nod, u->r->nod);
		return u;
	}
	// split for the kth first elements
	pair<node*, node*> split(node* u, int k){
		if (!u) return { u, u };
		u = clone(u); push(u);
		if (size(u->l) >= k){
			auto s = split(u->l, k);
			u->l = s.second;
			return { s.first, update(u) };
		}
		auto s = split(u->r, k - size(u->l) - 1);
		u->r = s.first;
		return { update(u), s.second };
	}
	node* merge(node *u, node *v){
		if (!u || !v) return u ? u : v;
		if (u->prio > v->prio){
			u = clone(u); push(u);
			u->r = merge(u->r, v);
			return update(u);
		}
		v = clone(v); push(v);
		v->l = merge(u, v->l);
		return update(v);
	}
	node* kth(node *u, int k){
		while (u && size(u->l) + 1 != k){
			push(u);
			if (size(u->l) >= k) u = u->l;
			else k -= size(u->l) + 1, u = u->r;
		}
		return u;
	}
	int less(node *u, const typename node::key_container &ky){
		int l = 0;
		while (u){
			push(u);
			if (u->key < ky) l += size(u->l) + 1, u = u->r;
			else u = u->l;
		}
		return l;
	}
	/*int pos(node *u) // require parents (set parent to NULL 
	in update and fix child->p){
		int r = size(u->l);
		while (u->p != NULL){
			if (u->p->r == u)
				r += size(u->p->l) + 1;
			u = u->p;
		}
		return r;
	}*/
	node* clone(node *u){return !persistent ? u : new_node(*u);}
	vector<node> nodes;
	treap() { nodes.reserve(capacity); }
	node* new_node(node u){nodes.emplace_back(u);return &nodes.back();}
};
struct node{
	struct key_container{int x;} key;
	struct node_container{ int sz;
		node_container(const key_container &k = {}) : sz(1) {}
	} nod;
	struct lazy_container{ int add;
		bool operator()() { return add != 0; }
		lazy_container(int add = 0) : add(add) {}
	} lazy;
	static node_container merge(const node_container &lhs, 
								const node_container &rhs){
		node_container x;
		x.sz = lhs.sz + rhs.sz;
		return x;
	}
	void apply(const lazy_container &p){
		key.x += p.add; lazy.add += p.add;
	}
	node *l, *r;
	int prio;
	node(const key_container &x) : key(x), nod(x){
		l = r = NULL; prio = randint(0, 1'000'000);
	}
};
