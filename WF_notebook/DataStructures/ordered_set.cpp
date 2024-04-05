/*
   Title: GNU pbds ordered statistic set
   Description: Set with random element acess
   Complexity:  All operations O(log n)
   find_by_order(i) -> iterator to the i-th element (0 indexed)
   order_of_key(k) -> number of elements strictly smaller than k*/
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;
int main() { 
     ordered_set o_set; 
     o_set.insert(5); 
     o_set.insert(1); 
     o_set.insert(2); 
  
     // Finding the second smallest element
     cout << *(o_set.find_by_order(1)) << endl; 
  
     // Finding the number of elements strictly less than k=4 
     cout << o_set.order_of_key(4) << endl; 
     if (o_set.find(2) != o_set.end()) 
        o_set.erase(o_set.find(2)); 
} 