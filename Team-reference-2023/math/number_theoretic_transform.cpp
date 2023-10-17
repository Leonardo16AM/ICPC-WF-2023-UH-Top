// Notes: mod = 2**k * c + 1 should be prime, k >= max_degree
namespace ntt{
	const int mod = 998244353;
	const int root = 5; // primitive root of mod
	int base = 1;
	vector<int> roots;
	void ensure_base(int nbase){
		if (nbase <= base) return;
		roots.resize(nbase);
		for (int mh = base; mh << 1 <= nbase; mh <<= 1){
			int wm = pow_mod(root, (mod - 1) / (mh << 1), mod);
			roots[mh] = 1;
			for (int i = 1; i < mh; ++i)
				roots[i + mh] = (ll)roots[i + mh - 1] * wm % mod;
		}
		base = nbase;
	}
	void fft(int a[], int n, int sign){
		ensure_base(n);
		for (int i = 1, j = 0; i < n - 1; ++i){
			for (int k = n >> 1; (j ^= k) < k; k >>= 1);
			if (i < j) swap(a[i], a[j]);
		}
		for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
			for (int i = 0; i < n; i += m)
				for (int j = i; j < i + mh; ++j){
					int y = (ll)a[j + mh] * roots[j - i + mh] % mod;
					if ((a[j + mh] = a[j] - y) < 0) a[j + mh] += mod;
					if ((a[j] += y) >= mod) a[j] -= mod;
				}
		if (sign < 0){
			int inv = pow_mod(n, mod - 2, mod);
			for (int i = 0; i < n; ++i) a[i] = (ll)a[i] * inv % mod;
			reverse(a + 1, a + n);
		}
	}
	vector<int> convolve(vector<int> x, vector<int> y){
		int n = x.size() + y.size() - 1, sz = 1;
		while (sz < n) sz <<= 1;
		x.resize(sz);
		y.resize(sz);
		fft(x.data(), sz, +1);
		fft(y.data(), sz, +1);
		for (int i = 0; i < sz; ++i)
			x[i] = (ll)x[i] * y[i] % mod;
		fft(x.data(), sz, -1);
		x.resize(n);
		return x;
	}
}
