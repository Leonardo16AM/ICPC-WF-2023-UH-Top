/*
	Grahpic sequence recognition

	Tested: UVA 11414, 10720
*/
	
bool is_graphic(vector<int> d)
{
	int n = d.size();
	sort(d.rbegin(), d.rend());
	vector<int> s(n + 1);
	for (int i = 0; i < n; ++i)
		s[i + 1] = s[i] + d[i];
	if (s[n] % 2)
		return false;
	for (int k = 1; k <= n; ++k)
	{
		int p = lower_bound(d.begin() + k, d.end(), k, greater<int>()) 
				- d.begin();
		if (s[k] > k * (p - 1) + s[n] - s[p])
			return false;
	}
	return true;
}
