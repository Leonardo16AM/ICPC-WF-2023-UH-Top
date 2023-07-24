struct Trie
{
    struct node
    {
        int val;
        node *edge[26];
        node() : val(0) { memset(edge, 0, sizeof(edge)); }
    };
    typedef node* pnode;

    pnode root;

    Trie()
    { 
        root = new node(); 
    }
    pnode insert(string& s)
    {
        int len=s.size();
        pnode t = root;
        for (int i = 0; i < len; i++)
        {
            char c = s[i] - 'a';
            if (!t->edge[c])
                t->edge[c] = new node();
            t = t->edge[c];
        }
        return t;
    }
    void insert(string& s,int v)
    {
        insert(s)->val=v;
    }

    pnode find(string& s)
    {
        int len=s.size();
        pnode t = root;
        if (!t)
            return 0;
        for (int i = 0; i < len; i++)
        {
            char c = s[i] - 'a';
            if (!t->edge[c])
                return 0;
            t = t->edge[c];
        }
        return t;
    }

    int eval(string& s)
    {
        pnode t = find(s);
        if(t)
            return t->val;
        return -1;
    }
};