/*
    Tested:
        https://codeforces.com/gym/102433/problems/K
*/

#define MAXP (ll)(2e7+5)
///up to change
typedef int T;

struct node{
    int l,r;
    T v;
    T lazy;
};

node pool[MAXP];
int actual;

int next()
{
    actual++;
    return actual;
}

//template<typename T>
struct pst{
    vector<int> versions;
    int n;
    T neutroL;
    pst(T neutroL) : n(0),neutroL(neutroL) {}
    pst(int n,T neutroL) : n(n),neutroL(neutroL) {}
    pst(vector<T> &a,T neutroL) : n(a.size()),neutroL(neutroL) { versions.push_back(build(0,n-1,a)); }

    T merge(T v1,T v2)
    {
        ///up to code
    }

    T combine(T l1,T l2)
    {
        ///up to code
    }

    void up(int p,int l,int r,T v)
    {
        ///up to code
        pool[p].lazy=combine(pool[p].lazy,v);
    }

    int build(int l,int r,vector<T> &a)
    {
        int ans=next();
        if(l==r)
        {
            pool[ans].v=a[l];
            pool[ans].lazy=neutroL;
            return ans;
        }
        int mid=(l+r)>>1;
        pool[ans].l=build(l,mid,a);
        pool[ans].r=build(mid+1,r,a);
        pool[ans].v=merge(pool[pool[ans].l].v,pool[pool[ans].r].v);
        pool[ans].lazy=neutroL;
        return ans;
    }

    int build(int l,int r,T *a)
    {
        int ans=next();
        if(l==r)
        {
            pool[ans].v=a[l];
            pool[ans].lazy=neutroL;
            return ans;
        }
        int mid=(l+r)>>1;
        pool[ans].l=build(l,mid,a);
        pool[ans].r=build(mid+1,r,a);
        pool[ans].v=merge(pool[pool[ans].l].v,pool[pool[ans].r].v);
        pool[ans].lazy=neutroL;
        return ans;
    }

    int clone(int p)
    {
        int ans=next();
        pool[ans].l=pool[p].l;
        pool[ans].r=pool[p].r;
        pool[ans].v=pool[p].v;
        pool[ans].lazy=pool[p].lazy;
        return ans;
    }

    void update(int ver,int l,int r,T v) { versions.push_back(update(versions[ver],0,n-1,l,r,v)); }
    void update(int l,int r,T v) { versions.push_back(update(versions.back(),0,n-1,l,r,v)); }

    int update(int p,int l,int r,int L,int R,T v)
    {
        p=clone(p);

        if(L<=l && r<=R)
        {
            up(p,l,r,v);
            return p;
        }
        ///the push function is merged to avoid MLE
        int mid=(l+r)>>1;
        if(pool[p].lazy!=neutroL)
        {
            pool[p].l=clone(pool[p].l);
            up(pool[p].l,l,mid,pool[p].lazy);
        }
        if(L<=mid)
        {
            actual-=(pool[p].lazy!=neutroL);
            pool[p].l=update(pool[p].l,l,mid,L,R,v);
        }

        if(pool[p].lazy!=neutroL)
        {
            pool[p].r=clone(pool[p].r);
            up(pool[p].r,mid+1,r,pool[p].lazy);
        }
        if(R>mid)
        {
            actual-=(pool[p].lazy!=neutroL);
            pool[p].r=update(pool[p].r,mid+1,r,L,R,v);
        }

        pool[p].v=merge(pool[pool[p].l].v,pool[pool[p].r].v);
        pool[p].lazy=neutroL;
        return p;
    }

    T query(int t,int l,int r) { return query(versions[t],0,n-1,l,r,neutroL); }
    T query(int l,int r) { return query(versions.back(),0,n-1,l,r,neutroL); }

    T query(int p,int l,int r,int L,int R,T lazy_up)
    {
        if(L<=l && r<=R)
        {
            int x=clone(p);
            up(x,l,r,lazy_up);
            T ans=pool[x].v;
            actual--;
            return ans;
        }
        int mid=(l+r)>>1;
        lazy_up=combine(lazy_up,pool[p].lazy);
        if(R<=mid)
            return query(pool[p].l,l,mid,L,R,lazy_up);
        if(L>mid)
            return query(pool[p].r,mid+1,r,L,R,lazy_up);
        return merge(query(pool[p].l,l,mid,L,R,lazy_up),query(pool[p].r,mid+1,r,L,R,lazy_up));
    }
};
