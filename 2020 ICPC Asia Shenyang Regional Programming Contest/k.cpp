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

vector<int> pos, neg;

int main(){

	fastio;

	int n;
	cin >> n;

	fr(i, n){
		char c; int x;
		cin >> c >> x;
		if(c == '+') pos.pb(x);
		else neg.pb(x);
	}

	sort(all(pos)); sort(all(neg));

	ll total = 0;
	ll pp = pos.size() - 1;
	ll pn = neg.size() - 1;

	while(pn >= 0){
		if(pp == pos.size()) pp--;
		while(pp >= 0 && pos[pp] > neg[pn]) pp--;
		pp++;

		total += pos.size() - pp;
		pn--;
	}

	long double T = total;
	long double P = pos.size();
	long double N = neg.size();

	cout << setprecision(15) << T/(P*N) << endl;

}
