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

int n,p;
int grid[2][600][600];

int soma(int q,int i,int j,int k){

	ll ans = 0;
	ans += grid[q][i+k][j+k];
	ans -= grid[q][i-1][j+k];
	ans -= grid[q][i+k][j-1];
	ans += grid[q][i-1][j-1];

	return ans;
}

int main(){

	fastio;
	cin >> n >> p;

	fr(i,p){
		int a,b;
		cin >> a >> b;
		grid[0][a][b]++;
	}

	fr(i,p){
		int a,b;
		cin >> a >> b;
		grid[1][a][b]++;
	}

	frr(i,n){
		frr(j,n){
			grid[0][i][j] += grid[0][i-1][j] + grid[0][i][j-1] - grid[0][i-1][j-1];
			grid[1][i][j] += grid[1][i-1][j] + grid[1][i][j-1] - grid[1][i-1][j-1];
		}
	}

	int p0,p1;
	p0 = p1 = 0;

	frr(i,n){
		frr(j,n){
			fr(k,n){
				if(i + k > n ||j + k > n) continue;

				int t0 = soma(0,i,j,k);
				int t1 = soma(1,i,j,k);

				if(t0 > 0 && t1 == 0) p0++;
				if(t1 > 0 && t0 == 0) p1++;

				if(t1 > 0 && t0 > 0) break;

			}
		}
	}

	cout << p0 << ' ' << p1 << endl;





}
