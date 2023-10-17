struct DSU_WITH_ROLLBACKS
{
    struct dsu_save
    {
        int u, urank, v, vrank, comps;
        bool bipart;
    };

    stack<dsu_save> op;

    vector<int> rnk;
    vector<bool> col;
    bool bipartite;
    int comps;

    DSU_WITH_ROLLBACKS()
    {

    }

    DSU_WITH_ROLLBACKS(int N)
    {
        init(N);
    }

    void init(int N)
    {
        rnk.clear();
        col.clear();
        while(!op.empty())op.pop();
        rnk.resize(N);
        col.resize(N);
        for(int i = 0 ; i < N ; i++)
        {
            rnk[i] = 1;
            col[i] = false;
        }
        bipartite = true;
        comps = N;
    }

    pair<int,bool> find(int x)
    {
        if(rnk[x] > 0)return {x, col[x]};
        pair<int,bool> tp = find(-rnk[x]);
        tp.second ^= col[x];
        return tp;
    }

    void join(int a, int b)
    {
        pair<int,bool> ta = find(a), tb = find(b);
        a = ta.first;
        b = tb.first;
        op.push({a, rnk[a], b, rnk[b], comps, bipartite});
        if(a == b)
        {
            if(ta.second == tb.second)bipartite = false;
            return;
        }
        comps--;
        if(rnk[a] < rnk[b])swap(a,b);
        rnk[a] += rnk[b];
        rnk[b] = -a;
        col[b] = col[b]^(ta.second == tb.second);
    }

    void rollback()
    {
        if(op.empty())return;
        dsu_save x = op.top();
        op.pop();
        comps = x.comps;
        bipartite = x.bipart;
        rnk[x.u] = x.urank;
        col[x.u] = false;
        rnk[x.v] = x.vrank;
        col[x.v] = false;
    }
};

template<typename F, typename Q, typename T, typename D>
struct ROLLBACK_TRICK
{
    typedef long long ll;

    vector<vector<T>> ST;
    vector<vector<Q>> arr;
    int N;

    void update(T &x, D &DS)
    {
        DS.join(x.first, x.second);
    }

    F query(Q &x, D &DS)
    {
        return DS.rnk[DS.find(x).first];
    }

    void rollback(D &DS)
    {
        DS.rollback();
    }

    void add_to_tree(int nodo, int l, int r, int a, int b, T &qu)
    {
        if(r < a || l > b)return;
        if(a <= l && r <= b)
        {
            ST[nodo].push_back(qu);
            return;
        }
        int mid = (l+r)/2;
        add_to_tree(nodo*2, l, mid, a, b, qu);
        add_to_tree(nodo*2+1, mid+1, r, a, b, qu);
    }

    void add_query(T &qu, int l, int r)
    {
        add_to_tree(1, 0, N-1, l, r, qu);
    }

    void dfs(int nodo, int l, int r, vector<F> &ans, D &DS)
    {
        for(auto x : ST[nodo])update(x, DS);
        if(l == r)
        {
            for(auto x : arr[l])ans.push_back(query(x, DS));
        }
        else
        {
            int mid = (l+r)/2;
            dfs(nodo*2, l, mid, ans, DS);
            dfs(nodo*2+1, mid+1, r, ans, DS);
        }
        for(int i = 0 ; i < ST[nodo].size() ; i++)rollback(DS);
    }

    vector<F> solve(vector<Q> &qu, vector<ll> &querys, vector<T> &vect, vector<pair<ll,ll>> &ranges, D &DS)
    {
        assert(qu.size() == querys.size());
        assert(vect.size() == ranges.size());

        vector<pair<ll,ll>> mp;

        for(int i = 0 ; i < querys.size() ; i++)
        {
            mp.push_back({querys[i], i});
        }

        for(int i = 0 ; i < ranges.size() ; i++)
        {
            mp.push_back({ranges[i].first, i+querys.size()});
            mp.push_back({ranges[i].second, i+querys.size()+ranges.size()});
        }

        sort(mp.begin(), mp.end());

        ll temp = 0;
        int cont = 0;

        if(mp.size())temp = mp[0].first;

        for(int i = 0 ; i < mp.size() ; i++)
        {
            if(mp[i].first != temp)cont++;

            if(mp[i].second < querys.size())querys[mp[i].second] = cont;
            else if(mp[i].second >= querys.size() + ranges.size())ranges[mp[i].second-querys.size()-ranges.size()].second = cont;
            else ranges[mp[i].second-querys.size()].first = cont;

            temp = mp[i].first;
        }

        N = cont+1;

        ST.clear();
        ST.resize(4*(N+4));

        for(int i = 0 ; i < vect.size() ; i++)
        {
            add_query(vect[i], ranges[i].first, ranges[i].second);
        }

        arr.clear();
        arr.resize(N);

        for(int i = 0 ; i < querys.size() ; i++)
        {
            arr[querys[i]].push_back(qu[i]);
        }

        vector<F> ans;

        dfs(1, 0, N-1, ans, DS);

        return ans;
    }
};