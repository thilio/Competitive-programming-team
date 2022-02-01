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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e6 + 10;

int en = 1, pa[MAXN], fim[MAXN];
struct no{
	char c;
	int mrk, cnt, tab;
	map<char, int> m;
	no(){mrk = cnt = tab = 0; m.clear();}
} t[MAXN];

inline int new_node(int p, char c){
	t[en].m.clear();
	t[en].mrk = t[en].cnt = 0;
	pa[en] = p;
	t[en].c = c;
	return en++;
}

inline void init(){t[0] = no(); en = 1;}

void add(int v, int pos, int id, string &s){
	int u = v;
	while (pos < s.size()){
		if (!t[u].m.count(s[pos])){// cria novo nó
			int aux = new_node(u, s[pos]);
			t[u].m[s[pos]] = aux;
			t[aux].tab = id;
		}
		u = t[u].m[s[pos]];
		t[u].cnt++;
		pos++;
	}
	t[u].mrk = 1;
	fim[id] = u; // palavra id acaba aqui
}

int dist[MAXN];

void dijkstra(){
	memset(dist, -1, sizeof dist);
	priority_queue<pii, vii, greater<pii> > pq;

	pq.push({0, 0}); // saindo da raiz gastando zero

	int dst, vtx;
	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[vtx] == -1){
			dist[vtx] = dst;
		
			for (auto it : t[vtx].m){
				if (dist[it.snd] == -1)
					pq.push({dst + 1, it.snd});
			}
		
			if (vtx != 0){ // estou em alguma palavra?
				if (dist[pa[vtx]] == -1)
					pq.push({dst + 1, pa[vtx]});
				if (dist[ fim[ t[vtx].tab ] ] == -1)
					pq.push({dst + 1, fim[t[vtx].tab]});
			}
		}
	}
}

int ans, sz;

void dfs(int v, int p, string &s){
	ans = min(ans, dist[v] + sz - p); // melhor forma de vir até aqui e digitar o resto

	if (t[v].m.count(s[p]) and p < sz)
		dfs(t[v].m[s[p]], p + 1, s);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m;

	cin>>n>>m;

	init(); // inicia a trie

	string s;

	fr(i, n){
		cin>>s;
		add(0, 0, i, s); // coloca a string i partindo da raiz
	}

	dijkstra();

	while (m--){
		cin>>s;
		ans = s.size();
		sz = s.size();

		dfs(0, 0, s);

		cout<<ans<<endl;
	}
}