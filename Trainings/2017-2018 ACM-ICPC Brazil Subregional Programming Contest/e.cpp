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

int v[13];
int mov[7] = {2,2,1,2,2,2,1};
int n;

int nota(int x){
	x--;
	x%=12;
	return x+1;
}

bool foi(int p){
	int k = 0;
	fr(i,7){
		k += v[p];
		p += mov[i];
		p = nota(p);
	}
	return k==n;
}

void print(int i){
	if(i == 1) cout << "do" << endl;
	if(i == 2) cout << "do#" << endl;
	if(i == 3) cout << "re" << endl;
	if(i == 4) cout << "re#" << endl;
	if(i == 5) cout << "mi" << endl;
	if(i == 6) cout << "fa" << endl;
	if(i == 7) cout << "fa#" << endl;
	if(i == 8) cout << "sol" << endl;
	if(i == 9) cout << "sol#" << endl;
	if(i == 10) cout << "la" << endl;
	if(i == 11) cout << "la#" << endl;
	if(i == 12) cout << "si" << endl;
}

int main(){

	fastio;
	cin >> n;

	fr(i,n){
		int x;
		cin >> x;
		v[nota(x)]++; 
	}

	bool a = false;

	frr(i,12){
		if(foi(i)){
			a = true;
			print(i);
			break;
		}
	}

	if(!a){
		cout << "desafinado\n";
	}



}
