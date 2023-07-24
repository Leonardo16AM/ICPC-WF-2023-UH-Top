/*
	Returns C(n, m) (mod p)
	
	Note: p can be any number 

	Tested: XV OpenCup GP of Tatarstan,
	http://codeforces.com/gym/100633/problem/J
*/

ll c1(ll n, ll p, ll pk)
{
	if (n == 0)
		return 1;
	ll i, k, ans = 1;
	for (i = 2; i <= pk; i++)
		if (i % p)
			ans = ans * i % pk;
	ans = pow(ans, n / pk, pk);
	for (k = n % pk, i = 2; i <= k; i++)
		if (i % p)
			ans = ans * i % pk;
	return ans * c1(n / p, p, pk) % pk;
}

ll cal(ll n, ll m, ll p, ll pi, ll pk)
{
	ll i, k = 0, a, b, c, ans;
	a = c1(n, pi, pk), b = c1(m, pi, pk), c = c1(n - m, pi, pk);
	for (i = n; i; i /= pi)
		k += i / pi;
	for (i = m; i; i /= pi)
		k -= i / pi;
	for (i = n - m; i; i /= pi)
		k -= i / pi;
	ans = a * inv(b, pk) % pk * inv(c, pk) % pk * pow(p, k, pk) % pk;
	return ans * (p / pk) % p * inv(p / pk, pk) % p;
}

ll comb(ll n, ll m, ll p)
{
	ll ans = 0, x, i, k;
	for (x = p, i = 2; x > 1; i++)
		if (x % i == 0)
		{
			for (k = 1; x % i == 0; x /= i)
				k *= i;
			ans = (ans + cal(n, m, p, i, k)) % p;
		}
	return ans;
}
