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

int n;
map<string, int> m;
int vtx = 1;

vi adj[100100];
bool vis[100100];

vi special;

string program = "::PROGRAM";

bool is(string &s){
	if(s.size() < 9) return false;

	for(int j = 0; j < 9; j++){
		if(s[s.size() - 9 + j] != program[j]) return false;
	}
	return true;
}

void dfs(int x){
	vis[x] = true;
	for(auto y: adj[x]){
		if(!vis[y]) dfs(y);
	}
}

int main(){

	fastio;

	cin >> n;
	string s;
	for(int i = 0; i < n; i++){
		cin >> s; 
		if(!m.count(s)){
			m[s] = vtx++;
		}

		if(is(s)) special.pb(m[s]);

		int eu = m[s];

		int k;
		cin >> k;
		fr(i,k){
			cin >> s;
			if(!m.count(s)){
				m[s] = vtx++;
			}
			adj[m[s]].pb(eu);
		}
	}

	for(auto x: special){
		if(!vis[x]) dfs(x);
	}

	int ans = 0;

	frr(i,n){
		if(!vis[i]) ans++;
	}

	cout << ans << endl;
}
