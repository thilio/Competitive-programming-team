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
typedef tuple<bool, bool ,bool, bool> tb;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

map<tb, int> M;

void pre(){
	bool row0, row1, col0, col1;
	for(int mask = 0; mask < 16; mask++){
		row0 = row1 = col0 = col1 = false;
		fr(i, 4){
			if(mask&(1 << i)){
			//	if(mask == 5) dbg(i + 1);
				int num = i + 1;
				if((num - 1)/2 == 0) row0 = true;
				else row1 = true;
				if((num - 1)%2 == 0) col0 = true;
				else col1 = true;

			}
		}
		tb a = {row0, row1, col0, col1};
		tb b = {1, 1, 1, 0};
		//if (a == b) dbg(mask);
		M[a]++;
	}
}

int main(){

	fastio;

	pre();
	int T;
	cin >> T;
	while(T--){
		int m, n;
		cin >> m >> n;
		bool r0, r1, c0, c1;
		r0 = r1 = c0 = c1 = false;
		fr(i, m){
			int x;
			cin >> x;
			if(x == 0) r0 = true;
			else r1 = true;
		}
		fr(i, n){
			int x;
			cin >> x;
			if(x == 0) c0 = true;
			else c1 = true;
		}

		tb a = {r0,r1,c0,c1};
		tb b = {1, 1, 1, 0};
		//	if (a == b) olar;
		cout << M[a] << endl;
	}
}
