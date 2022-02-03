/*
   Title: GNU pbds ordered statistic set
   Description: Set with random element acess
   Complexity:  All operations O(log n)
  
   Details: 
   find_by_order(i) -> iterator to the i-th element (0 indexed)
   order_of_key(k) -> number of elements strictly smaller than k
*/

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;