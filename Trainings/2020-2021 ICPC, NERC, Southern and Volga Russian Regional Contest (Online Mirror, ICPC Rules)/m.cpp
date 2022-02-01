#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

map<int, int> comp;
vi compr;
vi v[200200];
int n;
int total;
int tot;
vii dupla[200200];

int freq[200200];

void reset(){
	comp.clear();
	compr.clear();
	frr(i,n) v[i].clear();
	total = 0;
}
void read(){
	frr(i,n){
		int sz;
		cin >> sz;
		fr(j,sz){
			int x;
			cin >> x;
			v[i].pb(x);
			compr.pb(x);
		}
		sort(all(v[i]));
		total += sz;
	}

	sort(all(compr));
	tot = 1;
	for(auto x: compr){
		if(!comp.count(x)) comp[x] = tot++;
	}

	frr(i,tot) dupla[i].clear();
	frr(i,tot) freq[i] = 0;

	frr(i,n){
		fr(j, v[i].size()) v[i][j] = comp[v[i][j]]; 
	}
}

int tent_g(int i){
	for(auto x: v[i]) freq[x] = 1;
	int resp = -1;
	for(int j = 1; j <= n; j++){
		if(j == i) continue;
		int ct = 0;
		for(auto x: v[j]) if(freq[x]) ct++;
		if(ct > 1) resp = j;
	}
	for(auto x: v[i]) freq[x] = 0;
	return resp;
}

bool tont(int i){
	for(auto x: dupla[i]){
		if(freq[x.fst] != 0){
			cout << freq[x.fst] << ' ' << x.snd << endl;
			return true;
		}
		else{
			freq[x.fst] = x.snd;
		}
	}

	for(auto x: dupla[i]) freq[x.fst] = 0;
	return false;
}

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		cin >> n;
		reset();
		read();
		int ans = -1;

		int sq_tot = sqrt(total);

		
		frr(i,n){
			if(v[i].size() >= sq_tot){
				if(tent_g(i) != -1){
					ans = i;
				}
			}
		}

		if(ans != -1){
			cout << ans << ' ' << tent_g(ans) << endl;
			continue;
		}

		frr(i,n){
			if(v[i].size() < sq_tot){
				fr(j,v[i].size()){
					for(int k = j + 1; k < v[i].size();k++){
						dupla[v[i][j]].pb(mp(v[i][k],i));
					}
				}
			}
		}

		bool find = false;

		frr(i,tot){
			if(tont(i)){
				find = true;
				break;
			}
		}

		if(!find) cout << -1 << endl;


		

	}


}
