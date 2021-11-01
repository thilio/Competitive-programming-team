#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

int n, m;
int ub[100100];

vi ev[100100];
int val[100100];

int main(){

	fastio;

	cin >> n >> m;
	frr(i, m) ub[i] = 1e9;

	frr(i, n){
		int p, q;
		cin >> p >> q;
		val[i] = q;
		fr(j, p){
			int x;
			cin >> x;
			ub[x] = min(ub[x], q);
			ev[i].pb(x);
		}
	}

	bool deu = true;

	frr(i, n){
		int ans = 0;
		for(auto x: ev[i]) ans = max(ans, ub[x]);
		if(ans < val[i]) deu = false;
	}

	if(deu){
		cout << "Good memory" << endl;
		frr(i, m) cout << ub[i] << ' ';
		gnl;
 	}
 	else{
 		cout << "Poor memory" << endl;
 	}





}
