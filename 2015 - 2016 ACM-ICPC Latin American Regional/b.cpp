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
const int MAXN = 1e2 + 10;

vi adju[MAXN];
int matchu[MAXN], matchv[MAXN], vis[MAXN];
int iter, m;

bool dfs(int u){
    vis[u] = iter;
    if (u == 0) 
    	return true;
   	for (int &v : adju[u]){
		if (vis[matchv[v]] < iter and dfs(matchv[v])){
			matchv[v] = u; 
			matchu[u] = v;
			return true;
        }
    }
    return false;
}

int kuhn(){
	memset(matchv, 0, sizeof matchv);
	memset(matchu, 0, sizeof matchu);
	memset(vis, 0, sizeof vis);
	iter = 0;
	int res = 0;
	for (int u = 1; u <= m; u++){
		iter++;
		if (matchu[u] == 0 and dfs(u))
			res++;
	}

	return res;
}



int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, q;
	cin>>n>>q;

	vi blood[MAXN];

	int b, x;
  	frr(i, n){
		cin>>b;
		fr(j, b){
			cin>>x;
			blood[i].pb(x);
		}
	}

	m = n; // semre o tamanho do lado esquerdo

	int now[MAXN];

	while (q--){
		frr(i, n)
			adju[i].clear();

		fr(i, n + 1)
			now[i] = 0;

		cin>>b;
		fr(j, b){
			cin>>x;
			now[x] = 1; // tem o tipo x
		}

		bool bad = 0;

		frr(v, n){
			for (auto y : blood[v])
				if (now[y]) // tem esse tipo
					adju[v].pb(y);

			if (adju[v].empty() and blood[v].size() == n){
				// não ajuda nesse filho e não tem neutro
				bad = 1;
			}	
		}

		int aux = kuhn();

		if (aux != b or bad){
			cout<<"N"<<endl;
		}
		else{
			cout<<"Y"<<endl;
		}
	}
}