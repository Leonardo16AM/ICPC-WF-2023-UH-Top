//tested: https://codeforces.com/group/4zVk9dZl6Q/contest/391621/submission/166743883

struct PersistentImplicitST
{
    struct node
    {
        ll l,r;
        ll sum;
        node *ls,*rs;
        node(ll liml,ll limr) : l(liml),r(limr),ls(0),rs(0),sum(0) {}
    };

    typedef node* pnode;
    vector<pnode> root;
    int versionCount;

    PersistentImplicitST(ll liml,ll limr)
    {
        root.push_back(new node(liml,limr));
        versionCount=1;
    }

    pnode clone(pnode p)
    {
        if(!p)
            return 0;
        pnode ans=new node(p->l,p->r);
        ans->sum=p->sum;
        ans->ls=p->ls;
        ans->rs=p->rs;
        return ans;
    }

    ll sum(pnode p)
    {
        if(!p)
            return 0;
        return p->sum;
    }

    void update(ll pos,ll v)
    {
        root.push_back(update(root.back(),pos,v));
    }

    void update(int ver,ll pos,ll v)
    {
        root.push_back(update(root[ver],pos,v));
    }

    pnode update(pnode p,ll pos,ll v)
    {
        ll l=p->l;
        ll r=p->r;
        if(l>pos || r<pos)
            return p;
        
        p=clone(p);
        if(l==r && l==pos)
        {
            p->sum+=v;
            return p;
        }

        ll mid=(l+r)>>1;
        if(pos<=mid)
        {
            if(!p->ls)
                p->ls=new node(l,mid);
            p->ls=update(p->ls,pos,v);
        }
        else
        {
            if(!p->rs)
                p->rs=new node(mid+1,r);
            p->rs=update(p->rs,pos,v);
        }
        p->sum=sum(p->ls)+sum(p->rs);
        return p;
    }

    ll query(ll L,ll R)
    {
        return query(root.back(),L,R);
    }

    ll query(int ver,ll L,ll R)
    {
        return query(root[ver],L,R);
    }

    ll query(pnode p,ll L,ll R)
    {
        if(!p)
            return 0;
        ll l=p->l;
        ll r=p->r;
        if(L<=l && r<=R)
            return p->sum;
        if(l>R || L>r)
            return 0;

        ll mid=(l+r)>>1;
        return query(p->ls,L,R)+query(p->rs,L,R);
    }
};
