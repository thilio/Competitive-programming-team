#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int work[10100][101], mill[101];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m, x, y;

	cin>>n>>m>>x>>y;

	fr(i, n)
		fr(j, x)
			cin>>work[i][j];

	fr(i, 101)
		mill[i] = y;		


	int k;	
	fr(i, m){
		fr(j, x){
			cin>>k;
			mill[j] = min(mill[j], y - k);
		}
	}	

	fr(i, n){
		fr(j, x)
			cout<<min(mill[j], work[i][j])<<' ';
		gnl;	
	}	

}