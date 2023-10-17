/*
    Tested:
        https://codeforces.com/gym/102220/submission/83818012
*/

template <typename T>
struct ST{
    vector< T > st;
    int sz;

    ST (int n) : sz(n),st(4*n) {}

    T merge(T v1,T v2)
    {
        ///up to code
    }

    void up(int p,T v)
    {
        ///up to code
    }

    void build(vector<T> &arr) { build(1, 0, sz - 1, arr); }

    void build(int p, int l, int r, vector<T> &arr)
    {
        if (l == r)
        {
            st[p] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;

        build(p << 1, l, mid, arr);
        build((p << 1) + 1, mid + 1, r, arr);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
    }

    void build(T *arr) { build(1, 0, sz - 1, arr); }

    void build(int p, int l, int r, T *arr)
    {
        if (l == r)
        {
            st[p] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;

        build(p << 1, l, mid, arr);
        build((p << 1) + 1, mid + 1, r, arr);

        st[p] = merge(st[p << 1], st[(p << 1) + 1]);
    }

    void update(int pos,T v) { update(1,0,sz-1,pos,v); }

    void update(int p,int l,int r,int pos,T v)
    {
        if(pos<=l && r<=pos)
        {
            up(p,v);
            return ;
        }
        int mid=(l+r)>>1;

        if(pos<=mid)
            update(p<<1,l,mid,pos,v);
        if(pos>mid)
            update((p<<1)+1,mid+1,r,pos,v);

        st[p]=merge(st[p<<1],st[(p<<1)+1]);
    }

    T query(int L,int R) { return query(1,0,sz-1,L,R); }

    T query(int p,int l,int r,int L,int R)
    {
        if(L<=l && r<=R)
            return st[p];

        int mid=(l+r)>>1;

        if(R<=mid)
            return query(p<<1,l,mid,L,R);
        if(L>mid)
            return query((p<<1)+1,mid+1,r,L,R);
        return merge(query(p<<1,l,mid,L,R),query((p<<1)+1,mid+1,r,L,R));
    }
};
