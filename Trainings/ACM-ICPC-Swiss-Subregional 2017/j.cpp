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

vector<array<int, 2>> v, aux;

int mx[3000100];

int main(){

	fastio;

	int n;
	cin >> n;

	fr(i, n){
		int x, y;
		cin >> x >> y;
		aux.pb({x - 1, y + 1});
		aux.pb({x + 1, y + 1});
	}
	sort(all(aux));
	for(auto x: aux){
		int sz = v.size();
		if(sz == 0)
			v.pb(x);
		else{
			if(v[sz - 1][0] == x[0])
				v[sz - 1][1] = x[1];
			else
				v.pb(x);
		}
	}
	aux.clear();

	n = v.size();

	for(int i = n - 1; i >= 0; i--){
		mx[i] = max(v[i][1], mx[i + 1]);
	}

	ll circum, area, sz;
	circum = area = sz = 0;

	ll yat = 0;

	for(int i = 0; i < n; i++){
		if(i == 0){
			circum += v[i][1] + 1;
			area += v[i][1] + 1;
			sz += v[i][1] + 1;
			yat = v[i][1];
		}
		else if(i < n){
			if(v[i][1] >= yat){

				ll dx = v[i][0] - v[i - 1][0];
				ll dy = v[i][1] - yat;
			
				circum += dx + dy;
				sz += dx + dy;
				area += (yat + 1)*(dx - 1);
				area += v[i][1] + 1;
				
				yat = v[i][1];
			}
			else if(v[i][1] < yat && mx[i] >= yat){
				ll dx = v[i][0] - v[i - 1][0];
				circum += dx;
				sz += dx;
				area += (yat + 1)*(dx);
			}
			else{
				ll dx = v[i][0] - v[i - 1][0];
				ll dy = yat - mx[i];
				circum += dy + dx;
				sz += dy + dx;
				yat = mx[i];
				area += (yat + 1)*(dx);
			}
		}
		if(i == n - 1){
			circum += v[i][1] + 2;
			sz += v[i][1];

			yat = 0;
		}
	}

	cout << circum << ' ' << sz <<' '<< area - sz << endl;


}
