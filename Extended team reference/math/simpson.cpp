
template<class F>
double simpson(F f, double a, double b, int n = 2000)
{
	double h = (b - a) / (2 * n), fa = f(a), nfa, res = 0;
	for (int i = 0; i < n; ++i, fa = nfa)
	{
		nfa = f(a + 2 * h);
		res += (fa + 4 * f(a + h) + nfa);
		a += 2 * h;
	}
	res = res * h / 3;
	return res;
}
