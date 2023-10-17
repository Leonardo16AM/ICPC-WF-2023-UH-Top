/*
	Return a (mod p) where n!=a*p^k
	Complexity: O(p log n)
*/

ll mod_fact(ll n, ll p)
{
	ll res = 1;
	while (n > 0)
	{
		for (ll i = 1, m = n % p; i <= m; ++i)
			res = res * i % p;
		if ((n /= p) % 2 > 0)
			res = p - res;
	}
	return res;
}
