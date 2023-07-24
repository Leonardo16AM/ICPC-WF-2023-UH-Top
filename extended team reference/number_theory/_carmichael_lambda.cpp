/*
	Carmichael Lambda (Universal Totient Function)

	Description:
	lambda(n) is a smallest number that satisfies
	a^lambda(n) = 1 (mod n) for all a coprime with n.
	This is also known as an universal totien function psi(n).
*/

typedef long long ll;

ll gcd(ll a, ll b)
{
	while (a) swap(a, b %= a);
	return b;
}

ll lcm(ll a, ll b)
{
	return a * (b / gcd(a, b));
}

ll carmichael_lambda(ll n)
{
	ll lambda = 1;
	if (n % 8 == 0)
		n /= 2;
	for (ll d = 2; d * d <= n; ++d)
		if (n % d == 0)
		{
			n /= d;
			ll y = d - 1;
			while (n % d == 0)
			{
				n /= d;
				y *= d;
			}
			lambda = lcm(lambda, y);
		}
	if (n > 1)
		lambda = lcm(lambda, n - 1);
	return lambda;
}

// lambda(n) for all n in [lo, hi)
vector<ll> carmichael_lambda(ll lo, ll hi)
{
	vector<ll> ps = primes(sqrt(hi) + 1);
	vector<ll> res(hi - lo), lambda(hi - lo, 1);
	iota(res.begin(), res.end(), lo);
	for (ll k = ((lo + 7) / 8) * 8; k < hi; k += 8)
		res[k - lo] /= 2;
	for (ll p : ps)
		for (ll k = ((lo + (p - 1)) / p) * p; k < hi; k += p)
		{
			if (res[k - lo] < p)
				continue;
			ll t = p - 1;
			res[k - lo] /= p;
			while (res[k - lo] > 1 && res[k - lo] % p == 0)
			{
				t *= p;
				res[k - lo] /= p;
			}
			lambda[k - lo] = lcm(lambda[k - lo], t);
		}
	for (ll k = lo; k < hi; ++k)
		if (res[k - lo] > 1)
			lambda[k - lo] = lcm(lambda[k - lo], res[k - lo] - 1);
	return lambda; // lambda[k-lo] = lambda(k)
}
