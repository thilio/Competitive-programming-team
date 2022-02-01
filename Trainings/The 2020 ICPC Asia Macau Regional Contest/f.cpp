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
const int MAXN = 1e5 + 10;

ll n, d, c;

vi adj[MAXN];

bool used[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>d>>c;

	if (d == 0){
		if (n == c){
			cout<<"Yes"<<endl;
			fr(i, n)
				gnl;
		}
		else
			cout<<"No"<<endl;
		return 0;	
	}

	if (d == 1){
		if (2 * c != n){
			cout<<"No"<<endl;
		}
		else{
			cout<<"Yes"<<endl;
			for (int i = 1; i <= n; i += 2){
				cout<<i + 1<<endl;
				cout<<i<<endl;
			}
		}
		return 0;
	}



	if (n < (d + 1) * c){ // tem que ter no minimo d + 1 caras em cada componente
		cout<<"No"<<endl;
		return 0;
	}

	ll sobra = n - ((d + 1) * c);

	if ( (sobra & 1) and (d & 1)){ // ambos impares não da
		cout<<"No"<<endl;	// vou ter componente impar com regularidade impar
		return 0;
	}


	// vamos pra primeira componente

	for (int i = 1; i <= d + 1; i++) // forma clique de d + 1
		for (int j = i + 1; j <= d + 1; j++){
			adj[i].pb(j);
			adj[j].pb(i);
		}

	queue<int> fila;	
	frr(i, d + 1)	
		fila.push(i);

	int pendente = 0, auxd;	
	stack<int> stk;
	for (int id = d + 2; id <= sobra + d + 1; id++){ // coloca as sobras
		auxd = d;

		if (pendente > 0){ // liga com o anterior
			auxd--;
			used[pendente] = 1;
			stk.push(pendente);
			fila.push(pendente);
			adj[id].pb(pendente);
			adj[pendente].pb(id);
			pendente = 0;
		}


		while (auxd > 1){
			int u = fila.front();
			fila.pop();
			fila.push(u);	
			
			if (!used[u]){
				for (int i = 0; i < d; i++)
					if (!used[adj[u][i]]){
						int y = adj[u][i];
						used[u] = used[y] = 1;

						stk.push(u);
						stk.push(y);

						adj[id].pb(u);
						adj[id].pb(y);

						adj[u][i] = id;

						fr(k, d)
							if (adj[y][k] == u)
								adj[y][k] = id;

						auxd -= 2;		
						break;
					}
			}
		}		
		if (auxd == 1)
			pendente = id;
		else
			fila.push(id);

		while (!stk.empty()){
			used[stk.top()] = 0;
			stk.pop();
		}
	}	


	for (int k = 2; k <= c; k++){
		int ini = sobra + (k - 1) * (d + 1) + 1; // o que já foi
		for (int i = ini; i <= ini + d; i++)
			for (int j = i + 1; j <= ini + d; j++){
				adj[i].pb(j);
				adj[j].pb(i);
			}
	}

	frr(i, n)
		sort(all(adj[i]));


	cout<<"Yes"<<endl;
	frr(i, n){
		for (auto x : adj[i])
			cout<<x<<' ';
		gnl;
	}

}