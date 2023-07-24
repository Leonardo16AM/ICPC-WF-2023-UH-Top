#include <bits/stdc++.h>
using namespace std;
/*
    Tested:
        codeforces.com/gym/102220/problem/D
*/

struct LCA{

    vector< vector<int> > lca;
    vector<int> level, parent, lg;

    LCA (int n,vector<int> *adj) : level(n),parent(n),lg(n+1),lca(n) {
        lg[0]=-1;
        for(int i=1;i<=n;i++)
            lg[i]=lg[i-1]+!(i&(i-1));

        for(int i=0;i<n;i++)
            lca[i].resize(lg[n]+1);

        buildSparseTable(0,adj);
    }

    void buildSparseTable(int root,vector<int> *g)
    {
        queue< int > Q;
        level[root] = 0;
        parent[root] = -1;

        for ( Q.push( root ); !Q.empty(); Q.pop() )
        {
            int u = Q.front();

            for ( auto v : g[u])
            {
                if ( v == parent[u] ) continue;

                parent[v] = u;
                level[v] = level[u] + 1;
                Q.push( v );

                lca[v][0] = u;
                for ( int j = 1; j <= lg[ level[v] ]; j++ )
                    lca[v][j] = lca[ lca[v][ j - 1 ] ][ j - 1 ];
            }
        }
    }

    int query( int u, int v )
    {
        if ( level[u] < level[v] ) swap( u, v );

        if ( level[u] != level[v] )
            for ( int i = lg[ level[u] ]; i >= 0; i-- )
                if ( level[u] - ( 1 << i ) >= level[v] )
                    u = lca[u][i];

        if ( u == v ) return u;

        for ( int i = lg[ level[u] ]; i >= 0; i-- )
            if ( lca[u][i] != lca[v][i] )
            {
                u = lca[u][i];
                v = lca[v][i];
            }

        return parent[u];
    }
};

int main()
{
    return 0;
}
