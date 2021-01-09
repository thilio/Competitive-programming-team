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
int nxt[200200][27];
int init[27];
int n;
string s;

void build(){
	fr(i,26) nxt[n-1][i] = -1;

	for(int j = n - 2;j >= 0;j--){
		fr(i,26) nxt[j][i] = nxt[j+1][i];
		nxt[j][s[j+1] - 'a'] = j + 1; 
	}

	fr(i,26) init[i] = nxt[0][i];
	init[s[0] - 'a'] = 0;

}

int main(){

	fastio;
	
	getline(cin,s);
	n = s.size();
	int q;
	cin >> q;

	build();

	string ans;
	string t;
	getline(cin,t);

	fr(i,q){
		t.clear();
		ans.clear();
		getline(cin,t);
		int at = -1;
		at = init[t[0] - 'a'];
		if(at == -1){
			cout <<"IMPOSSIBLE\n";
			continue;
		}

		else{
			ans.pb(t[0]);
		}
		
		for(int i = 1; i < t.size();i++){
			at = nxt[at][t[i] - 'a'];
			if(at == -1) break;
			ans.pb(t[i]);
		}

		cout << ans << '\n';
	}




}
