#include <bits/stdc++.h>
#define db(x) cout << (x) << '\n';
#define all(v) (v).begin(),(v).end()
#define allr(v) (v).rbegin(),(v).rend()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef pair<double,ll> pdi;
typedef pair<string,ll> psi;
typedef pair<ll,string> pls;
typedef pair<ll,pii> pip;
typedef pair<pii,pii> ppp;

struct matrix{
    vector< vector<ll> > m;
    ll mod,sz;
    ll mod2;

    matrix (ll n,ll modc) : sz(n),m(n),mod(modc) {
        for(int i=0;i<n;i++)
            m[i].resize(n);
        mod2=mod*mod;
    }

    matrix operator*(matrix b)
    {
        matrix ans(sz,mod);
        for(int i=0;i<sz;i++)
            for(int j=0;j<sz;j++)
                for(int u=0;u<sz;u++)
                {
                    ans.m[i][u]+=m[i][j]*b.m[j][u];
                    if(ans.m[i][u]>=mod2)
                        ans.m[i][u]-=mod2;
                }
        for(int i=0;i<sz;i++)
            for(int j=0;j<sz;j++)
                ans.m[i][j]%=mod;
        return ans;
    }

    matrix qp(ll e)
    {
        if(e==1)
            return *this;
        matrix x=qp(e/2);
        x=(x*x);
        if(e&1)
            x=(x*(*this));
        return x;
    }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    matrix fib(2,1e9+7);
    fib.m[0][0]=1;
    fib.m[0][1]=1;
    fib.m[1][0]=1;

    for(int i=1;i<=10;i++)
        cout << fib.qp(i).m[0][0] << '\n';

    return 0;
}
