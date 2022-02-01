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
typedef tuple<int, int, int> tup;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;


map<tup, int> m3;
map<pii, int> m2;

int k;
int en3 = 0;
int en2 = 0;

set<int> adj3[100100];
set<int> adj2[100100];

int vis3[100100];
int vis2[100100];
int cycle2, cycle3;

int vtx(tup a){
	if(!m3.count(a)) m3[a] = ++en3;	
	return m3[a];
}

int vtx(pii a){
	if(!m2.count(a)) m2[a] = ++en2;	
	return m2[a];
}

pii read_tuple(){
	int x, y, z;
	cin >> x >> y >> z;
	tup a = make_tuple(x, y, z);
	pii b = make_pair(x, y);
	return {vtx(a), vtx(b)};
}

void dfs3(int v, int p){
	vis3[v] = 1;
	for(auto x: adj3[v]){
		if(vis3[x] == 0) dfs3(x, v);
		else if(vis3[x] == 1 && x != p){
			cycle3 = 1;		
		}
	} 
}

void dfs2(int v, int p){
	vis2[v] = 1;
	for(auto x: adj2[v]){
		//if(x == v) continue;
		if(vis2[x] == 0) dfs2(x, v);
		else if(vis2[x] == 1 && x != p) cycle2 = 1;
	}	
}


int main(){

	fastio;

	cin >> k;

	fr(i, k){
		pii v = read_tuple();
		pii u = read_tuple();

		if(u.fst != v.fst) adj3[v.fst].insert(u.fst);
		if(u.fst != v.fst) adj3[u.fst].insert(v.fst);
		if(u.snd != v.snd) adj2[v.snd].insert(u.snd);
		if(u.snd != v.snd) adj2[u.snd].insert(v.snd);
	}


	frr(i, en3){
		if(vis3[i] == 0){
			dfs3(i, 0);
		}
	}

	if(cycle3){
		cout << "True closed chains" << endl;
	}
	else{
		cout << "No true closed chains" << endl;
	}	

	frr(i, en2){
		if(vis2[i] == 0){
			dfs2(i, 0);
		}
	}

	if(cycle2){
		cout << "Floor closed chains" << endl;
	}
	else{
		cout << "No floor closed chains" << endl;
	}
}
