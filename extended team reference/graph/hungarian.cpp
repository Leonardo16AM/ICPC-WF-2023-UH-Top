/*
    Maximum assignment (Kuhn-Munkres)

    Description:
    - We are given a cost table of size n times m with n <= m.
    - It finds a maximum cost assignment, i.e.,
                max sum_{ij} c(i,j) x(i,j)
        where   sum_{i in [n]} x(i,j) = 1,
                sum_{j in [m]} x(i,j) <= 1.

    Complexity: O(n^3)

    Tested: http://www.spoj.com/problems/SCITIES/
*/

template <typename T> T max_assignment(const vector<vector<T>> &a) {
	int n = a.size(), m = a[0].size();
	assert(n <= m);

	vector<int> x(n, -1), y(m, -1);
	vector<T> px(n, numeric_limits<T>::min()), py(m, 0);

	for (int u = 0; u < n; ++u)
		for (int v = 0; v < m; ++v)
			px[u] = max(px[u], a[u][v]);

	for (int u = 0, p, q; u < n;) {
		vector<int> s(n + 1, u), t(m, -1);

		for (p = q = 0; p <= q && x[u] < 0; ++p)
			for (int k = s[p], v = 0; v < m && x[u] < 0; ++v)
				if (px[k] + py[v] == a[k][v] && t[v] < 0) {
					s[++q] = y[v], t[v] = k;
					if (s[q] < 0)
						for (p = v; p >= 0; v = p)
							y[v] = k = t[v], p = x[k], x[k] = v;
				}

		if (x[u] < 0) {
			T delta = numeric_limits<T>::max();

			for (int i = 0; i <= q; ++i)
				for (int v = 0; v < m; ++v)
					if (t[v] < 0)
						delta = min(delta, px[s[i]] + py[v] - a[s[i]][v]);

			for (int i = 0; i <= q; ++i)
				px[s[i]] -= delta;

			for (int v = 0; v < m; ++v)
				py[v] += (t[v] < 0 ? 0 : delta);
		} else
			++u;
	}

	T cost = 0;

	for (int u = 0; u < n; ++u)
		cost += a[u][x[u]];

	return cost;
}

template <typename T> T min_assignment(const vector<vector<T>> &c) {
	const int n = c.size(), m = c[0].size();  // assert(n <= m);
	vector<T> v(m), dist(m);                  // v: potential
	vector<int> matchL(n, -1), matchR(m, -1); // matching pairs
	vector<int> index(m), prev(m);

	iota(all(index), 0);

	auto residue = [&](int i, int j) {
		return c[i][j] - v[j];
	};

	for (int f = 0; f < n; ++f) {
		for (int j = 0; j < m; ++j) {
			dist[j] = residue(f, j);
			prev[j] = f;
		}
		T w;
		int j, l;
		for (int s = 0, t = 0;;) {
			if (s == t) {
				l = s;
				w = dist[index[t++]];
				for (int k = t; k < m; ++k) {
					j = index[k];
					T h = dist[j];
					if (h <= w) {
						if (h < w) {
							t = s;
							w = h;
						}
						index[k] = index[t];
						index[t++] = j;
					}
				}
				for (int k = s; k < t; ++k) {
					j = index[k];
					if (matchR[j] < 0)
						goto aug;
				}
			}
			int q = index[s++], i = matchR[q];
			for (int k = t; k < m; ++k) {
				j = index[k];
				T h = residue(i, j) - residue(i, q) + w;
				if (h < dist[j]) {
					dist[j] = h;
					prev[j] = i;
					if (h == w) {
						if (matchR[j] < 0)
							goto aug;
						index[k] = index[t];
						index[t++] = j;
					}
				}
			}
		}
	aug:
		for (int k = 0; k < l; ++k)
			v[index[k]] += dist[index[k]] - w;
		int i;
		do {
			matchR[j] = i = prev[j];
			swap(j, matchL[i]);
		} while (i != f);
	}
	T opt = 0;
	for (int i = 0; i < n; ++i)
		opt += c[i][matchL[i]]; // (i, matchL[i]) is a solution
	return opt;
}