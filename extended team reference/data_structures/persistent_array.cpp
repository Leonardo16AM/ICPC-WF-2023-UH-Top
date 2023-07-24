struct node{
    node *l, *r;
    int value;
};

node* clone(node *u){
    node *ans = new node();
    ans->l = u->l, ans->r = u->r, ans->value = u->value;
    return ans;
}

node* build(int b, int e){
    node *ans = new node();
    if (b + 1 < e){
        int m = (b + e) >> 1;
        ans->l = build(b, m);
        ans->r = build(m, e);
    }
    return ans;
}

node* update(node *root, int b, int e, int x, int v){
    root = clone(root);

    if (b + 1 == e){
        root->value = v;
    }
    else{
        int m = (b + e) >> 1;
        if (x < m) root->l = update(root->l, b, m, x, v);
        else root->r = update(root->r, m, e, x, v);
    }

    return root;
}

int query(node *root, int b, int e, int x){
    if (b + 1 == e) return root->value;

    int m = (b + e) >> 1;
    if (x < m) return query(root->l, b, m, x);
    else return query(root->r, m, e, x);
}
