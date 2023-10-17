// return not trivial divisor of n
ll pollard_rho(ll n){
	if (!(n & 1)) return 2;
	while (1) {
		ll x = (ll) rand() % n, y = x;
		ll c = rand() % n;
		if (c == 0 || c == 2) c = 1;
		for (int i = 1, k = 2;; i++) {
			x = mul(x, x, n);
			if (x >= c) x -= c;
			else x += n - c;
			if (x == n) x = 0;
			if (x == 0) x = n - 1;
			else x--;
			ll d = __gcd(x > y ? x - y : y - x, n);
			if (d == n) break;
			if (d != 1) return d;
			if (i == k) { y = x, k <<= 1; }
		}
	}
	return 0;
}
