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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, m, blue[50], red[50], memo[50][50];

int32_t main(){
	fastio;
	cin>>n>>m;

	string s;
	frr(i, n){
		blue[i] = 0;
		red[i] = m + 1;

		cin>>s;
		fr(j, m){
			if (s[j] == 'B')
				blue[i] = j + 1;
			if (s[j] == 'R' and red[i] == m + 1)
				red[i] = j + 1;
		}
		if (blue[i] > red[i])
			memo[n + 1][0] = -1;
	}

	blue[0] = 0;
	red[0] = m + 1;

	memo[n + 1][0] += 1;

	for (int i = n; i >= 0; i--){
		for (int j = 0; j <= blue[i]; j++)
			memo[i][blue[i]] += memo[i + 1][j];
		for (int j = blue[i] + 1; j < red[i]; j++)
			memo[i][j] = memo[i][j - 1] + memo[i + 1][j];
	}

	fr(i, n + 1){
		fr(j, m + 1)
			cout<<memo[i][j]<<' ';
		gnl;	
	}

	cout<<memo[0][m]<<endl;
}