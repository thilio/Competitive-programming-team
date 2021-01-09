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
const int MAXN = 2e5 + 10;

map<int, int> mapa;

int freq[MAXN];
pii ans[MAXN];
vi pos[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;

	cin>>n;

	int x, cntid = 0;
	fr(i, n){
		cin>>x;
		if (!mapa.count(x))
			mapa[x] = cntid++;

		freq[mapa[x]]++;
		pos[mapa[x]].pb(i);
	}

	for (auto it : mapa){
		int id = it.snd;	
		int cnt = 0;

		ll num = it.fst;

		for (ll i = 1; i * i <= num; i++){
			if (num % i == 0){ // divisor
				if (i * i == num){
					ans[pos[id][cnt]] = {i, i};
					cnt++;
				}
				else{
					ans[pos[id][cnt]] = {i, num / i};
					cnt++;
					if (cnt < freq[id]){
						ans[pos[id][cnt]] = {num / i, i};
						cnt++;
					}	
				}
			}
			if (cnt == freq[id])
				break;	
		}

		if (cnt < freq[id]){
			cout<<"NO"<<endl;
			return 0;
		}
	}

	cout<<"YES"<<endl;
	fr(i, n)
		cout<<ans[i].fst<<' '<<ans[i].snd<<endl;

}