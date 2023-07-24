template <typename T>
struct ABI{
    vector< T > abi1,abi2;
    int n;

    ///queries and updates are 1-indexed
    ABI(int _n) : abi1(_n),abi2(_n),n(_n) {}
    ABI() : abi1(0),abi2(0),n(0) {}

    ll query(int l,int r)
    {
        return query(r)-query(l-1);
    }

    ll query(ll p)
    {
        ll res=query(p,abi1)*p;
        res+=query(p,abi2);
        return res;
    }

    void update(int l,int r,ll v)
    {
        update(l,v,abi1);
        update(r+1,-v,abi1);

        update(l,v*(l-1),abi2);
        update(r+1,v*r,abi2);
    }

    ll query(int p,vector<ll>& abi)
    {
        ll res=0;
        while(p)
        {
            res+=abi[p];
            p-=(p&-p);
        }
        return res;
    }

    void update(int p,ll v,vector<ll>& abi)
    {
        while(p<n)
        {
            abi[p]+=v;
            p+=(p&-p);
        }
    }
};
