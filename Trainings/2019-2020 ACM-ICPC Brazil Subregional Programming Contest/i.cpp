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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 4e2 + 10;

typedef tuple<int, int, int> tup;

int n, m, dist[MAXN][MAXN][MAXN];
int ans[112345], check[MAXN];
vi frio, quente, srt_tmp;
vii temp;
vector<tup> query;
set<int> dif_tmp;

int32_t main(){
	//ios_base::sync_with_stdio(false); cin.tie(NULL);

	scanf("%d %d", &n, &m);
	//cin>>n>>m;

	int tmp;
	frr(i, n){
		scanf("%d", &tmp);
		//cin>>tmp;
		temp.pb({tmp, i});
		dif_tmp.insert(tmp);
	}

	while (!dif_tmp.empty()){
		srt_tmp.pb(*dif_tmp.begin());
		dif_tmp.erase(dif_tmp.begin());
	}
	
	sort(all(temp));

	memset(dist, INF, sizeof dist);
	frr(i, n)
		dist[i][i][0] = 0;

	int x, y, w;
	fr(i, m){
		scanf("%d %d %d", &x, &y, &w);
		//cin>>x>>y>>w;
		dist[x][y][0] = dist[y][x][0] = w; 
	}

	int q;
	cin>>q;
	fr(i, q){
		scanf("%d %d %d %d", &x, &y, &w, &tmp);
		//cin>>x>>y>>w>>tmp;
		if (tmp == 0)//frio
			frio.pb(i);
		else
			quente.pb(i);
		query.pb({x, y, w});
	}

	// frio primeiro
	int p = 0, aux;
	for (int k = 1; k <= srt_tmp.size(); k++)
		while (p < n and temp[p].fst <= srt_tmp[k - 1]){ // ta entre os k mais frios
			check[k] = p + 1;
			for (int v = 1; v <= n; v++)
				for (int u = 1; u <= n; u++){
					aux = temp[p].snd;
					dist[v][u][p + 1] = min(dist[v][u][p], dist[v][aux][p] + dist[aux][u][p]);
				}
			p++;
		}

	for (int i : frio){
		tie(x, y, w) = query[i];
		ans[i] = dist[x][y][check[w]];		
	}

	// agora quente
	reverse(all(temp));
	reverse(all(srt_tmp));
	p = 0;
	for (int k = 1; k <= srt_tmp.size(); k++)
		while (p < n and temp[p].fst >= srt_tmp[k - 1]){ // ta entre os k mais frios
			check[k] = p + 1;
			for (int v = 1; v <= n; v++)
				for (int u = 1; u <= n; u++){
					aux = temp[p].snd;
					dist[v][u][p + 1] = min(dist[v][u][p], dist[v][aux][p] + dist[aux][u][p]);
				}
			p++;
		}

	for (int i : quente){
		tie(x, y, w) = query[i];
		ans[i] = dist[x][y][check[w]];		
	}

	fr(i, q)
		printf("%d\n", ans[i] == INF? -1 : ans[i] );
		//cout<<(ans[i] == INF? -1 : ans[i])<<endl;
}