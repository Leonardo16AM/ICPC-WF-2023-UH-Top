// z[i] = length of the longest common prefix of s and s[i..n]
vector<int> zfunction(const string &s){
	int n = s.length();
	vector<int> z(n, n);
	for (int i = 1, g = 0, f; i < n; ++i)
		if (i < g && z[i - f] != g - i) z[i] = min(z[i - f], g - i);
		else {
			for (g = max(g, i), f = i; g < n && s[g] == s[g - f]; ++g);
			z[i] = g - f;
		}
	return z;
}