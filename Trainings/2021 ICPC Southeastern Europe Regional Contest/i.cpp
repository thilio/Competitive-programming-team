#include "bits/stdc++.h"
using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define endl '\n'
#define gnl cout<<endl
#define dbg(x) cout<<#x<< " = "<<x<<endl
#define olar cout<<"olar"<<endl
#define all(x) x.begin(),x.end()
#define pb push_back


typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;


#define INF 0x3f3f3f3f
const int MAXN = 1e5 + 3000;
const int MAXM = 9e5;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

int dfs(int u, int f, int t){
	if (u == t) return f;
	for (int &e = work[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0){
			int df = dfs(v, min(f, cap[e]), t);
			if (df > 0){
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	int st = 0, en = 0;
	q[en++] = s;
	while (en > st){
		int u = q[st++];
		for (int e = first[u]; e != -1; e = nxt[e]){
			int v = to[e];
			if (dist[v] < 0 && cap[e] > 0){
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t){
	int flow = 0, f;
	while (bfs(s, t)){
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, t)) 
			flow += f;
	}
	return flow;
}

int mx[4] = {-1, 1, 0, 0};
int my[4] = {0, 0, -1, 1};

int n, m, id[MAXN], sz[MAXN], vcmp[MAXN];

int find(int a){
    if (a == id[a])
        return a;
    return id[a] = find(id[a]);
}

void merge(int a, int b){
    a = find(a);
    b = find(b);
    
    if (a == b)
        return;

    if (sz[a] < sz[b])
        swap(a, b);
    id[b] = a;
    sz[a] += sz[b];
}

inline int crd(int x, int y){
    return x * m + y;
}

bool valid(int x, int y){
    return (0 <= x and x < n) and (0 <= y and y < m);
}

set<int> adj[MAXN];

vector<string> mapa;

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n>>m;

    for (int i = 0; i < n; i++) // init DSU
        for (int j = 0; j < m; j++){
            id[crd(i, j)] = crd(i, j);
            sz[crd(i, j)] = 1;
        }

    mapa.resize(n);
    fr(i, n)
        cin>>mapa[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 4; k++){
                int x = i + mx[k];
                int y = j + my[k];

                if (valid(x, y) and (mapa[x][y] == mapa[i][j])){
                    merge(crd(x, y), crd(i, j));
                }
                    
            }

    int ans = 0;
    fr(i, n){
        string s;
        cin>>s;
        fr(j, m)
            if (mapa[i][j] != s[j]) // I gain this cell if I flip
                vcmp[find(crd(i, j))]++; // on the component
            else{ // I lose this cell if I flip
                ans++; // In the answer now
                vcmp[find(crd(i, j))]--;
            }    
    } 

    init();
    int src = n * m;
    int snk = n * m + 1;
    int tot = 0;


    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (find(crd(i, j)) == crd(i, j)){ // I represent this cmp
                
                tot += max(0, vcmp[find(crd(i, j))]); // Number of 'Real' nodes

                if (mapa[i][j] == '0')  
                    add(src, crd(i, j), max(0, vcmp[find(crd(i, j))]));
                else        
                    add(crd(i, j), snk, max(0, vcmp[find(crd(i, j))]));
            } 

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mapa[i][j] == '0')
                for (int k = 0; k < 4; k++){
                    int x = i + mx[k];
                    int y = j + my[k];

                    if (valid(x, y) and mapa[x][y] != mapa[i][j])
                        if (!adj[find(crd(i, j))].count( find(crd(x, y)) )){
                            add(find(crd(i, j)), find(crd(x, y)), INF);
                            adj[ find(crd(i, j)) ].insert( find(crd(x, y)) );
                        }
                }

    ans += tot - dinic(src, snk); // add max inde set, or, the maximum increase

    cout<<n * m - ans<<endl;
}