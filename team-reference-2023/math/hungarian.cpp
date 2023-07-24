// max weight matching
template<typename T>
T hungarian(const vector<vector<T>> &a){
	int n = a.size(), m = a[0].size(), p, q; // n <= m
	vector<T> fx(n, numeric_limits<T>::min()), fy(m, 0);
	vector<int> x(n, -1), y(m, -1);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) fx[i] = max(fx[i], a[i][j]);
	for (int i = 0; i < n;){
		vector<int> t(m, -1), s(n + 1, i);
		for (p = q = 0; p <= q && x[i] < 0; ++p)
			for (int k = s[p], j = 0; j < m && x[i] < 0; ++j)
				// be careful with comparison on doubles
				if (fx[k] + fy[j] == a[k][j] && t[j] < 0) { 
					s[++q] = y[j], t[j] = k;
					if (s[q] < 0) for (p = j; p >= 0; j = p)
						y[j] = k = t[j], p = x[k], x[k] = j;
				}
		if (x[i] < 0){
			T d = numeric_limits<T>::max();
			for (int k = 0; k <= q; ++k)
				for (int j = 0; j < m; ++j) if (t[j] < 0)
					d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
			for (int j = 0; j < m; ++j)
				fy[j] += (t[j] < 0 ? 0 : d);
			for (int k = 0; k <= q; ++k) fx[s[k]] -= d;
		}
		else ++i;
	}
	T ret = 0;
	for (int i = 0; i < n; ++i) ret += a[i][x[i]];
	return ret;
}
