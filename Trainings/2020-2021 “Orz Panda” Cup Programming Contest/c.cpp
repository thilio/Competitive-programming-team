#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;
// Comandos
// find_by_order(i) -> iterador para o i-ésimo elemento (contando do zero)
// order_of_key(k) -> número de elementos estritamente menores que k
// pode-se subtrair iteradores como em um vector

int n, m;
ordered_set pos;

typedef tuple<int, int, int> tup;
set<tup> interval;

int getdist(int pa, int pb){
	int pm = (pa + pb) / 2;
	return min(pm - pa, pb - pm);
}

void insert_itv(int pa, int pb){
	if (pa + 1 == pb)
		return;
	interval.insert({-getdist(pa, pb), pa, pb});
}

int add(){
	if (interval.empty()){ // não tenho intervalo, boto nas pontas 
		if (pos.empty()){
			pos.insert(1);
			return 1;
		}

		int pa = *pos.begin();
		int pb = *pos.find_by_order(pos.size() - 1);

		if (pa - 1 < n - pb){
			pos.insert(n);
			insert_itv(pb, n);
			return n;
		}
		else{
			pos.insert(1);
			insert_itv(1, pa);
			return 1;
		}
	}
	else{
		int sz, p, q;
		tie(sz, p, q) = *interval.begin();
		sz *= -1;

		int pa = -1, da = -INF;
		if (pos.find(1) == pos.end()){
			pa = *pos.begin();
			da = pa - 1;
		}

		int pb = -1, db = -INF;
		if (pos.find(n) == pos.end()){
			pb = *pos.find_by_order(pos.size() - 1);
			db = n - pb;
		}

		if (sz > da and sz >= db){
			interval.erase({-sz, p, q});
			int pm = (p + q)/2;

			insert_itv(p, pm);
			insert_itv(pm, q);
			pos.insert(pm);
			return pm;
		}
		else{
			if (da >= db){
				pos.insert(1);
				insert_itv(1, pa);
				return 1;
			}
			else{
				pos.insert(n);
				insert_itv(pb, n);
				return n;
			}
		}
	}
}

void remove(int prm){
	int k = pos.order_of_key(prm);

	if (k == 0){
		pos.erase(prm);
		if (pos.empty()) 
			return;

		int pa = *pos.begin();
		interval.erase({-getdist(prm, pa), prm, pa});
		return;
	}
	if (k == pos.size() - 1){
		pos.erase(prm);
		if (pos.empty()) 
			return;

		int pb = *pos.find_by_order(pos.size() - 1);
		interval.erase({-getdist(pb, prm), pb, prm});
		return;
	}

	int pa = *pos.find_by_order(k - 1);
	int pb = *pos.find_by_order(k + 1);

	interval.erase({-getdist(pa, prm), pa, prm});
	interval.erase({-getdist(prm, pb), prm, pb});
	pos.erase(prm);

	insert_itv(pa, pb);
}

int enter[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	while (cin>>n){
		cin>>m;

		pos.clear();
		interval.clear();

		int op, p;
		fr(i, m){
			cin>>op;

			if (op != 1){
				cin>>p;
				remove(enter[p]);
			}
			else{
				enter[i + 1] = add();
				cout<<enter[i + 1]<<endl;
			}
		}
	}
}

