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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, freq[3][MAXN];

int test(int a, int b, int c){
	int ans = 0, aux;
	for (int i = 1; i <= freq[a][n]; i++){
		aux = freq[a][i];
		aux += freq[b][i + freq[b][n]] - freq[b][i]; 
		aux += freq[c][i + freq[b][n] + freq[c][n]] - freq[c][i + freq[b][n]];
		aux += freq[a][n] - freq[a][i + freq[b][n] + freq[c][n]];
		ans = max(ans, aux);
	}

	return n - ans;	
}

int32_t main(){
	fastio;

	cin>>n;

	string s;
	cin>>s;

	frr(i, n)
		freq[s[i - 1] - 'A'][i]++;
	
	fr(j, 3)
	frr(i, n)
		freq[j][i] += freq[j][i - 1];	

	int ans = min({
		test(0, 1, 2),
		test(0, 2, 1),
		test(1, 0, 2),
		test(1, 2, 0),
		test(2, 0, 1),
		test(2, 1, 0)
	});

	cout<<ans<<endl;
}	