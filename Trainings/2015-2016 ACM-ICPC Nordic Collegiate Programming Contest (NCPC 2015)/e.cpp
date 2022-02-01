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

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, k;

	cin>>n>>k;

	int x, y;
	vii event;

	fr(i, n){
		cin>>x>>y;
		event.pb({y, x});
	}

	sort(all(event));

	set<pii> q;

	int ans = 0, cnt = 0;
	for (auto e : event){ // coloca na maquina que tem o menor gap com o começo
		cnt++;

		if (q.empty()){
			q.insert({-e.fst, -cnt});
			ans++;
		}
		else{ 
			auto it = q.lower_bound({-e.snd, -cnt});
			if (it != q.end()){
				q.erase(it);
				q.insert({-e.fst, -cnt});
				ans++;
			}
			else if (q.size() < k){
				q.insert({-e.fst, -cnt});
				ans++;
			}
		}
	}

	cout<<ans<<endl;
}