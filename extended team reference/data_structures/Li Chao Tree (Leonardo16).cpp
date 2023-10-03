struct line {
    int m=-1e12, b=0;
    int operator()(int x) { return m * x + b; }
};

struct node{
    line l;
    node *lft=NULL,*rgt=NULL;
    node(){}
};


struct li_chao{
    node *root=new node();

    void insert(node *wr,int l,int r,line seg){
        if(l==r){
            if( seg(l) > wr->l(l) )wr->l=seg;
            return;
        }
        int mid=(l+r)>>1;
        if( wr->l.m > seg.m)swap(wr->l,seg);
        if(wr->l(mid) < seg(mid) ){
            swap(wr->l,seg);
            if(wr->lft==NULL)wr->lft=new node();
            insert(wr->lft,l,mid,seg);
        }else{
            if(wr->rgt==NULL)wr->rgt=new node();
            insert(wr->rgt,mid+1,r,seg);
        }
    }

    int query(node *wr,int l,int r,int x){
        if(l==r) return wr->l(x);
        int mid=(l+r)>>1;
        if(x<mid && wr->lft!=NULL){
            return max( wr->l(x) , query(wr->lft,l,mid,x) );
        }
        if(x>=mid && wr->rgt!=NULL){
            return max( wr->l(x) , query(wr->rgt,mid+1,r,x) );
        }
        return wr->l(x);
    }

    void insert(int m,int b){
        line l;l.m=m;l.b=b;
        insert(root,-1e6,1e6,l);
    }

    int query(int x){return  query(root,-1e6,1e6,x);}
};