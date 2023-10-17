/**
    Complejidad en memoria O(Q*log(Q))
    Complejidad temporal O(Q*log^3(Q)) amortizado
    Buena constante
    tested: https://codeforces.com/gym/101964/submission/119939799
**/

/// ops fall in [0,n-1] range
struct st2d
{
    vector<vector<int>> abi;
    int sz;

    st2d()
    {
        vector<int> v = {};
        build(v);
    }

    st2d(vector<int> &v)
    {
        build(v);
    }

    st2d(vector<pii> &v)
    {
        vector<int> v2(v.size());
        for (int i = 0; i < v.size(); i++)
            v2[i] = v[i].s;
        build(v2);
    }

    void build(vector<int> &v)
    {
        sz = v.size() + 1;
        abi = vector<vector<int>>(sz, vector<int>(0));
        for (int i = 0; i < sz - 1; i++)
            update(i + 1, v[i]);
        for (int i = 1; i < sz; i++)
            sort(all(abi[i]));
    }

    void update(int p, int v)
    {
        while (p < sz)
        {
            abi[p].push_back(v);
            p += (p & -p);
        }
    }

    int query(int p, int v)
    {
        int ans = 0;
        while (p)
        {
            ans += upper_bound(all(abi[p]), v) - abi[p].begin();
            p -= (p & -p);
        }
        return ans;
    }

    /// x1<=x2 must hold
    int query(int l, int r, int x1, int x2)
    {
        return query(r + 1, x2) - query(r + 1, x1 - 1) - query(l, x2) + query(l, x1 - 1);
    }
};

struct bunch_st2d
{
    vector<st2d> sts;
    vector<vector<pii>> ps;
    int n;

    bunch_st2d() : n(0), sts(30), ps(30) {}

    int query(int x1, int x2, int y1, int y2)
    {
        int ans = 0;
        for (int i = 0; i < 30; i++)
            if (n & (1 << i))
            {
                int l = lower_bound(all(ps[i]), pii(x1, -2e9 - 5)) - ps[i].begin();
                int r = lower_bound(all(ps[i]), pii(x2 + 1, -2e9 - 5)) - ps[i].begin();
                r--;
                if (r < l)
                    continue;

                ans += sts[i].query(l, r, y1, y2);
            }
        return ans;
    }

    vector<pii> merge(vector<pii> &v1, vector<pii> &v2)
    {
        vector<pii> ans;
        int p1 = 0, p2 = 0;
        while (p1 < v1.size() && p2 < v2.size())
        {
            if (v1[p1] < v2[p2])
            {
                ans.push_back(v1[p1]);
                p1++;
            }
            else
            {
                ans.push_back(v2[p2]);
                p2++;
            }
        }
        while (p1 < v1.size())
        {
            ans.push_back(v1[p1]);
            p1++;
        }
        while (p2 < v2.size())
        {
            ans.push_back(v2[p2]);
            p2++;
        }

        return ans;
    }

    void insert(pii p)
    {
        vector<pii> act = {p};
        for (int i = 0; i < 30; i++)
        {
            if (n & (1 << i))
            {
                act = merge(act, ps[i]);
                sts[i] = st2d();
                ps[i].clear();
            }
            else
            {
                ps[i] = act;
                sts[i] = st2d(act);
                break;
            }
        }
        n++;
    }
};
