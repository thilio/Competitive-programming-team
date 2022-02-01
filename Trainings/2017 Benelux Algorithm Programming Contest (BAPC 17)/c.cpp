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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 5e5 + 10;

set<ll> ans, at, lst;

int32_t main(){
	fastio;

	ll n, val, aux;
	
	cin>>n;

	for (int i = 0; i < n; i++){
		cin>>val;
		
		at.insert(val);
		ans.insert(val);
		while (!lst.empty()){
			aux = *lst.begin();
			lst.erase(lst.begin());
			at.insert(__gcd(val, aux));
			ans.insert(__gcd(val, aux));
		}
		lst = at;
		at.clear();
	}	

	cout<<ans.size()<<endl;
}