
typedef long long ll;

ll mobius_mu(ll n)
{
	if (n == 0)
		return 0;
	ll mu = 1;
	for (ll x = 2; x * x <= n; ++x)
		if (n % x == 0)
		{
			mu = -mu;
			n /= x;
			if (n % x == 0)
				return 0;
		}
	return n > 1 ? -mu : mu;
}

// phi(n) for all n in [lo, hi)
vector<ll> mobius_mu(ll lo, ll hi)
{
	vector<ll> ps = primes(sqrt(hi) + 1);
	vector<ll> res(hi - lo), mu(hi - lo, 1);
	iota(res.begin(), res.end(), lo);
	for (ll p : ps)
		for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p)
		{
			mu[k - lo] = -mu[k - lo];
			if (res[k - lo] % p == 0)
			{
				res[k - lo] /= p;
				if (res[k - lo] % p == 0)
				{
					mu[k - lo] = 0;
					res[k - lo] = 1;
				}
			}
		}
	for (ll k = lo; k < hi; ++k)
		if (res[k - lo] > 1)
			mu[k - lo] = -mu[k - lo];
	return mu; // mu[k-lo] = mu(k)
}
