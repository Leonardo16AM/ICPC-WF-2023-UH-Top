/*
    Solves x^2=a (mod p).
    Complexity: O(log(p))
    Tested: https://codeforces.com/gym/102354/submission/74617802
*/
ll norm_mod(ll a, ll p)
{
    a %= p;
    if (a < 0)
        a += p;
    return a;
}
// p: odd (not necessarily prime)
// 10^18
ll jacobi(ll a, ll p)
{
    a = ((a % p) + p) % p;
    auto neg = [](ll x)
    { return x % 2 ? -1 : 1; };
    if (a == 0)
        return p == 1;
    else if (a % 2)
        return neg(((p - 1) & (a - 1)) >> 1) * jacobi(p % a, a);
    else
        return neg(((p & 15) * (p & 15) - 1) / 8) * jacobi(a / 2, p);
}

// p: prime
// 0<=a<p
// returns minimum solution
ll rnd(ll l, ll r) //[l,r)
{
    using D = uniform_int_distribution<ll>;
    mt19937 gen(time(0));
    return D(l, r - 1)(gen);
}

ll rnd(ll n) //[0,n)
{
    return rnd(ll(0), n);
}
ll sqrt_mod(ll a, ll p)
{
    if (p == 2)
        return a % 2;
    if (a == 0)
        return 0;
    if (jacobi(a, p) == -1)
        return -1;
    ll b, c;
    do
    {
        b = rnd(p);
        c = norm_mod(b * b - a, p);
    } while (jacobi(c, p) != -1);
    auto mul = [&](pair<ll, ll> x, pair<ll, ll> y)
    {
        return pair<ll, ll>(norm_mod(x.first * y.first + x.second * y.second % p * c, p), norm_mod(x.first * y.second + x.second * y.first, p));
    };
    pair<ll, ll> x(b, 1), cur(1, 0);
    ll n = (p + 1) / 2;
    while (n)
    {
        if (n & 1)
            cur = mul(cur, x);
        x = mul(x, x);
        n >>= 1;
    }
    return min(cur.first, p - cur.first);
}