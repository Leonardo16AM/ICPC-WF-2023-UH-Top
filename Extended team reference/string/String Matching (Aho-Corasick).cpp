/*
  koder : melkor
  TASK  : Aho-Corasick Pattern Matcher Automaton
          Given a set P = {p1, p2, ..., pk} of patterns
          and a text T[1...m], we want to locate occurrences
          of any pattern of P in T.

  Remarks: Using English alphabet (|S|=26). This automata
           approach is dependent on the alphabet's size
           (but for practical purposes that's a constant)
  Running time:
          Preprocessing: O(n|S|)
          Matching: Theta(m + z)
  n = Sigma[i=1...k] |pi|
  z = number of pattern occurrences in T
*/

#include <cstdio>
#include <queue>

using namespace std;

#define MAXN 50000
#define MAXLEN 1001
#define ALPHA 26

struct PMA {

  PMA *fail;        /* failure function */
  PMA *next[ALPHA]; /* goto function */
  int pos;
  PMA *link;

  PMA() : pos( -1 ), link( 0 ) { memset( next, 0, sizeof( next ) ); }
} *root;

int N;
char c;
PMA *t, *v;

char P[MAXN][MAXLEN];
int result[MAXN];

void build_AC_automaton() {

  /*
    Phase I
      - construct the keyword tree for P
      - for each p in P added to the tree, out(v) = {p} for
        the node v labeled by p
      - t->next[c] is function goto(t,c)
  */

  root = new PMA;
  
  for ( int i = 0; i < N; i++ ) {
    t = root;
    for ( int j = 0; P[i][j] != '\0'; j++ ) {
      char c = P[i][j] - 'a';
      if ( !t->next[c] ) t->next[c] = new PMA;
      t = t->next[c];
    }
    t->pos = i;
  }
  
  /*
    Phase II
      - complete goto function for the root by setting
        goto(root,a) = root for each a in S that doesn't
        label an edge out of the root
      - compute failure function for nodes on level 1
      - compute failure function for all other nodes using BFS
  */
  
  queue< PMA* > Q;
  for ( int c = 0; c < ALPHA; c++ ) {
    if ( root->next[c] ) {
      root->next[c]->fail = root;
      Q.push( root->next[c] );
    } else root->next[c] = root;
  }
  
  while ( !Q.empty() ) {
    t = Q.front(); Q.pop();
    for ( int c = 0; c < ALPHA; c++ ) {
      if ( t->next[c] ) {
        Q.push( t->next[c] );
        v = t->fail;
        while ( !v->next[c] ) v = v->fail;
        t->next[c]->fail = v->next[c];
        if ( t->next[c]->fail->pos != -1 )
             t->next[c]->link = t->next[c]->fail;
        else t->next[c]->link = t->next[c]->fail->link;
      }
    }
  }
}

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%d", &N );
  for ( int i= 0; i < N; i++ )
    scanf( "%s", P[i] );
  
  build_AC_automaton();
  
  /* Pattern Matching */
  
  c = getchar();
  t = root;
  while ( ( c = getchar() ) != EOF ) {
    c -= 'a';
    while ( !t->next[c] ) t = t->fail;
    t = t->next[c];
    if ( t->pos != -1 )
      result[ t->pos ]++;
    for ( v = t->link; v; v = v->link )
      result[ v->pos ]++;
  }
  
  for ( int i = 0; i < N; i++ ) {
    for ( int j = 0; P[i][j] != '\0'; j++ )
      printf( "%c", P[i][j] );
    printf( " %d\n", result[i] );
  }

  return 0;
}//melkor
