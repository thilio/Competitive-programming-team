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
typedef pair<double, double> pdd;
 
const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n;
pdd M;
vector<pdd> v;

int win(){
	int ja = 0;
	vector<pair<double, int>> ev;

	for(auto x: v){
		if(x.fst <= M.fst && x.snd <= M.snd){
			ja++; continue;
		}
		if(x.fst > M.fst && x.snd > M.snd) continue;

		double inter = (x.snd - M.snd)/((M.fst - M.snd) - (x.fst - x.snd));
		if(inter < 0 || inter > 1) assert(0);

		if(x.snd > M.snd) ev.pb({inter, 0});
		else if(x.snd < M.snd){
			ev.pb({inter, 1});
			ja++;
		}
		else{
			if((M.fst - M.snd) > (x.fst - x.snd)) ev.pb({inter, 0});
			else{
				ev.pb({inter, 1});
				ja++;
			}
		}
	}

	sort(all(ev));
	int mx = ja;

	for(auto x: ev){
		if(x.snd == 1) ja--;
		else ja++;

		mx = max(ja, mx);
	}

	return n - mx;
}

int lose(){
	int ja = 0;
	vector<pair<double, int>> ev;

	for(auto x: v){
		if(x.fst >= M.fst && x.snd >= M.snd){
			ja++; continue;
		}
		if(x.fst < M.fst && x.snd < M.snd) continue;

		double inter = (x.snd - M.snd)/((M.fst - M.snd) - (x.fst - x.snd));
		if(inter < 0 || inter > 1) assert(0);

		if(x.snd > M.snd){
			ja++;
			ev.pb({inter, 1});
		}
		else if(x.snd < M.snd) ev.pb({inter, 0});
		else{
			if((M.fst - M.snd) > (x.fst - x.snd)){
				ev.pb({inter, 1});
				ja++;
			}
			else ev.pb({inter, 0});
		}
	}

	sort(all(ev));

	int mn = ja;

	for(auto x: ev){
		if(x.snd == 1) ja--;
		else ja++;

		mn = max(mn, ja);
	}

	return mn + 1;
}

int main(){

	fastio;
	cin >> n;
	cin >> M.fst >> M.snd;
	fr(i, n - 1){
		double a, b;
		cin >> a >> b;
		v.pb({a, b});
	}

	cout << win() << ' ';
	cout << lose() << endl;
}
