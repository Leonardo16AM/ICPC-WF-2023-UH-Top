/*
	Solve a^x=b (mod M)
	Tested: LIGHTOJ 1325
*/

ll dlog(ll a, ll b, ll M)
{
	map<ll, ll> _hash;
	ll n = euler_phi(M), k = sqrt(n);
	for(ll i = 0, t = 1; i < k; ++i)
	{
		_hash[t] = i;
		t = mul(t, a, M);
	}
	ll c = pow(a, n - k, M);
	for(ll i = 0; i * k < n; i++)
	{
		if(_hash.find(b) != _hash.end())
			return i * k + _hash[b];
		b = mul(b, c, M);
	}
	return -1;
}
