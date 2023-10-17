/*
    Treap implementation.
    jcg solution of Robotic Sort
*/

const int oo = 0x3f3f3f3f;

struct node
{
    pair<int, int> val, mn;
    int prio, size, rev;
    node *l, *r;

    node(pair<int, int> val) : val(val), mn(val), prio(rand()), 
                                size(1), rev(0), l(0), r(0) {}
};

int size(node *u)
{
    return u ? u->size : 0;
}

pair<int, int> mn(node *u)
{
    return u ? u->mn : make_pair(oo, oo);
}

node *update(node *u)
{
    if (u)
    {
        // Change this
        u->mn = min({u->val, mn(u->l), mn(u->r)});
        u->size = 1 + size(u->l) + size(u->r);
    }

    return u;
}

void push(node *u)
{
    if (!u) return;

    // Change this

    if (u->rev)
    {
        swap(u->l, u->r);
        if (u->l) u->l->rev = !u->l->rev;
        if (u->r) u->r->rev = !u->r->rev;
        u->rev = 0;
    }
}

node *merge(node *u, node *v)
{
    push(u); push(v);

    if (!u || !v) return u ? u : v;

    if (u->prio > v->prio)
    {
        u->r = merge(u->r, v);
        return update(u);
    }
    else
    {
        v->l = merge(u, v->l);
        return update(v);
    }
}

pair<node*, node*> split(node *u, int k)
{
    push(u);

    if (!u) return make_pair(nullptr, nullptr);

    if (size(u->l) >= k)
    {
        auto p = split(u->l, k);
        u->l = p.second;
        return make_pair(p.first, update(u));
    }
    else
    {
        auto p = split(u->r, k - size(u->l) - 1);
        u->r = p.first;
        return make_pair(update(u), p.second);
    }
}

int find_min(node *u)
{
    push(u);

    if (u->mn == u->val)
        return size(u->l);
    if (u->mn == mn(u->l))
        return find_min(u->l);
    return 1 + size(u->l) + find_min(u->r);
}


void dfs(node *u){
    // Debug

    if (u){
        push(u);
        if (u->l) dfs(u->l);
        cout << u->val << endl;
        if (u->r) dfs(u->r);
    }
}

int main()
{
    node *root = nullptr;

    for (int i = 1; i <= N; ++i)
    {
        int P;
        cin >> P;

        node *u = new node(make_pair(P, i));

        root = merge(root, update(u));
    }

    for (int i = 1; i <= N; ++i)
    {
        int k = find_min(root);

        cout << i + k << " \n"[i == N];

        pair<node*, node*> a = split(root, k);
        pair<node*, node*> b = split(a.second, 1);

        if (a.first) a.first->rev = !a.first->rev;
        root = merge(a.first, b.second);

        delete b.first;
    }
}
