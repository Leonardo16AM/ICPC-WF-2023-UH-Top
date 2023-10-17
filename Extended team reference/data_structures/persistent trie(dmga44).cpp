//tested: https://codeforces.com/group/4zVk9dZl6Q/contest/391621/submission/166743883
struct PersistentTrie
{
    struct node
    {
        int val;
        node *edge[26];
        node() : val(0) { memset(edge, 0, sizeof(edge)); }
    };
    typedef node* pnode;

    vector<pnode> root;
    int versionCount;

    PersistentTrie()
    { 
        root.push_back(new node());
        versionCount=1; //Empty version
    }

    pnode clone(pnode p)
    {
        if(!p)
            return 0;
        pnode ans=new node();
        ans->val=p->val;
        for(int i=0;i<26;i++)
            ans->edge[i]=p->edge[i];
        return ans;
    }

    pnode insert(string& s,int ver)
    {
        int len=s.size();
        pnode t = clone(root[ver]);
        root.push_back(t);
        versionCount++;
        for (int i = 0; i < len; i++)
        {
            char c = s[i] - 'a';
            if (!t->edge[c])
            {
                t->edge[c] = new node();
                t=t->edge[c];
                continue;
            }
            pnode previous=t;
            t = clone(t->edge[c]);
            previous->edge[c]=t;
        }
        return t;
    }
    void insert(string& s,int v,int ver)
    {
        insert(s,ver)->val=v;
    }

    pnode find(string& s,int ver)
    {
        int len=s.size();
        pnode t = root[ver];
        for (int i = 0; i < len; i++)
        {
            char c = s[i] - 'a';
            if (!t->edge[c])
                return 0;
            t = t->edge[c];
        }
        return t;
    }

    int eval(string& s,int ver)
    {
        pnode t = find(s,ver);
        if(t)
            return t->val;
        return -1;
    }
};