struct aho_corasick{
	static const int alpha = 26;
	vector<array<int, alpha>> go;
	vector<int> fail, endpos;
	aho_corasick() { add_node(); }
	int add_string(const string &str){
		int e = 0;
		for (char c : str){
			if (!go[e][c-'a']){
				int nn = add_node();
				go[e][c-'a'] = nn;
			}
			e = go[e][c-'a'];
		}
		++endpos[e];
		return e;
	}
	void build(){
		queue<int> que;
		for (int c = 0; c < alpha; ++c)
			if (go[0][c]) que.push(go[0][c]);
		for (; !que.empty(); que.pop()){
			int e = que.front();
			int f = fail[e];
			for (int c = 0; c < alpha; ++c)
				if (!go[e][c]) go[e][c] = go[f][c];
				else {
					fail[go[e][c]] = go[f][c];
					endpos[go[e][c]] += endpos[go[f][c]];
					que.push(go[e][c]);
				}
		}
	}
private:
	int add_node(){
		int pos = go.size();
		go.emplace_back(array<int, alpha>());
		fail.emplace_back(0);
		endpos.emplace_back(0);
		return pos;
	}
};