///testeado en codechef
///con fractional cascading(query en log(n))
struct st2d
{
    vector<vector< vector< int > > > st;
    int sz;

    st2d (vector<int>& v)
    {
        sz=v.size();
        st=vector<vector< vector< int > > >(4*sz,vector< vector< int > >(5,vector<int>(0)));
        build(1,0,sz-1,v);
    }

    void build(int p,int l,int r,vector<int>& base)
    {
        if(l==r)
        {
            st[p][0].push_back(base[l]);
            return;
        }
        int mid=(l+r)>>1;
        int ls=p<<1;
        int rs=(p<<1)+1;

        build(ls,l,mid,base);
        build(rs,mid+1,r,base);

        int pl=0,pr=0;
        while(pl<st[ls][0].size() && pr<st[rs][0].size())
        {
            if(st[ls][0][pl]<st[rs][0][pr])
            {
                st[p][0].push_back(st[ls][0][pl]);
                pl++;
            }
            else
            {
                st[p][0].push_back(st[rs][0][pr]);
                pr++;
            }
        }

        while(pl<st[ls][0].size())
        {
            st[p][0].push_back(st[ls][0][pl]);
            pl++;
        }

        while(pr<st[rs][0].size())
        {
            st[p][0].push_back(st[rs][0][pr]);
            pr++;
        }

        for(int i=1;i<5;i++)
            st[p][i].resize(st[p][0].size());
        int act=0;
        for(auto son :{ls,rs})
            for(int add : {0,1})
            {
                int pos=0;
                act++;
                for(int i=0;i<st[p][0].size();i++)
                {
                    int v=st[p][0][i];
                    while(pos<st[son][0].size() && st[son][0][pos]<v+add)
                        pos++;
                    st[p][act][i]=pos;
                }
            }
    }

    ///y1<=y2 must hold
    int query(int l,int r,int y1,int y2) { return query(1,0,sz-1,y1,y2,0,0,l,r);}

    int query(int p,int l,int r,int x,int y,int ll,int lr,int L,int R)
    {
        if(p==1)
        {
            int i0=lower_bound(all(st[1][0]),x)-st[1][0].begin();
            int i1=upper_bound(all(st[1][0]),y)-st[1][0].begin()-1;
//            cout << i0 << ' ' << i1 << '\n';
            int mid=r>>1;

            return query(2,0,mid,x,y,st[1][1][i0],st[1][2][i1]-1,L,R)+query(3,mid+1,r,x,y,st[1][3][i0],st[1][4][i1]-1,L,R);
        }
        if(L<=l && r<=R)
            return lr-ll+1;
        if(l>R || r<L)
            return 0;
        if(lr==ll-1)
            return 0;

        int mid=(l+r)>>1;

        return query(p<<1,l,mid,x,y,st[p][1][ll],st[p][2][lr]-1,L,R)+query((p<<1)+1,mid+1,r,x,y,st[p][3][ll],st[p][4][lr]-1,L,R);
    }
};

///ops fall in [0,n-1] range
struct st2d_abi
{
    vector<vector<int>> abi;
    int sz;

    st2d_abi(vector<int>& v)
    {
        sz=v.size()+1;
        abi=vector<vector<int>>(sz,vector<int>(0));
        for(int i=0;i<sz-1;i++)
            update(i+1,v[i]);
        for(int i=1;i<sz;i++)
            sort(all(abi[i]));
    }

    void update(int p,int v)
    {
        while(p<sz)
        {
            abi[p].push_back(v);
            p+=(p&-p);
        }
    }

    int query(int p,int v)
    {
        int ans=0;
        while(p)
        {
            ans+=upper_bound(all(abi[p]),v)-abi[p].begin();
            p-=(p&-p);
        }
        return ans;
    }

    ///x1<=x2 must hold
    int query(int l,int r,int x1,int x2)
    {
        return query(r+1,x2)-query(r+1,x1-1)-query(l,x2)+query(l,x1-1);
    }
};

