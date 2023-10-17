typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;
// inverse of 1, 2, ..., n mod P in O(n) (P must be prime)
vector<ll> inverses(int n, int P){
	vector<ll> inv(n + 1, 1);
	for (int i = 2; i <= n; ++i) 
		inv[i] = inv[P % i] * (P - P / i) % P;
	return inv;
}
template <typename T, typename U>
T pow_mod(T a, U b, int mod){
	T r = 1;
	for (; b > 0; b >>= 1){
		if (b & 1) r = (ll)r * a % mod;
		a = (ll)a * a % mod;
	}
	return r;
}
ll inv(ll b, ll M){
	ll u = 1, x = 0, s = b, t = M;
	while (s){
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	return (x %= M) >= 0 ? x : (x + M);
}
// solve a x == b (mod M) (sol iff (a, m) | b same as (a, m) | (b, m))
ll div(ll a, ll b, ll M){
	ll u = 1, x = 0, s = a, t = M;
	while (s){
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	if (b % t) return -1; // infeasible
	return (x < 0 ? (x + M) : x) * (b / t) % M;
}
// assume: M is prime (singular ==>
mat inv(mat A, ll M){
	int n = A.size();
	mat B(n, vec(n));
	for (int i = 0; i < n; ++i) B[i][i] = 1;
	for (int i = 0; i < n; ++i){
		int j = i;
		while (j < n && A[j][i] == 0) ++j;
		if (j == n) return {};
		swap(A[i], A[j]);
		swap(B[i], B[j]);
		ll inv = div(1, A[i][i], M);
		for (int k = i; k < n; ++k) A[i][k] = A[i][k] * inv % M;
		for (int k = 0; k < n; ++k) B[i][k] = B[i][k] * inv % M;
		for (int j = 0; j < n; ++j) {
			if (i == j || A[j][i] == 0) continue;
			ll cor = A[j][i];
			for (int k = i; k < n; ++k)
				A[j][k] = (A[j][k] - cor * A[i][k] % M + M) % M;
			for (int k = 0; k < n; ++k)
				B[j][k] = (B[j][k] - cor * B[i][k] % M + M) % M;
		}
	}
	return B;
}
