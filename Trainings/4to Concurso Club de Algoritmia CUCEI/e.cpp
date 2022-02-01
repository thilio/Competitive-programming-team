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

struct point{
	ll x,y,z;
};

struct cubo{
	int xi,yi,zi;
	int xf,yf,zf;
	ll t;
};

bool intersec_clo(cubo a,cubo b){
	if(a.xi >= b.xf || b.xi >= a.xf) return false;
	if(a.yi >= b.yf || b.yi >= a.yf) return false;
	if(a.zi >= b.zf || b.zi >= a.zf) return false;

	return true;
}

bool intersec_op(cubo a,cubo b){
	if(a.xi > b.xf || b.xi > a.xf) return false;
	if(a.yi > b.yf || b.yi > a.yf) return false;
	if(a.zi > b.zf || b.zi > a.zf) return false;

	return true;
}

vector<cubo> figura;
int many[50];
int X,Y,Z,Q,T;

int main(){

	fastio;

	cin >> X >> Y >> Z >> Q >> T;

	frr(i,Q){
		frr(i,T) many[i] = 0;
		int op;
		cin >> op;
		if(op == 1){
			cubo at;
			cin >> at.xi >> at.yi >> at.zi;
			ll w,d,h;
			cin >> w >> d >> h;
			at.xf = at.xi + w - 1; at.yf = at.yi + d - 1; at.zf = at.zi + h - 1; 
			cin >> at.t;

			bool ok = true;
			fr(i,figura.size()){
				if(intersec_op(figura[i],at)) ok = false;
			}

			if(ok) figura.pb(at);
			if(!ok) cout << -1 << endl;
		}
		if(op == 2){
			cubo at;
			cin >> at.xi >> at.yi;
			at.zi = 1;
			cin >> at.xf >> at.yf;
			ll dz;
			cin >> dz;
			at.zf = at.zi + dz - 1;

			fr(i,figura.size()){
				if(intersec_op(figura[i],at)) many[figura[i].t]++;
			}
			//dbg(intersec_clo(figura[0],at));
			ll ans = 0;
			frr(i, T){
				if(many[i] > 0) ans++;
			}
			//olar;
			cout << ans << endl;
		}
	}

}
