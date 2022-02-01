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
const int MAXN = 100100; 

int n, T;
int en;

unordered_map<string, int> hashq;
int hashqu = 1;
unordered_map<string, int> hasha;
int hashan = 1;

int total[MAXN];
int mx[MAXN];
long double P[MAXN];

unordered_map<int, int> no[MAXN];

long double memo[MAXN][110];
bool vis[MAXN][110];

struct trie{
	int cnt, wrd;
	map<int, int> m;
	trie(){
		cnt = 0; wrd = 0;
		m.clear();
	}
	
}t[MAXN];

int new_node(){
	t[en].cnt = t[en].wrd = 0;
	t[en].m.clear();
	return en++;
}

void init(){
	en = 0;
	new_node();
}

void add(vi &s, int node, int i, int ans){ // add string to trie
	t[node].cnt++;
	
	no[node][ans]++;
	total[node]++;
	if(no[node][ans] > mx[node]) mx[node] = no[node][ans];

	if(i == s.size()){
		t[node].wrd = ans;
		return;
	}
	if(!t[node].m.count(s[i])){
		t[node].m[s[i]] = new_node();
	}
	add(s, t[node].m[s[i]], i + 1, ans);
}

long double pd(int node, int tt){
	if(tt == T) return 0;
	if(vis[node][tt]) return memo[node][tt];

	vis[node][tt] = true;
	long double& pdm = memo[node][tt];

	pdm = P[node] + pd(0, tt + 1);

	long double tent = 0.0;

	for(auto x: t[node].m){
		tent += ((long double)total[x.snd]/(long double)total[node])*pd(x.snd, tt + 1);
	}

	pdm = max(pdm, tent);
	return pdm;
}



int main(){

	fastio;
	cin >> T >> n;
	init();
	cout << setprecision(12) << fixed;

	string s;
	fr(i, n){
		vi q;
		cin >> s;
		while(s[s.size() - 1] != '?'){
			if(!hashq.count(s)){
				hashq[s] = hashqu++;
			}
			q.pb(hashq[s]);
			//dbg(s);
			//dbg(hashq[s]);
			cin >> s;
		}
		s.pop_back();
		if(!hashq.count(s)){
			hashq[s] = hashqu++;
		}
		//dbg(s);
		//dbg(hashq[s]);
		q.pb(hashq[s]);

		cin >> s;
		if(!hasha.count(s)){
			hasha[s] = hashan++;
		}

		add(q, 0, 0, hasha[s]);
	}

	fr(i, en){
		P[i] = (long double) mx[i]/ (long double) total[i];
	}

	//fr(i, en) dbg((P[i]));
	cout << pd(0, 0) << endl;

}
