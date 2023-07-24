/*
	Solve ax+by=(a,b)
*/

struct info { ll x, y, g; };

info gcd(ll a, ll b)
{
	ll a0 = 1, a1 = 0, b0 = 0, b1 = 1, t;
	while (b != 0)
	{
		t = a0 - a / b * a1; a0 = a1; a1 = t;
		t = b0 - a / b * b1; b0 = b1; b1 = t;
		swap(a %= b, b);
	}
	if (a < 0)
	{
		a0 = -a0; b0 = -b0; a = -a;
	}
	return {a0, b0, a};
}
