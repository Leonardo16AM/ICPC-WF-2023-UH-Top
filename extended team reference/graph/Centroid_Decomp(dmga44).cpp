#include <bits/stdc++.h>
#define db(x) cout << (x) << '\n';
#define all(v) (v).begin(), (v).end()
#define allr(v) (v).rbegin(), (v).rend()
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<double, ll> pdi;
typedef pair<string, ll> psi;
typedef pair<ll, string> pls;
typedef pair<string, string> pss;
typedef pair<ll, pii> pip;
typedef pair<pii, pii> ppp;
typedef complex<ld> point;
#define MAXN 500005

vector<int> g[MAXN], nodes;
bool mk1[MAXN], mk2[MAXN];
int sons[MAXN][2];

void dfs1(int u)
{
    mk1[u] = 1;
    sons[u][0] = 1;
    nodes.push_back(u);
    for (auto v : g[u])
        if (!mk1[v] && !mk2[v])
        {
            dfs1(v);
            sons[u][0] += sons[v][0];
            sons[u][1] = max(sons[v][0], sons[u][1]);
        }
}

void dfs2(int u)
{
    mk1[u] = 1;
    /// usually you start coding over here
    nodes.push_back(u);
    for (auto v : g[u])
        if (!mk1[v] && !mk2[v])
            dfs2(v);
}

void solve(int u)
{
    dfs1(u);

    int cent = -1, cant = nodes.size() / 2;
    for (auto v : nodes)
    {
        if (cent == -1 && sons[v][0] >= cant && sons[v][1] <= cant)
            cent = v;
        mk1[v] = sons[v][0] = sons[v][1] = 0;
    }
    nodes.clear();

    /// usually you start coding over here
    mk2[cent] = 1;
    for (auto v : g[cent])
    {
        if (mk2[v])
            continue;
        /// usually you start coding over here
        dfs2(v);

        for (auto y : nodes)
            mk1[y] = 0;
        nodes.clear();
    }

    for (auto v : g[cent])
        if (!mk2[v])
            solve(v);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    solve(0);

    return 0;
}
