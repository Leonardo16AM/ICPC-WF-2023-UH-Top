#include <bits/stdc++.h>
#define db(x)   cout << (x) << '\n';
#define all(v)  (v).begin(), (v).end()
#define allr(v) (v).rbegin(), (v).rend()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<double, ll> pdi;
typedef pair<string, ll> psi;
typedef pair<ll, string> pls;
typedef pair<string, string> pss;
typedef pair<ll, pii> pip;
typedef pair<pii, pii> ppp;

struct aho_corasick {
	/// vector failure
	/// ok: la mayor palabra que termina en el nodo i
	vector<ll> f, ok;
	/// g: funcion go, es para hacer el trie
	vector<vector<ll>> g;
	/// cantidad de palabras
	int k;

#define ALPHA 26
	int cv(char c) { return c - 'a'; }

	/// construccion
	aho_corasick(vector<string> vs) : k(vs.size()) {
		int n = 0;
		for (int i = 0; i < k; i++)
			n += vs[i].size();

		f = vector<ll>(n + 1, 0);
		ok = vector<ll>(n + 1, -1);
		g = vector<vector<ll>>(n + 1, vector<ll>(ALPHA, -1));

		int cont = 1;
		for (int i = 0; i < k; i++) {
			int pos = 0;
			for (int j = 0; j < vs[i].size(); j++) {
				int v = cv(vs[i][j]);
				if (g[pos][v] == -1) {
					g[pos][v] = cont;
					cont++;
				}
				pos = g[pos][v];
			}

			ok[pos] = i;
		}

		for (int i = 0; i < ALPHA; i++)
			if (g[0][i] == -1)
				g[0][i] = 0;

		queue<int> q;
		for (int i = 0; i < ALPHA; i++)
			if (g[0][i]) {
				f[g[0][i]] = 0;
				q.push(g[0][i]);
			}

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int i = 0; i < ALPHA; i++)
				if (g[u][i] != -1) {
					int fail = f[u];
					while (g[fail][i] == -1)
						fail = f[fail];

					fail = g[fail][i];
					f[g[u][i]] = fail;

					if (ok[g[u][i]] == -1)
						ok[g[u][i]] = ok[fail];

					q.push(g[u][i]);
				}
		}
	}

	/// funcion para pasar al siguiente estado
	int next(int current, int ch) {
		while (g[current][ch] == -1)
			current = f[current];
		return g[current][ch];
	}
};

struct aho_corasick_extra_stuff {
	/// vector failure
	/// ok: la mayor palabra que termina en el nodo i
	vector<ll> f, ok;
	/// g: funcion go, es para hacer el trie
	vector<vector<ll>> g;
	/// cantidad de palabras
	int k;
	vector<ll> abi, ts;
	/// intervalo que le corresponde a la palabra i-esima
	vector<pii> lims;

#define ALPHA 26
	int cv(char c) { return c - 'a'; }

	/// construccion
	aho_corasick_extra_stuff(vector<string> vs)
	    : k(vs.size()), abi(2 * k + 1), ts(k), lims(k) {
		int n = 0;
		for (int i = 0; i < k; i++)
			n += vs[i].size();

		f = vector<ll>(n + 1, 0);
		ok = vector<ll>(n + 1, -1);
		g = vector<vector<ll>>(n + 1, vector<ll>(ALPHA, -1));

		int cont = 1;
		for (int i = 0; i < k; i++) {
			int pos = 0;
			for (int j = 0; j < vs[i].size(); j++) {
				int v = cv(vs[i][j]);
				if (g[pos][v] == -1) {
					g[pos][v] = cont;
					cont++;
				}
				pos = g[pos][v];
			}

			ok[pos] = i;
		}

		for (int i = 0; i < ALPHA; i++)
			if (g[0][i] == -1)
				g[0][i] = 0;

		queue<int> q;
		for (int i = 0; i < ALPHA; i++)
			if (g[0][i]) {
				f[g[0][i]] = 0;
				q.push(g[0][i]);
			}

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int i = 0; i < ALPHA; i++)
				if (g[u][i] != -1) {
					int fail = f[u];
					while (g[fail][i] == -1)
						fail = f[fail];

					fail = g[fail][i];
					f[g[u][i]] = fail;

					if (ok[g[u][i]] == -1)
						ok[g[u][i]] = ok[fail];

					q.push(g[u][i]);
				}
		}

		vector<psi> to_sort;
		for (int i = 0; i < k; i++) {
			reverse(all(vs[i]));
			to_sort.push_back(psi(vs[i], i));
		}

		sort(all(to_sort));

		for (int i = 0; i < k; i++) {
			ts[to_sort[i].second] = i;
			lims[i].first = i;

			int pos = k;
			for (int j = 0; j < to_sort[i].first.size(); j++)
				for (int po = (1 << 18); po; po >>= 1)
					if (pos - po > i &&
					    to_sort[pos - po].first[j] != to_sort[i].first[j])
						pos -= po;

			pos--;
			lims[i].second = pos;
		}

		for (int i = 0; i <= n; i++)
			if (ok[i] != -1)
				ok[i] = ts[ok[i]];
	}

	/// funcion para pasar al siguiente estado
	int next(int current, int ch) {
		while (g[current][ch] == -1)
			current = f[current];
		return g[current][ch];
	}

	void update(int p, int v) {
		while (p < 2 * k) {
			abi[p] += v;
			p += (p & -p);
		}
	}

	ll query(int p) {
		ll res = 0;
		while (p) {
			res += abi[p];
			p -= (p & -p);
		}
		return res;
	}

	/// funcion para matchear en un solo string
	vector<ll> match(string s) {
		int pos = 0;
		vector<int> ups;
		for (int i = 0; i < s.size(); i++) {
			pos = next(pos, cv(s[i]));
			if (ok[pos] != -1) {
				update(ok[pos] + 1, 1);
				ups.push_back(ok[pos] + 1);
			}
		}

		vector<ll> res(k);
		for (int i = 0; i < k; i++) {
			int tp = ts[i];
			res[i] = query(lims[tp].second + 1) - query(lims[tp].first);
		}

		for (auto y : ups)
			update(y, -1);
		return res;
	}

	/// funcion para matchear en varios strings
	vector<ll> match(vector<string> &vs) {
		vector<int> ups;
		for (auto s : vs) {
			int pos = 0;
			for (int i = 0; i < s.size(); i++) {
				pos = next(pos, cv(s[i]));
				if (ok[pos] != -1) {
					update(ok[pos] + 1, 1);
					ups.push_back(ok[pos] + 1);
				}
			}
		}

		vector<ll> res(k);
		for (int i = 0; i < k; i++) {
			int tp = ts[i];
			res[i] = query(lims[tp].second + 1) - query(lims[tp].first);
		}

		for (auto y : ups)
			update(y, -1);
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int patrones;
	cin >> patrones;
	vector<string> vs(patrones);
	for (int i = 0; i < patrones; i++)
		cin >> vs[i];

	aho_corasick ac(vs);

	int textos;
	cin >> textos;
	vector<string> ns(textos);
	for (int i = 0; i < textos; i++)
		cin >> ns[i];

	vector<ll> res = ac.match(ns);

	for (int i = 0; i < patrones; i++)
		db(res[i])

		    return 0;
}
