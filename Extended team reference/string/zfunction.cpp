/*
	zfunction and suffix function

	Complexity: O(n)

	Tested:
	- http://www.spoj.com/problems/QUERYSTR/
	- http://codeforces.com/contest/126/problem/B
*/

// z[i] = length of the longest common prefix of s and s[i..n]
vector<int> zfunction(const string &s)
{
	int n = s.length();

	vector<int> z(n, n);

	for (int i = 1, g = 0, f; i < n; ++i)
		if (i < g && z[i - f] != g - i)
			z[i] = min(z[i - f], g - i);
		else
		{
			for (g = max(g, f = i); g < n && s[g] == s[g - f]; ++g);
			z[i] = g - f;
		}

	return z;
}

// suff[i] = length of the longest common suffix of s and s[0..i]
vector<int> suffixes(const string &s)
{
	int n = s.length();

	vector<int> suff(n, n);

	for (int i = n - 2, g = n - 1, f; i >= 0; --i)
	{
		if (i > g && suff[i + n - 1 - f] != i - g)
			suff[i] = min(suff[i + n - 1 - f], i - g);
		else
		{
			for (g = min(g, f = i); g >= 0 && 
				 s[g] == s[g + n - 1 - f]; --g);
			suff[i] = f - g;
		}
	}

	return suff;
}
