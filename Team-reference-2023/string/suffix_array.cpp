// Notes: The suffix starting in |S| is always the lowest 
// and have lcp 0 with the next suffix.
// 		lcp[i] is the longest common prefix between 
// 		the suffix in sa[i] and sa[i-1]
struct suffix_array{
	int n;
	vector<int> sa, lcp, rank;
	template<typename RAIter>
	suffix_array(const RAIter &bg, const RAIter &nd, int alp = 256)
		: n(nd - bg + 1), sa(n), lcp(n), rank(n){
		vector<int> ws(max(n, alp));
		auto &x = lcp, &y = rank;
		copy(bg, nd, x.begin());
		iota(sa.begin(), sa.end(), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), alp = p){
			p = j, iota(y.begin(), y.end(), n - j);
			fill(ws.begin(), ws.end(), 0);
			for (int i = 0; i < n; ws[x[i++]]++)
				if (sa[i] >= j) y[p++] = sa[i] - j;
			partial_sum(ws.begin(), ws.end(), ws.begin());
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			x.swap(y), p = 1, x[sa[0]] = 0;
			for (int i = 1, a, b; i < n; ++i)
				a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0; i < n; ++i) rank[sa[i]] = i;
		for (int i = 0, j, k = lcp[0] = 0; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					bg[i + k] == bg[j + k]; k++);
	}
};
