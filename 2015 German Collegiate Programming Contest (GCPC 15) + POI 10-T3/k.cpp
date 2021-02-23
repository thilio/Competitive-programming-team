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

bool is(ll p){
	if(p <= 1) return false;

	for(ll i = 2; i*i <= p; i++){
		if(p == (p/i)*i) return false;
	}
	return true;
}

ll inv(ll n){
	ll k = 0;
	while(n != 0){
		k *= 10;
		ll last = n%10;
		n /= 10;
		if(last == 3 || last == 4 || last == 7) return -1;
		else if(last == 6) last = 9;
		else if(last == 9) last = 6;
		k += last;
		//dbg(last);
	}
	return k;
}

int main(){

	fastio;


	ll n;
	cin >> n;

	ll k = inv(n);

//	dbg(k);

	if(is(n) && is(k)){
		cout << "yes" << endl;
	}
	else{
		cout << "no" << endl;
	}

}
