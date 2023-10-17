/**
 * @file combine different NTT and FWHT(dmga44).cpp
 * @author your name (you@domain.com)
 * @brief Tested: https://codeforces.com/gym/102441/submission/175268662
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")
#pragma GCC option("arch=native", "no-zero-upper") // Enable AVX

/// UH Top
#include <bits/stdc++.h>
#define db(x) cerr << #x << ':' << (x) << '\n';
#define all(v) (v).begin(), (v).end()
#define allr(v) (v).rbegin(), (v).rend()
// #define int ll
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
// typedef __int128_t int128;
typedef pair<ll, ll> pii;
typedef pair<ld, ll> pdi;
typedef pair<ld, ld> pdd;
typedef pair<ld, pdd> pdp;
typedef pair<string, ll> psi;
typedef pair<ll, string> pls;
typedef pair<string, string> pss;
typedef pair<ll, pii> pip;
typedef pair<pii, pii> ppp;
typedef complex<ld> point;
typedef vector<point> polygon;
typedef vector<ll> vi;
typedef pair<point, int> ppi;
#define prec(n)        \
    cout.precision(n); \
    cout << fixed
const ll mod = (998244353);
const ld eps = (1e-9);
const ll oo = (ll)(1e18 + 5);
#define pi acos(-1)
#define MAXN (ll)(1e6 + 5)

ll inv(ll b, ll M)
{
    ll u = 1, x = 0, s = b, t = M;
    while (s)
    {
        ll q = t / s;
        swap(x -= u * q, u);
        swap(t -= s * q, s);
    }
    return (x %= M) >= 0 ? x : x + M;
}

ll pow(ll a, ll b, ll M)
{
    ll x = 1;
    for (; b > 0; b >>= 1)
    {
        if (b & 1)
            x = (a * x) % M;
        a = (a * a) % M;
    }
    return x;
}

void fmt(vector<vector<ll>> &x, ll mod, int type, int sign = +1)
{
    if (type == 0) // FWHT
    {
        int n = x.size();
        for (int p = 0; p < x[0].size(); p++)
        {
            for (int i = 0, j = 1; j < n - 1; j++)
            {
                for (int k = n >> 1; k > (i ^= k); k >>= 1);
                if (j < i)
                    swap(x[i][p], x[j][p]);
            }
            for (int m = 1; m < n; m *= 2)
            {
                for (int i = 0; i < m; i++)
                {
                    for (int j = i; j < n; j += 2 * m)
                    {
                        ll u = x[j][p], d = x[j + m][p];
                        if ((x[j][p] = u + d) >= mod)
                            x[j][p] -= mod;
                        if ((x[j + m][p] = u - d) < 0)
                            x[j + m][p] += mod;
                    }
                }
            }
            if (sign < 0)
            {
                ll n_inv = inv(n, mod);
                for (int i = 0; i < n; i++)
                    x[i][p] = (x[i][p] * n_inv) % mod;
            }
        }
    }
    else // NTT
    {
        int n = x[0].size();
        ll h = pow(3, (mod - 1) / n, mod); // primitive root for 998244353
        if (sign < 0)
            h = inv(h, mod);
        for (int p = 0; p < x.size(); p++)
        {
            for (int i = 0, j = 1; j < n - 1; j++)
            {
                for (int k = n >> 1; k > (i ^= k); k >>= 1);
                if (j < i)
                    swap(x[p][i], x[p][j]);
            }
            for (int m = 1; m < n; m *= 2)
            {
                ll w = 1, wk = pow(h, n / (2 * m), mod);
                for (int i = 0; i < m; i++)
                {
                    for (int j = i; j < n; j += 2 * m)
                    {
                        ll u = x[p][j], d = x[p][j + m] * w % mod;
                        if ((x[p][j] = u + d) >= mod)
                            x[p][j] -= mod;
                        if ((x[p][j + m] = u - d) < 0)
                            x[p][j + m] += mod;
                    }
                    w = w * wk % mod;
                }
            }
            if (sign < 0)
            {
                ll n_inv = inv(n, mod);
                for (int i = 0; i < n; i++)
                    x[p][i] = (x[p][i] * n_inv) % mod;
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<ll>> a(512, vector<ll>(2048));
    vector<int> as(n), bs(n);
    for (int i = 0; i < n; i++)
        cin >> as[i];
    for (int i = 0; i < n; i++)
        cin >> bs[i];
    for (int i = 0; i < n; i++)
        a[bs[i]][as[i]]++;

    // a = conv(a, a, mod);
    // a = conv(a, a, mod);
    fmt(a, mod, 0, 1);
    fmt(a, mod, 1, 1);
    for (int i = 0; i < 512; i++)
        for (int j = 0; j < 2048; j++)
            a[i][j] = pow(a[i][j], 4, mod);
    fmt(a, mod, 1, -1);
    fmt(a, mod, 0, -1);
    ll ans = 0;
    for (int i = 0; i < 512; i++)
        for (int j = 0; j < 2048; j++)
            ans = (ans + a[i][j] * pow(j, i, mod)) % mod;
    cout << ans << '\n';

    return 0;
}