/*
	Tested: SPOJ VFMUL
	Complexity: O(n log n)
*/

typedef complex<double> point;

void fft(vector<point> &a, int sign = 1)
{
	int n = a.size(); // n should be a power of two
	double theta = 8 * sign * atan(1.0) / n;
	for (int i = 0, j = 1; j < n - 1; ++j)
	{
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
	{
		int irev = 0;
		for (int i = 0; i < n; i += m)
		{
			point w = polar(1.0, theta * irev);
			for (int k = n >> 2; k > (irev ^= k); k >>= 1);
			for (int j = i; j < mh + i; ++j)
			{
				int k = j + mh;
				point x = a[j] - a[k];
				a[j] += a[k];
				a[k] = w * x;
			}
		}
	}
	if (sign == -1)
		for (auto &p : a)
			p /= n;
}

// for parse integers as polynomials

typedef long long ll;

const int WIDTH = 5;
const ll RADIX = 100000; // = 10^WIDTH

vector<point> parse(const char s[])
{
	int n = strlen(s);
	int m = (n + WIDTH - 1) / WIDTH;
	vector<point> v(m);
	for (int i = 0; i < m; ++i)
	{
		int b = n - WIDTH * i, x = 0;
		for (int a = max(0, b - WIDTH); a < b; ++a)
			x = x * 10 + s[a] - '0';
		v[i] = x;
	}
	return v;
}

void print(const vector<point> &v)
{
	int i, N = v.size();
	vector<ll> digits(N + 1, 0);
	long double err = 0;

	for (i = 0; i < N; i++)
		digits[i] = (ll) (v[i].real() + 0.5);
	ll c = 0;
	for (i = 0; i < N; ++i)
	{
		c += digits[i];
		digits[i] = c % RADIX;
		c /= RADIX;
	}
	for (i = N - 1; i > 0 && digits[i] == 0; --i);
	printf("%lld", digits[i]);
	for (--i; i >= 0; --i)
		printf("%.*lld", WIDTH, digits[i]);
	printf("\n");
}
