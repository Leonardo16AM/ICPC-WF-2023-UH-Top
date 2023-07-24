/*
  koder : melkor
  TASK  : LCA Problem using DP (online)
  
  Performance:
    Preprocess logarithms --> O(V)
    Build tree            --> O(V)
    buildSparseTable      --> O(V log V)
    queryLCA              --> O(log V)
*/

#include <cstdio>
#include <queue>

#define LOGV 16
#define MAXV 1 << LOGV

using namespace std;

struct Node {
  int v, next;
} L[MAXV];

int V, Q;
int u, v;

int P[MAXV];
int level[MAXV], parent[MAXV];
int lg[MAXV];
int LCA[MAXV][LOGV];

void buildSparseTable() {

  queue< int > Q;
  level[0] = 0; parent[0] = -1;
  
  for ( Q.push( 0 ); !Q.empty(); Q.pop() ) {

    int u = Q.front();

    for ( int i = P[u]; i != -1; i = L[i].next ) {

      int v = L[i].v;
      if ( v == parent[u] ) continue;

      parent[v] = u;
      level[v] = level[u] + 1;
      Q.push( v );
      
      // DP
      
      LCA[v][0] = u;
      for ( int j = 1; j <= lg[ level[v] ]; j++ )
        LCA[v][j] = LCA[ LCA[v][ j - 1 ] ][ j - 1 ];
    }
  }
}

int queryLCA( int u, int v ) {

  if ( level[u] < level[v] ) swap( u, v );
  
  if ( level[u] != level[v] )
    for ( int i = lg[ level[u] ]; i >= 0; i-- )
      if ( level[u] - ( 1 << i ) >= level[v] )
        u = LCA[u][i];
  
  if ( u == v ) return u;
  
  for ( int i = lg[ level[u] ]; i >= 0; i-- )
    if ( level[u] - ( 1 << i ) >= 0 && LCA[u][i] != LCA[v][i] ) {
      u = LCA[u][i];
      v = LCA[v][i];
    }
  
  return parent[u];
}

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%d", &V );
  
  fill( P, P + V, -1 );
  
  // Preprocess logarithms
  
  lg[0] = -1;
  for ( int i = 1; i < MAXV; i++ )
    lg[i] = lg[ i - 1 ] + !( i & ( i - 1 ) );
  
  // Read tree
  
  for ( int i = 0; i < V - 1; i++ ) {

    scanf( "%d %d", &u, &v );
    u--; v--;

    L[ 2 * i ] = ( Node ) { v, P[u] }; 
    P[u] = 2 * i;

    L[ 2 * i + 1 ] = ( Node ) { u, P[v] };
    P[v] = 2 * i + 1;
  }
  
  buildSparseTable();
  
  // Read queries
  
  scanf( "%d", &Q );
  for ( int i = 0; i < Q; i++ ) {
    scanf( "%d %d", &u, &v );
    printf( "LCA( %d, %d ) = %d\n", u, v, queryLCA( u - 1, v - 1 ) + 1 );
  }

  return 0;
}//melkor
