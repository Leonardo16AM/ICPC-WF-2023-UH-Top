#define mod (ll)(2e9+99)
#define MAXN (ll)(2e5+5)
#define b (ll)(331)

ll po[MAXN];
ll h[MAXN],ih[MAXN];

ll hs(int i,int j,ll* h)
{
    ll h1=h[j+1];
    ll h2=h[i];
    ll res=(h1-((h2*po[j-i+1])%mod)+mod)%mod;
    return res;
}

map<ll,ll> solve(string s)
{
    int n=s.size();
    for(int i=0;i<n;i++)
    {
        h[i+1]=(h[i]*b+s[i])%mod;
        ih[i+1]=(ih[i]*b+s[n-i-1])%mod;
    }

    map<ll,ll> res;
    vector<map<ll,pii>> pos;
    pos.resize(n+2);
    for(int i=0;i<n;i++)
    {
        int sz=1;
        int ma=min(i,n-1-i);
        ma++;
        for(int add=(1<<17);add;add>>=1)
        {
            sz+=add;
            if(sz>ma)
            {
                sz-=add;
                continue;
            }
            if(hs(i-sz+1,i+sz-1,h)!=hs(n-i-1-sz+1,n-i-1+sz-1,ih))
                sz-=add;
        }
        ll ha=hs(i-sz+1,i+sz-1,h);
        res[ha]++;
        if(res[ha]==1)
            pos[2*sz-1][ha]=pii(i-sz+1,i+sz-1);
    }
    for(int i=1;i<n;i++)
    {
        int sz=0;
        int ma=min(i,n-i);
        for(int add=(1<<17);add;add>>=1)
        {
            sz+=add;
            if(sz>ma)
            {
                sz-=add;
                continue;
            }
            if(hs(i-sz,i+sz-1,h)!=hs(n-i-1-sz+1,n-i-1+sz,ih))
                sz-=add;
        }
        if(!sz)
            continue;
        ll ha=hs(i-sz,i+sz-1,h);
        res[ha]++;
        if(res[ha]==1)
            pos[2*sz][ha]=pii(i-sz,i+sz-1);
    }

    for(int i=n;i>=3;i--)
    {
        for(auto y : pos[i])
        {
            ll ha=y.f;
            int l=y.s.f;
            int r=y.s.s;
            ll hb=hs(l+1,r-1,h);
            if(!res[hb])
                pos[i-2][hb]=pii(l+1,r-1);
            res[hb]+=res[ha];
        }
    }

    return res;
}
