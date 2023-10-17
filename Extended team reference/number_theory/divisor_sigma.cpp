
typedef long long ll;

ll divisor_sigma(ll n)
{
	ll sigma = 0, d = 1;
	for (; d * d < n; ++d)
		if (n % d == 0)
			sigma += d + n / d;
	if (d * d == n)
		sigma += d;
	return sigma;
}

// sigma(n) for all n in [lo, hi)
vector<ll> divisor_sigma(ll lo, ll hi)
{
	vector<ll> ps = primes(sqrt(hi) + 1);
	vector<ll> res(hi - lo), sigma(hi - lo, 1);
	iota(res.begin(), res.end(), lo);
	for (ll p : ps)
		for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p)
		{
			ll b = 1;
			while (res[k - lo] > 1 && res[k - lo] % p == 0)
			{
				res[k - lo] /= p;
				b = 1 + b * p;
			}
			sigma[k - lo] *= b;
		}
	for (ll k = lo; k < hi; ++k)
		if (res[k - lo] > 1)
			sigma[k - lo] *= (1 + res[k - lo]);
	return sigma; // sigma[k-lo] = sigma(k)
}
