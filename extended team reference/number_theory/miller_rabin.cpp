/*
	Tested: SPOJ PON, FACT0
	Note: be carful with overflow
*/

bool witness(ll a, ll s, ll d, ll n)
{
	ll x = pow(a, d, n);
	if (x == 1 || x == n - 1)
		return 0;
	for (int i = 0; i < s - 1; i++)
	{
		x = mul(x, x, n);
		if (x == 1)
			return 1;
		if (x == n - 1)
			return 0;
	}
	return 1;
}

bool miller_rabin(ll n)
{
	if (n < 2)
		return 0;
	if (n == 2)
		return 1;
	if (n % 2 == 0)
		return 0;
	ll d = n - 1, s = 0;
	while (d % 2 == 0)
		++s, d /= 2;
	vector<ll> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (ll p : test)
		if (p >= n) break;
		else if (witness(p, s, d, n))
			return 0;
	return 1;
}
