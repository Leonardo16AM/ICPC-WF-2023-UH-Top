/*
	Modular arithmetics (long long)

	Note:
		int       < 2^31 < 10^9
		long long < 2^63 < 10^18
	feasible for M < 2^62 (10^18 < 2^62 < 10^19)

	Tested: SPOJ
*/

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

ll add(ll a, ll b, ll M)
{
	a += b;
	if (a >= M) a -= M;
	return a;
}

ll sub(ll a, ll b, ll M)
{
	if (a < b) a += M;
	return a - b;
}

ll mul(ll a, ll b, ll M)
{
	ll q = (long double) a * (long double) b / (long double) M;
	ll r = a * b - q * M;
	return (r + 5 * M) % M;
}

ll pow(ll a, ll b, ll M)
{
	ll x = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1) x = mul(x, a, M);
		a = mul(a, a, M);
	}
	return x;
}

ll inv(ll b, ll M)
{
	ll u = 1, x = 0, s = b, t = M;
	while (s)
	{
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	return (x %= M) >= 0 ? x : x + M;
}

// solve a * x = b (M)
ll div(ll a, ll b, ll M)
{
	ll u = 1, x = 0, s = b, t = M;
	while (s)
	{
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	if (a % t) return -1; // infeasible
	return mul(x < 0 ? x + M : x, a / t, M);
}

// Modular Matrix
mat eye(int n)
{
	mat I(n, vec(n));
	for (int i = 0; i < n; ++i)
		I[i][i] = 1;
	return I;
}

mat zeros(int n)
{
	return mat(n, vec(n));
}

mat mul(mat A, mat B, ll M)
{
	int l = A.size(), m = B.size(), n = B[0].size();
	mat C(l, vec(n));
	for (int i = 0; i < l; ++l)
		for (int k = 0; k < m; ++k)
			for (int j = 0; j < n; ++j)
				C[i][j] = add(C[i][j], mul(A[i][k], B[k][j], M), M);
	return C;
}

mat pow(mat A, ll b, ll M)
{
	mat X = eye(A.size());
	for (; b > 0; b >>= 1)
	{
		if (b & 1) X = mul(X, A, M);
		A = mul(A, A, M);
	}
	return X;
}

// assume: M is prime (singular ==>
// verify: SPOJ9832
mat inv(mat A, ll M)
{
	int n = A.size();
	mat B(n, vec(n));
	for (int i = 0; i < n; ++i)
		B[i][i] = 1;

	for (int i = 0; i < n; ++i)
	{
		int j = i;
		while (j < n && A[j][i] == 0) ++j;
		if (j == n)
			return {};
		swap(A[i], A[j]);
		swap(B[i], B[j]);
		ll inv = div(1, A[i][i], M);
		for (int k = i; k < n; ++k)
			A[i][k] = mul(A[i][k], inv, M);
		for (int k = 0; k < n; ++k)
			B[i][k] = mul(B[i][k], inv, M);
		for (int j = 0; j < n; ++j)
		{
			if (i == j || A[j][i] == 0)
				continue;
			ll cor = A[j][i];
			for (int k = i; k < n; ++k)
				A[j][k] = sub(A[j][k], mul(cor, A[i][k], M), M);
			for (int k = 0; k < n; ++k)
				B[j][k] = sub(B[j][k], mul(cor, B[i][k], M), M);
		}
	}

	return B;
}
