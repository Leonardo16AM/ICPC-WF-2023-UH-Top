/*
	Tested: UVA 10408
*/

vector<pair<ll, ll>> farey_sequence(int n)
{
	ll a = 0, b = 1, c = 1, d = n;
	vector<pair<ll, ll>> s;
	s.push_back({ 0, 1 });
	while (c < n)
	{
		ll k = (n + b) / d;
		ll e = k * c - a;
		ll f = k * d - b;
		a = c; b = d;
		c = e, d = f;
		s.push_back({ a, b });
	}
	return s;
}
