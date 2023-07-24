/*
    1-indexed functions
    This treap extends array functionalities and may also support segment-tree functions

    Tested:
        https://codeforces.com/contest/863/submission/83569849
*/

typedef ll T;

mt19937 rng(time(0));
struct node
{
    node *l, *r, *p;
    int sz, prior;
    bool rev;
    T v;
    ll lazy, sum;
    node(T v) : v(v), l(0), r(0), sz(1), prior(rng()), sum(v), lazy(0), p(0) {}
};
typedef node *pnode;

// template<typename T>
struct treap
{
    pnode root;
    treap() : root(0) {}

    int sz(pnode p) { return p ? p->sz : 0; }
    int size() { return sz(root); }
    int sum(pnode p)
    {
        if (p)
        {
            push(p);
            return p->sum;
        }
        return 0;
    }

    void update(pnode p)
    {
        if (!p)
            return;
        p->sz = 1 + sz(p->l) + sz(p->r);
        p->sum = (p->v + sum(p->l) + sum(p->r));
        if (p->sum >= mod)
            p->sum -= mod;
        if (p->sum >= mod)
            p->sum -= mod;
        if (p->l)
            p->l->p = p;
        if (p->r)
            p->r->p = p;
        p->p = 0;
    }

    void push(pnode p)
    {
        if (!p)
            return;
        if (p->rev)
        {
            swap(p->l, p->r);
            if (p->l)
                p->l->rev ^= 1;
            if (p->r)
                p->r->rev ^= 1;
            p->rev = 0;
        }
        if (p->lazy)
        {
            p->v = (p->v + p->lazy);
            if (p->v >= mod)
                p->v -= mod;
            p->sum = (p->sum + sz(p) * p->lazy) % mod;
            if (p->l)
            {
                p->l->lazy = (p->l->lazy + p->lazy);
                if (p->l->lazy >= mod)
                    p->l->lazy -= mod;
            }
            if (p->r)
            {
                p->r->lazy = (p->r->lazy + p->lazy);
                if (p->r->lazy >= mod)
                    p->r->lazy -= mod;
            }
            p->lazy = 0;
        }
    }

    void split(pnode p, int key, pnode &l, pnode &r)
    {
        push(p);
        if (!p)
        {
            l = r = 0;
            return;
        }
        int cur_pos = sz(p->l);
        if (key <= cur_pos)
        {
            split(p->l, key, l, p->l);
            r = p;
        }
        else
        {
            split(p->r, key - cur_pos - 1, p->r, r);
            l = p;
        }
        update(p);
    }

    void merge(pnode &p, pnode l, pnode r)
    {
        push(l);
        push(r);
        if (!l || !r)
        {
            if (l)
                p = l;
            else
                p = r;
        }
        else if (l->prior > r->prior)
        {
            merge(l->r, l->r, r);
            p = l;
        }
        else
        {
            merge(r->l, l, r->l);
            p = r;
        }
        update(p);
    }

    /// 0 means at the begining of the treap(array)
    void insert(T v, int pos)
    {
        pos = max(0, pos);
        pos = min(sz(root), pos);
        pnode it = new node(v);
        pnode l, r;
        split(root, pos, l, r);
        merge(l, l, it);
        merge(root, l, r);
    }

    void insert(pnode it, int pos)
    {
        pnode l, r;
        split(root, pos, l, r);
        merge(l, l, it);
        merge(root, l, r);
    }

    void erase(int pos) { erase_interval(pos, pos); }

    void erase_interval(int l, int r)
    {
        if (l > r)
            swap(l, r);
        if (l <= 0 || r > sz(root))
            return;

        pnode pl, pr, _discard;
        split(root, l - 1, pl, pr);
        split(pr, r - l + 1, _discard, pr);
        merge(root, pl, pr);
    }

    void reverse(int l, int r)
    {
        pnode l1, r1, m;
        split(root, l - 1, l1, r1);
        split(r1, r - l + 1, m, r1);
        m->rev ^= 1;
        merge(r1, m, r1);
        merge(root, l1, r1);
    }

    /// intervals have to be disjoint and non-empty
    ///(both ends inclusive: [l1,r1]->[l2,r2])
    void swap_intervals(int l1, int r1, int l2, int r2)
    {
        if (l1 > l2)
        {
            swap(l1, l2);
            swap(r1, r2);
        }
        pnode i1, i2;
        pnode m1, m2, m3;

        split(root, l1 - 1, m1, i1);
        split(i1, r1 - l1 + 1, i1, m2);
        split(m2, l2 - r1 - 1, m2, i2);
        split(i2, r2 - l2 + 1, i2, m3);

        merge(m1, m1, i2);
        merge(m1, m1, m2);
        merge(m3, i1, m3);
        merge(root, m1, m3);
    }

    /// position has to exist(1<=i<=sz(root))
    T operator[](int i)
    {
        assert(1 <= i && i <= sz(root));
        return find_kth(root, i)->v;
    }

    void assign(T v, int pos)
    {
        pnode p = find_kth(root, pos);
        p->v = v;
    }

    pnode find_kth(pnode p, int k)
    {
        push(p);
        if (sz(p->l) < k - 1)
            return find_kth(p->r, k - sz(p->l) - 1);
        else if (sz(p->l) == k - 1)
            return p;
        return find_kth(p->l, k);
    }

    void app(int l, int r, ll v)
    {
        pnode li, mi, ri;
        split(root, l - 1, li, mi);
        split(mi, r - l + 1, mi, ri);
        mi->lazy = (mi->lazy + v) % mod;
        merge(mi, mi, ri);
        merge(root, li, mi);
    }

    ll query(int l, int r)
    {
        pnode li, mi, ri;
        split(root, l - 1, li, mi);
        split(mi, r - l + 1, mi, ri);
        push(mi);
        ll res = mi->sum;
        merge(mi, mi, ri);
        merge(root, li, mi);
        return res;
    }

    int index(pnode p)
    {
        int res = 1;
        push(p);
        if (p->l)
            res += sz(p->l);
        pnode last = p;
        p = p->p;
        while (p)
        {
            if (p->rev)
            {
                swap(p->l, p->r);
                if (p->l)
                    p->l->rev ^= 1;
                if (p->r)
                    p->r->rev ^= 1;
                p->rev = 0;

                res = (sz(last) + 1 - res);
            }
            if (last == p->r)
                res += sz(p->l) + 1;
            last = p;
            p = p->p;
        }
        return res;
    }

    void imp(pnode p)
    {
        if (!p)
            return;
        imp(p->l);
        cout << p->v << ' ' << p->sum << ' ' << p->lazy << ' ' << p->sz << '\n';
        imp(p->r);
    }
};
