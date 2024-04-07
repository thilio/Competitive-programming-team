/* Set with random element acess
Complexity:  All operations O(log n)
find_by_order(i) -> iterator to the i-th element (0 indexed)
order_of_key(k) -> # of elements strictly smaller than k
    
ordered_set o_set; 
Finding the second smallest element
   auto q = *(o_set.find_by_order(1); 
Finding the number of elements strictly less than k=4 
   int n = o_set.order_of_key(4); 
*/
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;