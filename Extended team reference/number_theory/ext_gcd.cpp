/*
	Solve ax+by=(a,b)

	Tested: Benelux 2014 I, AIZU NTL_1_E
*/

ll gcd(ll a, ll b, ll &x, ll &y)
{
	if(b == 0)
		return x = 1, y = 0, a;
	ll r = gcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
