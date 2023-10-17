/*
    Tested:
        https://codeforces.com/gym/102220/submission/83818012
*/

template <typename T>
struct ST
{
    vector<T> st, lazy;
    int sz;
    T neutroL;

    ST(int n, T neutrol) : sz(n), st(4 * n), lazy(4 * n), neutroL(neutrol) {}

    T merge(T v1, T v2)
    {
        /// up to code
    }

    void up(int p, int l, int r, T v)
    {
        /// up to code
    }

    void push(int p, int l, int r)
    {
        if (l == r)
        {
            lazy[p] = neutroL;
            return;
        }
        if (lazy[p] == neutroL)
            return;
        ///(basic) up to code
        T v = lazy[p];
        up((p << 1), l, (l + r) >> 1, v);
        up((p << 1) + 1, ((l + r) >> 1) + 1, r, v);
        lazy[p] = neutroL;
    }

    void build(vector<T> &arr) { build(1, 0, sz - 1, arr); }

    void build(int p, int l, int r, vector<T> &arr)
    {
        if (l == r)
        {
            st[p] = arr[l];
            lazy[p] = neutroL;
            return;
        }
        int mid = (l + r) >> 1;

        build(p << 1, l, mid, arr);
        build((p << 1) + 1, mid + 1, r, arr);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
        lazy[p] = neutroL;
    }

    void build(T *arr) { build(1, 0, sz - 1, arr); }

    void build(int p, int l, int r, T *arr)
    {
        if (l == r)
        {
            st[p] = arr[l];
            lazy[p] = neutroL;
            return;
        }
        int mid = (l + r) >> 1;

        build(p << 1, l, mid, arr);
        build((p << 1) + 1, mid + 1, r, arr);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
        lazy[p] = neutroL;
    }

    void update(int L, int R, T v) { update(1, 0, sz - 1, L, R, v); }

    void update(int p, int l, int r, int L, int R, T v)
    {
        if (L <= l && r <= R)
        {
            up(p, l, r, v);
            return;
        }
        push(p, l, r);

        int mid = (l + r) >> 1;

        if (L <= mid)
            update(p << 1, l, mid, L, R, v);
        if (R > mid)
            update((p << 1) + 1, mid + 1, r, L, R, v);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
    }

    T query(int L, int R) { return query(1, 0, sz - 1, L, R); }

    T query(int p, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
            return st[p];
        push(p, l, r);

        int mid = (l + r) >> 1;

        if (R <= mid)
            return query(p << 1, l, mid, L, R);
        if (L > mid)
            return query((p << 1) + 1, mid + 1, r, L, R);
        return merge(query(p << 1, l, mid, L, R), query((p << 1) + 1, mid + 1, r, L, R));
    }
};
