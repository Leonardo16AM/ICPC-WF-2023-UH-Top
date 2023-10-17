vector<int> g[MAXN], nodes;
bool mk[MAXN]; //marks centroid taken before
int sz[MAXN], mx[MAXN];
void dfs1(int u, int p){
	sz[u] = 1;
	nodes.push_back(u);
	for (auto v : g[u])
		if (!mk[v]){ 
			dfs1(v, u);
			sz[u] += sz[v];
			mx[u] = max(sz[v], mx[u]);
		}
}
void dfs2(int u, int p){
	nodes.push_back(u);
	for (auto v : g[u])
		if (!mk[v]) dfs2(v, u);
}
void solve(int u){
	dfs1(u, -1);
	int cent = -1, cant = nodes.size() / 2;
	for (auto v : nodes){
		if (cent == -1 && sz[v] >= cant && mx[v] <= cant) cent = v;
		sz[v] = mx[v] = 0;
	}
	nodes.clear();
	mk[cent] = 1;
	for (auto v : g[cent]){
		if (mk[v]) continue;
		dfs2(v, cent);
		for (auto y : nodes) ;
		nodes.clear();
	}
	for (auto v : g[cent]) if (!mk[v]) solve(v);
}