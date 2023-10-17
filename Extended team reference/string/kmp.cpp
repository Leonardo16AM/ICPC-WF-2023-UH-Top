/*
	Prefix function and Knuth-Morris-Pratt string matching

	Complexity: O(n + m)

	Tested: http://www.spoj.com/problems/NHAY/
*/

vector<int> prefix_function(const string &p)
{
	int n = p.length();

	vector<int> pref(n + 1);

	for (int i = 0, j = pref[0] = -1; i < n; pref[++i] = ++j)
		while (j >= 0 && p[i] != p[j]) j = pref[j];

	return pref;
}

vector<int> knuth_morris_pratt(const string &s, const string &p)
{
	int n = s.length(), m = p.length();

	vector<int> pref = prefix_function(p), matches;

	for (int i = 0, j = 0; i < n; ++i)
	{
		while (j >= 0 && s[i] != p[j]) j = pref[j];

		if (++j == m)
			matches.push_back(i - m + 1), j = pref[j];
	}

	return matches;
}
