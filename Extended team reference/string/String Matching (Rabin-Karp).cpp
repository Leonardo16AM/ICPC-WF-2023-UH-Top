/*
  koder : melkor
  TASK  : Given a pattern P[1...m] and a test T[1...n], find all
          occurrences of P in T
  
  Running time:
          Preprocessing: Theta(m)
          Matching: O((n - m + 1)m)
*/

#include <cstdio>
#include <cstring>
#include <deque>

using namespace std;

#define MAXL 50005
#define MOD 1000003
#define BASE 26

int N, E, cnt;
int hp, ht;
char c;

char pattern[MAXL];
deque< char > q;

inline int intMod( int a, int b ) { return ( a % b + b ) % b; }

bool equal() {
  int i = 0;
  for ( deque< char >::iterator it = q.begin(); it != q.end(); it++, i++ )
    if ( *it != pattern[i] ) return 0;
  return 1;
}

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%s\n", pattern );
  N = strlen( pattern );
  
  // Calculate E = BASE^(N-1) mod MOD
  
  E = 1;
  for ( int i = 0; i < N - 1; i++ ) E = BASE * E % MOD;
  
  // Hashing the pattern
  
  hp = 0;
  for ( int i = 0; i < N; i++ )
    hp = intMod( BASE * hp + pattern[i], MOD );
  
  // Hash the first N characters of the text
  
  ht = 0;
  for ( int i = 0; i < N; i++ ) {
    scanf( "%c", &c ); cnt++;
    q.push_back( c );
    ht = intMod( BASE * ht + c, MOD );
  }
  
  if ( ht == hp )
    if ( equal() ) printf( "%d\n", cnt - N );
  
  // Continue hashing the characters of the text
  
  while ( ( c = getchar() ) != EOF ) {
    
    cnt++;
    ht = intMod( ht - intMod( q.front() * E, MOD ), MOD );
    ht = intMod( BASE * ht + c, MOD );
    
    q.pop_front();
    q.push_back( c );
    
    if ( ht == hp )
      if ( equal() ) printf( "%d\n", cnt - N );
  }

  return 0;
}//melkor
