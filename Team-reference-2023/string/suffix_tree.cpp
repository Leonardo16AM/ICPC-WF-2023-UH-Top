template <typename charT, typename Container>
struct suffix_tree{
	vector<charT> s;
	vector<Container> next;
	vector<int> spos, len, link;
	int node, pos, last;
	suffix_tree() { make_node(0), node = pos = 0; }
	int make_node(int p, int l = 2e9){
		spos.push_back(p);
		len.push_back(l);
		link.push_back(0);
		next.emplace_back();
		return spos.size() - 1;
	}
	void extend(charT c){
		for (s.push_back(c), ++pos, last = 0; pos > 0;){
			int n = s.size();
			while (pos > len[next[node][s[n - pos]]])
				node = next[node][s[n - pos]], pos -= len[node];
			charT edge = s[n - pos];
			int v = next[node][edge];
			charT t = s[spos[v] + pos - 1];
			if (v == 0){
				v = make_node(n - pos);
				link[last] = node;
				last = 0;
			}
			else if (t == c){ link[last] = node; return; }
			else{
				int u = make_node(spos[v], pos - 1);
				next[u][c] = spos.size(), make_node(n - 1);
				next[u][t] = v;
				spos[v] += pos - 1;
				len[v] -= pos - 1;
				v = last = link[last] = u;
			}
			next[node][edge] = v;
			if (node == 0) --pos;
			else node = link[node];
		}
	}
	int get_len(int p) { return p == 0 ? 0 : 
					min(len[p], (int)s.size() - spos[p]); }
};
