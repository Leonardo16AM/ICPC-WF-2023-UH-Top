/*
	Tested: SPOJ PRIME1, ETFS
	Complexity: O(n log log n)
*/

typedef long long ll;

// primes in [lo, hi)
vector<ll> primes(ll lo, ll hi)
{
	const ll M = 1 << 14, SQR = 1 << 16;
	vector<bool> composite(M), small_composite(SQR);
	vector<pair<ll, ll>> sieve;
	for (ll i = 3; i < SQR; i += 2)
		if (!small_composite[i])
		{
			ll k = i * i + 2 * i * max(0.0, ceil((lo - i*i)/(2.0*i)));
			sieve.push_back({ 2 * i, k });
			for (ll j = i * i; j < SQR; j += 2 * i)
				small_composite[j] = 1;
		}
	vector<ll> ps;
	if (lo <= 2)
	{
		ps.push_back(2);
		lo = 3;
	}
	for (ll k = lo | 1, low = lo; low < hi; low += M)
	{
		ll high = min(low + M, hi);
		fill(composite.begin(), composite.end(), 0);
		for (auto &z : sieve)
			for (; z.second < high; z.second += z.first)
				composite[z.second - low] = 1;
		for (; k < high; k += 2)
			if (!composite[k - low])
				ps.push_back(k);
	}
	return ps;
}

vector<ll> primes(ll hi)
{
	return primes(0, hi);
}
