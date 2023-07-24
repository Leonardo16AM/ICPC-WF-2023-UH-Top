
struct hashing
{
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    ll mod1 = 2e9 + 99, mod2 = 1e9 + 7;
    ll b1 = 331, b2 = 997;

    hashing(string s)
    {
        int n = s.size();
        h1.resize(n + 1);
        h2.resize(n + 1);
        p1.resize(n + 1);
        p2.resize(n + 1);
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; i++)
        {
            p1[i + 1] = (p1[i] * b1) % mod1;
            p2[i + 1] = (p2[i] * b2) % mod2;
            h1[i + 1] = (h1[i] * b1 + s[i]) % mod1;
            h2[i + 1] = (h2[i] * b2 + s[i]) % mod2;
        }
    }

    pii hs(int i, int j)
    {
        ll vi1 = (h1[i] * p1[j - i + 1]) % mod1;
        ll vi2 = (h2[i] * p2[j - i + 1]) % mod2;
        ll vj1 = h1[j + 1];
        ll vj2 = h2[j + 1];
        return pii((vj1 - vi1 + mod1) % mod1, (vj2 - vi2 + mod2) % mod2);
    }
};