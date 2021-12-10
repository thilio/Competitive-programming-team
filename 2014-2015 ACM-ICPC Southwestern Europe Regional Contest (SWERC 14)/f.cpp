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
#define int long long int

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const int llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n;
int area[100100];

int id[100100];
int sz[100100];

int ans[100100];

map<int, vector<array<int, 3>>> xbegin, xend;
map<int, vector<array<int, 3>>> ybegin, yend;

void init(int n){
	fr(i, n){
		id[i] = i;
		sz[i] = 1;
	}
}

int find(int x){
	if(x == id[x]) return x;
	else return id[x] = find(id[x]);
}

void merge(int u, int v){
	u = find(u);
	v = find(v);
	if(u == v) return;
	if(sz[u] < sz[v]) swap(u, v);
	id[v] = u;
	sz[u] += sz[v];
}


signed main(){

	fastio;

	cin >> n;

	init(n);

	for(int i = 0; i < n; i++){
		int x, y, w, h;
		cin >> x >> y >> w >> h;

		xbegin[x].pb({y, y + h, i});
		xend[x + w].pb({y, y + h, i});

		ybegin[y].pb({x, x + w, i});
		yend[y + h].pb({x, x + w, i});

		area[i] = w*h;
	}


	for(auto x: xbegin){
		if(!xend.count(x.fst)) continue;

		vector<array<int, 3>> comeco = x.snd;
		vector<array<int, 3>> final = xend[x.fst];

		sort(all(comeco));
		sort(all(final));

		int p = 0; int q = 0;

		while(p < final.size()){
			while(q < comeco.size() && comeco[q][0] <= final[p][1]){
				if(comeco[q][1] >= final[p][0]){
					merge(comeco[q][2], final[p][2]);
				}
				q++;
			}
			p++;
			if (q > 0) q--;
		}
	}


	for(auto y: ybegin){
		if(!yend.count(y.fst)) continue;

		vector<array<int, 3>> comeco = y.snd;
		vector<array<int, 3>> final = yend[y.fst];

		sort(all(comeco));
		sort(all(final));

		int p = 0; int q = 0;

		while(p < final.size()){
			while(q < comeco.size() && comeco[q][0] <= final[p][1]){
				if(comeco[q][1] >= final[p][0]){
					merge(comeco[q][2], final[p][2]);
				}
				q++;
			}
			p++;
			if (q > 0) q--;
		}
	}

	fr(i, n){
		ans[find(i)] += area[i]; 
	}

	int mx = -1;
	fr(i, n){
		mx = max(mx, ans[i]);
	}

	cout << mx << endl;




}
