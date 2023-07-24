template<typename T>
struct dinic
{
    struct edge
    {
        int src, dst;
        T cap, flow;
        int rev;
    };

    int n;
    vector< vector<edge> > adj;

    dinic(int n) : n(n), adj(n) {}

    void add_edge(int src, int dst, T cap)
    {
        adj[src].push_back({ src, dst, cap, 0, (int) adj[dst].size() });
        if (src == dst)
            adj[src].back().rev++;
        adj[dst].push_back({ dst, src, 0, 0, (int) adj[src].size() - 1 });
    }

    vector<int> level, iter;

    T augment(int u, int t, T cur)
    {
        if (u == t)
            return cur;
        for (int &i = iter[u]; i < (int) adj[u].size(); ++i)
        {
            edge &e = adj[u][i];
            if (e.cap - e.flow > 0 && level[u] > level[e.dst])
            {
                T f = augment(e.dst, t, min(cur, e.cap - e.flow));
                if (f > 0)
                {
                    e.flow += f;
                    adj[e.dst][e.rev].flow -= f;
                    return f;
                }
            }
        }
        return 0;
    }

    int bfs(int s, int t)
    {
        level.assign(n, n);
        level[t] = 0;
        queue<int> Q;
        for (Q.push(t); !Q.empty(); Q.pop())
        {
            int u = Q.front();
            if (u == s)
                break;
            for (int i = 0; i < (int)adj[u].size(); ++i){
                edge &e = adj[u][i];
                edge &erev = adj[e.dst][e.rev];
                if (erev.cap - erev.flow > 0
                    && level[e.dst] > level[u] + 1)
                {
                    Q.push(e.dst);
                    level[e.dst] = level[u] + 1;
                }
            }
        }
        return level[s];
    }

    const T oo = numeric_limits<T>::max();

    T max_flow(int s, int t)
    {
        for (int u = 0; u < n; ++u) // initialize
            for (int i = 0; i < (int)adj[u].size(); ++i){
                edge &e = adj[u][i];
                e.flow = 0;
            }

        T flow = 0;
        while (bfs(s, t) < n)
        {
            iter.assign(n, 0);
            for (T f; (f = augment(s, t, oo)) > 0;)
                flow += f;
        } // level[u] == n ==> s-side
        return flow;
    }
};
