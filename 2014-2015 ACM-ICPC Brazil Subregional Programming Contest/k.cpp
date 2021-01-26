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

int v[100100];
int c,n;

bool tenta(int i){
	int passo = c/n;

	for(int j = 2; j <= n; j++){
		if(!(i + (j-2)*passo < v[j] && v[j] <= i + (j-1)*passo)) return false;
	}

	return true;
}

int main(){

	fastio;
	cin >> c >> n;

	frr(i,n) cin >> v[i];

	for(int i = v[1]; i < v[1] + c/n; i++){
		if(tenta(i)){
			cout <<  "S" << endl;
			return 0;
		}
	}

	cout << "N" << endl;



}
