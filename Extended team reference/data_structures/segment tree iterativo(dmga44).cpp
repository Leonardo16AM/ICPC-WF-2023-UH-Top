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

    void build(T *arr)
    {
        for(int i=0;i<sz;i++)
            st[i+sz]=arr[i];
        for(int i=sz-1;i>=1;i--)
            st[i]=merge(st[i*2],st[i*2+1]);
    }

    void update(int pos,T v)
    {
        pos+=sz;
        up(pos,v);
        pos>>=1;
        while(pos)
        {
            st[pos]=merge(st[(pos<<1)],st[(pos<<1)+1]);
            pos>>=1;
        }
    }

    T query(int l,int r)
    {
        int ma=st[l];
        l+=sz;
        r+=sz;
        while(l<=r)
        {
            ma=merge(ma,st[l]);
            ma=merge(ma,st[r]);
            l=(l>>1)+(l&1);
            r=(r>>1)-(!(r&1));
        }
        return ma;
    }
};
