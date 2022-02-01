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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, m, c[MAXN];
vi lista[MAXN];

int p[MAXN], match[MAXN];
map<pii, int> pref;

priority_queue<pii, vii, greater<pii>> pq[MAXN];

void stable(){
	memset(match, -1, sizeof match);
	int hubby = -1, wom = 0;
	for (int i = 0; i < n; i++)
		for (int man = i; man >= 0; ){
			bool ok = 0;
			while (p[man] < lista[man].size()){
				wom = lista[man][p[man]++];
				if (c[wom] > pq[wom].size() or pref[{wom, man}] > pq[wom].top().fst){
					ok = 1;
					break;
				}
			}
			if (ok){
				hubby = -1;
				if (!pq[wom].empty() and c[wom] == pq[wom].size()){
					hubby = pq[wom].top().snd;
					pq[wom].pop();
				}
				match[man] = wom;
				pq[wom].push({pref[{wom, man}], man});
				man = hubby;
			}
			else{
				match[man] = -1;
				man = -1;
			}
		}
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m;
	fr(i, m)
		cin>>c[i];

	string s;
	getline(cin, s);	

	fr(i, n){
		getline(cin, s);
		stringstream ss(s);

		int x;
		while (ss>>x){
			x--;
			lista[i].pb(x);
		}
	}	


	fr(i, m){
		getline(cin, s);
		stringstream ss(s);

		int x, cnt = n;
		while (ss>>x){
			x--;
			if (x >= 0){
				pref[{i, x}] = cnt;
				cnt--;
			}
		}
	}

	stable();

	fr(i, n)
		if (match[i] != -1)
			cout<<i + 1<<endl;
}