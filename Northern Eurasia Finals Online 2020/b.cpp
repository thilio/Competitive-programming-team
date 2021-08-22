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

const int MAXN = 5000100; 

string A, B;
vector<string> ans;
int n;

int lton[30];
int ntol[30];

int en;

struct trie{
	int cnt, wrd, sol;
	map<char, int> m;
	trie(){
		cnt = 0; wrd = 0;sol = 0;
		m.clear();
	}
	
}t[MAXN];

int new_node(){
	t[en].cnt = t[en].wrd = t[en].sol = 0;
	t[en].m.clear();
	return en++;
}

void init(){
	en = 0;
	new_node();
}

void add(int node, string &s,int i){ // add string to trie
	t[node].cnt++;
	if(i == s.size()){
		t[node].wrd++;
		return;
	}
	if(!t[node].m.count(s[i])){
		t[node].m[s[i]] = new_node();
	}
	add(t[node].m[s[i]], s, i + 1);
}

bool cond(int pos, int node, int carry){
	if(pos == 1 && node == 4 && carry == 1 && lton[3] == 7 && lton[4] == 5) return true;
	return false;
}

void backtrack(int pos, int node, int carry){

	if(pos >= max(A.size(), B.size()) && carry == 0){
		if(lton[A[A.size() - 1] - 'A'] == 0 || lton[B[B.size() - 1] - 'A'] == 0) t[node].sol--;
		t[node].sol++;
		return;
	}

	for(int i = 0; i < 10; i++){	
		//if(pos == A.size() - 1 && i == 0) continue;
		if(pos < A.size()){
			if(lton[A[pos] - 'A'] != -1) i = 10;
			else if(ntol[i] == -1){
				lton[A[pos] - 'A'] = i;
				ntol[i] = A[pos] - 'A';
			}
			else continue;
		}
		else i = 10;

		for(int j = 0; j < 10; j++){
			//if(pos == B.size() - 1 && j == 0) continue;
			if(pos < B.size()){
				if(lton[B[pos] - 'A'] != -1) j = 10;
				else if(ntol[j] == -1){
					lton[B[pos] - 'A'] = j;
					ntol[j] = B[pos] - 'A';
				}
				else continue;
			}
			else j = 10;


			

			int x = carry;
			if(pos < A.size()) x += lton[A[pos] - 'A'];
			if(pos < B.size()) x += lton[B[pos] - 'A'];
			  
			int y = x%10;

			int nxt = -1;
			if(ntol[y] != -1){	
				
				if(t[node].m.count(ntol[y] + 'A')) nxt = t[node].m[ntol[y] + 'A'];
				if(nxt != -1){
					backtrack(pos + 1, nxt, x/10);
				}  
			}
			else{
				for(auto k: t[node].m){
					if(lton[k.fst - 'A'] == -1){
						lton[k.fst - 'A'] = y;
						ntol[y] = k.fst - 'A';
						backtrack(pos + 1, k.snd, x/10);
						lton[k.fst - 'A'] = -1;
						ntol[y] = -1;						 
					}
				}
			}

			if(j != 10){
				lton[B[pos] - 'A'] = -1; ntol[j] = -1;
			}
		}
		if(i != 10){
			lton[A[pos] - 'A'] = -1; ntol[i] = -1;
		}
	}
}

void dfs(int node, string& k){
	if(t[node].sol == 1 && t[node].wrd > 0){
		string a = k;
		reverse(all(a));
		ans.pb(a);
	}

	for(auto x: t[node].m){
		k.pb(x.fst);
		dfs(x.snd, k);
		k.pop_back();
	}

}

int main(){

	fastio;

	init();
	cin >> A >> B;
	reverse(all(A));
	reverse(all(B));
	cin >> n;

	fr(i, n){
		string s;
		cin >> s;
		reverse(all(s));
		add(0, s, 0);
	}

	ms(lton, -1); ms(ntol, -1);

	backtrack(0, 0, 0);

	string k;
	dfs(0, k);

	sort(all(ans));
	cout << ans.size() << endl;
	for(auto x: ans) cout << x << endl;

}
