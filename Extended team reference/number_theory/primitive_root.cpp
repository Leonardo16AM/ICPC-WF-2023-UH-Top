/*
	Find a primitive root of m

	Note: Only 2, 4, p^n, 2p^n have primitive roots
	Tested: http://codeforces.com/contest/488/problem/E
*/

// only prime and p>2
ll primitiveroot(ll p)
{
	auto v = prime_divisors(p - 1);
	for (ll g = 1;; g++)
	{
		bool ok = 1;
		for (auto d : v)
		{
			ll f = (p - 1) / d;
			if (pow(g, f, p) == 1)
			{
				ok = 0;
				break;
			}
		}
		if (ok)
			return g;
	}
}

ll primitive_root(ll m)
{
	if (m == 1)
		return 0;
	if (m == 2)
		return 1;
	if (m == 4)
		return 3;
	auto pr = primes(0, sqrt(m) + 1); // fix upper bound
	ll t = m;
	if (!(t & 1))
		t >>= 1;
	for (ll p : pr)
	{
		if (p > t)
			break;
		if (t % p)
			continue;
		do
			t /= p;
		while (t % p == 0);
		if (t > 1 || p == 2)
			return 0;
	}
	ll x = euler_phi(m), y = x, n = 0;
	vector<ll> f(32);
	for (ll p : pr)
	{
		if (p > y)
			break;
		if (y % p)
			continue;
		do
			y /= p;
		while (y % p == 0);
		f[n++] = p;
	}
	if (y > 1)
		f[n++] = y;
	for (ll i = 1; i < m; ++i)
	{
		if (__gcd(i, m) > 1)
			continue;
		bool flag = 1;
		for (ll j = 0; j < n; ++j)
		{
			if (pow(i, x / f[j], m) == 1)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
			return i;
	}
	return 0;
}
