// Maximum flow of minimum cost with potentials
// Complexity: O(min(m^2 n log n, m log n flow))
template<typename T, typename C = T>
struct min_cost_flow{
	struct edge{
		int src, dst;
		T cap, flow;
		C cost;
		int rev;
	};
	int n;
	vector<vector<edge>> adj;
	min_cost_flow(int n) : n(n), adj(n) {}
	void add_edge(int src, int dst, T cap, C cost){
		adj[src].push_back({src, dst, cap, 0, cost,
		    (int)adj[dst].size()});
		if (src == dst) adj[src].back().rev++;
		adj[dst].push_back({dst, src, 0, 0, -cost, 
			(int)adj[src].size() - 1});
	}
	const C oo = numeric_limits<C>::max();
	vector<C> dist, pot;
	vector<edge*> prev;
	vector<T> curflow;
	void bellman_ford(int s, int t){
		pot.assign(n, oo);
		pot[s] = 0;
		for (int it = 0, change = true; it < n && change; ++it){
			change = false;
			for (int u = 0; u < n; ++u) if (pot[u] != oo) {
					for (auto &e : adj[u])
						if (e.flow < e.cap 
							&& pot[e.dst] > pot[u] + e.cost) {
							pot[e.dst] = pot[u] + e.cost;
							change = true;
						}
				}
		}
	}
	bool dijkstra(int s, int t){
		dist.assign(n, oo);
		prev.assign(n, nullptr);
		dist[s] = 0;
		curflow[s] = numeric_limits<T>::max();
		using pci = pair<C, int>;
		priority_queue<pci, vector<pci>, greater<pci>> pq;
		pq.push({ 0, s });
		while (!pq.empty()){
			C d; int u;
			tie(d, u) = pq.top();
			pq.pop();
			if (d != dist[u]) continue;
			for (auto &e : adj[u])
				if (e.flow < e.cap && dist[e.dst] > dist[u] 
					+ e.cost + pot[u] - pot[e.dst]){
					dist[e.dst] = dist[u] + e.cost 
							+ pot[u] - pot[e.dst];
					prev[e.dst] = &e;
					curflow[e.dst] = min(curflow[u], e.cap - e.flow);
					pq.push({ dist[e.dst], e.dst });
				}
		}
		return dist[t] < oo;
	}
	pair<T, C> max_flow(int s, int t, bool neg_edges = true){
		T flow = 0;
		C cost = 0;
		curflow.assign(n, 0);
		if (neg_edges) bellman_ford(s, t);
		else pot.assign(n, 0);
		while (dijkstra(s, t)){
			for (int u = 0; u < n; ++u)
				if (dist[u] < oo) pot[u] += dist[u];
			T delta = curflow[t];
			flow += delta;
			for (edge *e = prev[t]; e != nullptr; e = prev[e->src]){
				e->flow += delta;
				adj[e->dst][e->rev].flow -= delta;
				cost += delta * e->cost;
			}
		}
		return {flow, cost};
	}
};
