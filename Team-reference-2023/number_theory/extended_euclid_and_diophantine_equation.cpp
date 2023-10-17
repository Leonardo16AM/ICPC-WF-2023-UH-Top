// returns (d, x, y) such that d = gcd(a, b) = ax + by
ll extended_euclid(ll a, ll b, ll &x, ll &y){
	if (b == 0) { x = 1, y = 0; return a; }
	ll r = extended_euclid(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
// returns (x, y) such that c = ax + by
pair<ll, ll> diophantine_equation(ll a, ll b, ll c){
	ll g, x, y; g = extended_euclid(a, b, x, y);
	ll k = 0; // k e Z
	return { x * c / g + (k * b / g), y * c / g - (k * a / g) };
}
