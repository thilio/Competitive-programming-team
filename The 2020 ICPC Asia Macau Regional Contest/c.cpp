#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

const int MAXN = 3003000; 
int en;

int n;
int ans[MAXN];	

struct trie{
	int cnt, wrd;
	map<int, int> m;
	vector<int> num;
	vector<int> pos;
	trie(){
		cnt = 0; wrd = 0;
		m.clear();
		num.clear();
		pos.clear();
	}
	
}t[MAXN];

int new_node(){
	t[en] = trie();
	return en++;
}

void init(){
	for(int i = 1; i <= n; i++) ans[i] = -1;
	en = 0;
	new_node();
}

void add(int node, int k, int i, int x){ // add string to trie
	t[node].cnt++;
	t[node].num.pb(k);
	t[node].pos.pb(x);
	if(i == -1){
		t[node].wrd++;
		return;
	}
	int l = k&(1 << i);
	if(l > 0) l = 1;
	if(!t[node].m.count(l)){
		t[node].m[l] = new_node();
	}
	add(t[node].m[l], k, i - 1, x);
}

ll dfs(int node){
	//dbg(node); dbg(t[node].cnt);
	if(t[node].m.empty()){
		if(t[node].cnt >= 3){
			for(auto x: t[node].pos) if(ans[x] == -1) ans[x] = 1;
				return 0;
		}
		else{
			fr(i, t[node].pos.size()) if (ans[t[node].pos[i]] == -1) ans[t[node].pos[i]] = i + 1;
		}
		return llINF;
	}

	if(t[node].cnt <= 2){
		fr(i, t[node].pos.size()) if (ans[t[node].pos[i]] == -1) ans[t[node].pos[i]] = i + 1;
		return llINF;
	}
	//t[node].cnt > 2;

	if(!t[node].m.count(0) || !t[node].m.count(1)){ // one child
		fr(i, 2){
			if(t[node].m.count(i)) return dfs(t[node].m[i]);
		}
	}



	int l = t[node].m[0];
	int r = t[node].m[1];

	if(t[l].cnt > 2 || t[r].cnt > 2){ // one big child
		return min(dfs(l), dfs(r));
	}

	//t[node].cnt < 5

	if(t[r].cnt == 1 && t[l].cnt == 2) swap(l, r);

	if(t[l].cnt == 1 && t[r].cnt == 2){
		ans[t[r].pos[0]] = 1;
		ans[t[r].pos[1]] = 2;
		if((t[l].num[0]^t[r].num[0]) > (t[l].num[0]^t[r].num[1])) ans[t[l].pos[0]] = 1;
		else ans[t[l].pos[0]] = 2;
		return max((t[l].num[0]^t[r].num[0]),(t[l].num[0]^t[r].num[1]));
	}

	ans[t[r].pos[0]] = 1;
	ans[t[r].pos[1]] = 2;

	int op1 = min(t[l].num[0]^t[r].num[0], t[l].num[1]^t[r].num[1]);
	int op2 = min(t[l].num[1]^t[r].num[0], t[l].num[0]^t[r].num[1]);

	if(op1 > op2){
		ans[t[l].pos[0]] = 1;
		ans[t[l].pos[1]] = 2;
	}
	else{
		ans[t[l].pos[0]] = 2;
		ans[t[l].pos[1]] = 1;
	}

	return max(op1, op2);
}

int main(){


	fastio;
	int tt;
	cin >> tt;
	while(tt--){
		cin >> n;
		init();
		fr(i, n){
			int w;
			cin >> w;
			add(0, w, 29, i + 1);
		}

		cout << dfs(0) << endl;
		frr(i, n) cout << ans[i];
		gnl;
	}

}
