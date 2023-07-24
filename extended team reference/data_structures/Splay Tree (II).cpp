/*
  koder : melkor
  TASK  : Coding a splay tree
  
  Remarks: Assuming keys are integers. This version uses a (recursive)
           bottom-up approach for splaying.

  Performance:
              Splay: O(log n)*
              Insert: O(log n)*
              Erase: O(log n)*
              Find: O(log n)*
              Count lesser than: O(log n)*
              Count greater than: O(log n)*
              
              * amortized
*/

#include <cstdlib>
#include <cassert>

struct SplayTree {
  
  #define RESIZE( x ) \
    ( (x)->l->size + (x)->r->size + (x)->cnt )
  
  static const int oo = 1 << 30;

  struct node {
    int key, size, cnt;
    node *l, *r;
  } *root, *null;
  
  int key;
  
  void splay( node*& t, const int& key ) {

    if ( t == null ) return;

    if ( key < t->key ) {
      if ( t->l != null ) {
        splay( t->l, key );
        node *y = t->l; t->l = y->r; y->r = t;
        t->size = RESIZE( t ); y->size = RESIZE( y );
        t = y;
      }
    }
    else if ( key > t->key ) {
      if ( t->r != null ) {
        splay( t->r, key );
        node *y = t->r; t->r = y->l; y->l = t;
        t->size = RESIZE( t ); y->size = RESIZE( y );
        t = y;
      }
    }
  }
  
  node* find( int x ) {
    splay( root, key = x );
	return ( root != null && x == root->key ) ? root : NULL;
  }
  
  node* new_node( int key, int size, int cnt, node* l, node *r ) {
    node *t = new node;
    t->key = key; t->size = size; t->cnt = cnt;
    t->l = l; t->r = r;
    return t;
  }
  
  void insert( int x ) {

    if ( root == null ) root = new_node( x, 1, 1, null, null );

    else {
      splay( root, key = x );
      if ( x < root->key ) {
	    node *t = new_node( x, root->size + 1, 1, root->l, root );
		root->l = null; root->size = RESIZE( root );
		root = t;
	  }
	  else if ( x > root->key ) {
	    node *t = new_node( x, root->size + 1, 1, root, root->r );
		root->r = null; root->size = RESIZE( root );
		root = t;
	  }
      else root->cnt++, root->size++;
    }
  }
  
  void erase( int x ) {

    if ( root == null ) return;

    splay( root, key = x );
    if ( x == root->key ) {
      node *t;
      if ( root->cnt > 1 ) root->cnt--;
      else {
        if ( root->l == null ) t = root->r;
        else {
          t = root->l;
          splay( t, x );
          t->r = root->r;
        }
        root = t;
      }
    }

    if ( root != null ) root->size = RESIZE( root );
  }
  
  int getMin() { /* assuming there is no key < -2^30 */
    assert( root != null );
    splay( root, -oo );
    return root->key;
  }
  
  int getMax() { /* assuming there is no key > 2^30 */
    assert( root != null );
    splay( root, +oo );
    return root->key;
  }
  
  int countLesserThan( int x ) {
    if ( root = null ) return 0;
    splay( root, key = x );
    if ( root->key < x )
         return root->l->size + root->cnt;
    else return root->l->size;
  }
  
  int countGreaterThan( int x ) {
    if ( root == null ) return 0;
	splay( root, key = x );
	if ( root->key <= x )
         return root->r->size;
    else return root->r->size + root->cnt;
  }
  
  SplayTree() {
    null = new node;
    null->size = null->cnt = 0;
    null->l = null->r = 0;
    root = null;
  }
};

int main() {
  return 0;
}//melkor
