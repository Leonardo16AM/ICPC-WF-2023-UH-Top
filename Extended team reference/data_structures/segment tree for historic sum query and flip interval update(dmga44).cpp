/**
 * @brief
 *
 * Maintains the sum of the previous versions of the value on the position (and interval).
 *
 * Tested: https://codeforces.com/gym/103069/submission/173539704
 * Based on: https://pastebin.com/EcMXt8YV
 */

struct ST
{
    struct node
    {
        ll cant1, cant0;
        ll prevsum, last_update;
        node()
        {
            cant0 = cant1 = prevsum = last_update = 0;
        }
    };

    struct lazyT
    {
        ll time1, time0;
        ll flip, last_update;
        lazyT()
        {
            time1 = time0 = flip = last_update = 0;
        }
    };
    vector<node> st;
    vector<lazyT> lazy;
    int sz;

    ST(int n) : sz(n), st(4 * n), lazy(4 * n)
    {
        build();
    }

    node merge(node v1, node v2)
    {
        node ans;
        ans.cant1 = v1.cant1 + v2.cant1;
        ans.cant0 = v1.cant0 + v2.cant0;
        ans.last_update = v1.last_update;
        ans.prevsum = v1.prevsum + v2.prevsum;
        return ans;
    }

    lazyT combine(lazyT a, lazyT b)
    {
        if (a.last_update == -1e9)
            return b;
        if (a.flip)
        {
            a.time0 += b.time1;
            a.time1 += b.time0;
        }
        else
        {
            a.time0 += b.time0;
            a.time1 += b.time1;
        }
        a.flip ^= b.flip;
        a.last_update = b.last_update;
        return a;
    }

    void up(int p, int l, int r, lazyT v)
    {
        /// up to code
        st[p].prevsum += v.time0 * st[p].cant1 + v.time1 * st[p].cant0;
        st[p].last_update = v.last_update;
        if (v.flip)
            swap(st[p].cant0, st[p].cant1);
        lazy[p] = combine(lazy[p], v);
    }

    ll calc(node p, ll x)
    {
        return p.prevsum + (x - p.last_update) * (p.cant1);
    }

    void push(int p, int l, int r)
    {
        if (l == r)
            return;
        if (lazy[p].last_update == -1e9)
            return;
        ///(basic) up to code
        lazyT v = lazy[p];
        up((p << 1), l, (l + r) >> 1, v);
        up((p << 1) + 1, ((l + r) >> 1) + 1, r, v);
        lazy[p].last_update = -1e9;
    }

    void build() { build(1, 0, sz - 1); }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            st[p].cant0 = 1;
            st[p].cant1 = 0;
            st[p].last_update = -1;
            st[p].prevsum = 0;

            lazy[p].last_update = -1e9;
            return;
        }
        int mid = (l + r) >> 1;

        build(p << 1, l, mid);
        build((p << 1) + 1, mid + 1, r);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
        lazy[p].last_update = -1e9;
    }

    void update(int L, int R, int v) { update(1, 0, sz - 1, L, R, v); }

    void update(int p, int l, int r, int L, int R, int v)
    {
        if (L <= l && r <= R)
        {
            lazyT x;
            x.flip = 1;
            x.time0 = v - st[p].last_update;
            x.time1 = 0;
            x.last_update = v;
            up(p, l, r, x);
            return;
        }
        push(p, l, r);

        int mid = (l + r) >> 1;

        if (L <= mid)
            update(p << 1, l, mid, L, R, v);
        else
        {
            lazyT x;
            x.flip = 0;
            x.time0 = v - st[p << 1].last_update;
            x.time1 = 0;
            x.last_update = v;
            up(p << 1, l, mid, x);
        }
        if (R > mid)
            update((p << 1) + 1, mid + 1, r, L, R, v);
        else
        {
            lazyT x;
            x.flip = 0;
            x.time0 = v - st[(p << 1) + 1].last_update;
            x.time1 = 0;
            x.last_update = v;
            up((p << 1) + 1, mid + 1, r, x);
        }

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
    }

    ll query(int L, int R, ll x) { return query(1, 0, sz - 1, L, R, x); }

    ll query(int p, int l, int r, int L, int R, ll x)
    {
        if (L <= l && r <= R)
            return calc(st[p], x);
        push(p, l, r);

        int mid = (l + r) >> 1;

        if (R <= mid)
            return query(p << 1, l, mid, L, R, x);
        if (L > mid)
            return query((p << 1) + 1, mid + 1, r, L, R, x);
        return query(p << 1, l, mid, L, R, x) + query((p << 1) + 1, mid + 1, r, L, R, x);
    }
};