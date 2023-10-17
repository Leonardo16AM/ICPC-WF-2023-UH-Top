/*  pb_ds_tree allowing:
		order_of_key(x) number of keys less that x
		find_by_order(k) find the k-th key
	Notes: Duplicated keys are not allowed, use pair<key, int> instead */
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, 
	tree_order_statistics_node_update>;
