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
const int MAXN = 1e6 + 10;

int n, m;
bool sim[MAXN], nao[MAXN]; // tem que ser sim/não
int nclau = 1, sz[MAXN], quem[MAXN];
vi clau[MAXN];

queue<int> fila;

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m;
	string s;
	getline(cin, s);

	fr(i, n){
		getline(cin, s);

		if (count(all(s), '-')){ // implicação
			int p = 0;
			fr(i, s.size())
				if (s[i] == '-'){
					p = i - 1;
					break;
				}
			string t = s.substr(0, p);
			s = s.substr(p + 4);


			stringstream ss(t);
			int x;
			while (ss>>x){
				sz[nclau]++;
				clau[x].pb(nclau);
			}

			quem[nclau] = 1;

			if (s[0] == '!'){
				quem[nclau] = -1;
				s.erase(s.begin());
			}
			
			quem[nclau] *= stoi(s);
			
			nclau++;
		}
		else{ // fixação
			if (s[0] == '!'){ // negando
				s.erase(s.begin());
				nao[stoi(s)] = 1;
			}
			else
				sim[stoi(s)] = 1;	
		}
	}


	frr(i, m)
		if (sim[i])
			fila.push(i);

	int v;	
	while (!fila.empty()){
		v = fila.front();
		fila.pop();

		for (auto x : clau[v]){
			sz[x]--;

			if (sz[x] == 0){
				if (quem[x] < 0)
					nao[-quem[x]] = 1;
				else if (sim[quem[x]] == 0){
					sim[quem[x]] = 1;
					fila.push(quem[x]);
				}
			}				
		}
	}	

	bool ok = 1;
	frr(i, m)
		if (sim[i] and nao[i])
			ok = 0;
	
	if (!ok){
		cout<<"conflict"<<endl;
		exit(0);
	}
	
	frr(i, m)
		cout<<(sim[i]?'T':'F');
	gnl;

}