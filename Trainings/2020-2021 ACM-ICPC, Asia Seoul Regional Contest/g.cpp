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

ll v[1000100];
ll d, n;

ll tentd(){

	ll ini = v[0];
	ll te = 0;
	ll td = 0;

	fr(i,n){
		ll deve = ini + i*d;
		if(deve > v[i]){
			td = max(td, deve - v[i]);
		}
		else if(deve < v[i]){
			te = max(te, v[i] - deve);
		}
	}
	return td + te;
}

ll tente(){
	ll ini = v[0];
	ll te = 0;
	ll td = 0;

	fr(i,n){
		ll deve = ini - i*d;
		if(deve > v[i]){
			td = max(td, deve - v[i]);
		}
		else if(deve < v[i]){
			te = max(te, v[i] - deve);
		}
	}
	return td + te;

}

void print(ll x){
	cout << x/2;

	if(x&1) cout << ".5" << endl;
	else cout << ".0" << endl;
}

int main(){

	fastio;

	cin >> n >> d;

	fr(i,n){
		cin >> v[i];
	}

	ll a = tentd();

	a = min(a, tente());

	print(a);
}
