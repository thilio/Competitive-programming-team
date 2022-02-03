// GNU pbds ordered set
// Set com acesso aleatório de elemento
// O(log(n)) para todas operações

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;
// Comandos
// find_by_order(i) -> iterador para o i-ésimo elemento (contando do zero)
// order_of_key(k) -> número de elementos estritamente menores que k
// pode-se subtrair iteradores como em um vector