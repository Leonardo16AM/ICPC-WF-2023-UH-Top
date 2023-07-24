vector<point> convex_hull(vector<point> v){
	int n = v.size(), k = 0;
	vector<point> ch(2 * n);
	sort(v.begin(), v.end(), cmp);
    for (ll i = k = 0; i < n; ch[k++] = v[i++])
        while (k > 1 && cross(ch[k - 2], ch[k - 1], v[i]) <= 0) --k;
    for (ll i = n - 2, t = k; i >= 0; ch[k++] = v[i--])
        while (k > t && cross(ch[k - 2], ch[k - 1], v[i]) <= 0) --k;
    ch.resize(k - (k > 1));
	return ch;
}