#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int del[MAXN], add[MAXN], ans[MAXN];
vi adj[MAXN];
deque<int> s;

void dfs(int v){
	if (v != 0){
		if (del[v] == 0)
			s.push_back(add[v]); // coloquei
		else{
			ans[del[v]] = s[0]; // retrei primeiro elemento
			s.pop_front();
		}
	}

	for (int x : adj[v])
		dfs(x);

	if (v != 0){
		if (del[v] == 0)
			s.pop_back(); //removi
		else{
			s.push_front(ans[del[v]]); // devolvi primeiro elemento
		}
	}
}



int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, v, x;

	cin>>n;

	string t;
	int q = 1; // # de deleções + 1

	frr(i, n){
		cin>>t>>v;
		adj[v].pb(i);	

		if (t == "D")
			del[i] = q++;
		else
			cin>>add[i];
	}

	dfs(0);

	for (int i = 1; i < q; i++)
		cout<<ans[i]<<endl;
}