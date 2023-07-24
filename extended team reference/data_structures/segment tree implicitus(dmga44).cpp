#include <bits/stdc++.h>
typedef long long ll;

struct ImplicitST
{
    struct node
    {
        ll l,r;
        ll sum;
        node *ls,*rs;
        node(ll liml,ll limr) : l(liml),r(limr),ls(0),rs(0),sum(0) {}
    };
    typedef node* pnode;
    pnode root;
    ImplicitST(ll liml,ll limr)
    {
        root=new node(liml,limr);
    }

    void update(pnode p,ll pos,ll v)
    {
        ll l=p->l;
        ll r=p->r;
        if(l==r && l==pos)
        {
            p->sum+=v;
            return ;
        }
        if(l>pos || r<pos)
            return ;

        ll mid=(l+r)>>1;
        if(!p->ls)
            p->ls=new node(l,mid);
        if(!p->rs)
            p->rs=new node(mid+1,r);
        update(p->ls,pos,v);
        update(p->rs,pos,v);
        p->sum=p->ls->sum+p->rs->sum;
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

    ///this is an implicit binary search
    ///which searches for tar-th in the st if it is used as a multiset
    ll query2(pnode p,int tar)
    {
        ll l=p->l;
        ll r=p->r;
        if(l==r)
            return l;

        ll mid=(l+r)>>1;
        if(!p->ls)
            p->ls=new node(l,mid);
        if(!p->rs)
            p->rs=new node(mid+1,r);
        if(p->ls->sum<tar)
        {
            tar-=p->ls->sum;
            return query2(p->rs,tar);
        }
        return query2(p->ls,tar);
    }
};