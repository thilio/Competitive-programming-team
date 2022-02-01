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

const int MAXN = 5000100; 
int en[2];

int n, m;
int a, b;

int no[2][5];

struct trie{
	int cnt, wrd;
	map<char, int> m;
	trie(){
		cnt = 0; wrd = 0;
		m.clear();
	}
	
};

vector<trie> t[2];

int new_node(int u){
	t[u][en[u]].cnt = t[u][en[u]].wrd = 0;
	t[u][en[u]].m.clear();
	return en[u]++;
}

void init(){
	en[0] = 0;
	en[1] = 0;
	new_node(0);
	new_node(1);
}

void add(int node, string &s,int i, int u){ // add string to trie
	t[u][node].cnt++;
	if(i == s.size()){
		t[u][node].wrd++;
		return;
	}
	if(!t[u][node].m.count(s[i])){
		t[u][node].m[s[i]] = new_node(u);
	}
	add(t[u][node].m[s[i]], s, i + 1, u);
}

int solve(int i, int j){
	if(j == m){
		i++;
		j = 0;
	}
	if(i == n){
		return 1;
	}

	int nodea = no[0][i];
	int nodeb = no[1][j];


	int ans = 0;

	for(auto x: t[0][nodea].m){
		if(t[1][nodeb].m.count(x.fst)){
			//cout << i << ' ' << j << ' ' << x.fst << endl;
			no[0][i] = x.snd;
			no[1][j] = t[1][nodeb].m[x.fst];
			ans += solve(i, j + 1);
		}
		no[0][i] = nodea;
		no[1][j] = nodeb;
	}
	return ans;
}

int main(){

	fastio;

	cin >> n >> a;
	cin >> m >> b;

	t[0].resize(b*m + 5);
	t[1].resize(a*n + 5);
	string s;

	init();

	fr(i, a){
		cin >> s;
		add(0, s, 0, 1);
	}
	fr(i, b){
		cin >> s;
		add(0, s, 0, 0);
	}

	cout << solve(0 , 0) << endl;




}
