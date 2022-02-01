#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
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
const int MAXN = 3e2 + 10;

int n, m, nvar;
ll b[MAXN], svar[MAXN], val[MAXN];
vi aparece[MAXN], esta[MAXN];

map<string, int> name;
string rname[MAXN];

ll sis[MAXN][MAXN];

bool calc[MAXN];

void solve(){
	queue<int> prox; // sistemas com uma variavel

	for (int i = 0; i < n + m; i++)
		if (svar[i] == 1)
			prox.push(i);

	int nsis;	
	while (!prox.empty()){ // O(n + m)
		nsis = prox.front();
		prox.pop();

		int idvar = 0;
		for (int i = 1; i < nvar; i++) // O((n + m)
			if (sis[i][nsis] != 0){
				if (idvar == 0)
					idvar = i;
			}

		if (idvar == 0 or sis[idvar][nsis] == 0)
			continue;	
			
		if (calc[idvar]) // já calculei
			continue;	
		
		calc[idvar] = 1;

		val[idvar] = b[nsis] / sis[idvar][nsis]; // valor

		for (auto ids : aparece[idvar]){
				b[ids] -= sis[idvar][ids] * val[idvar];
				sis[idvar][ids] = 0;
				svar[ids]--;

				if (svar[ids] == 1)
					prox.push(ids);
			}
	}	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m;

	nvar = 1;

	int aux;
	string s;

	fr(i, n){
		fr(j, m){
			cin>>s;
			if (!name.count(s)){
				name[s] = nvar;
				rname[nvar++] = s;
			}

			//cout<<name[s]<<' ';
			aux = name[s];

			if (sis[aux][i] == 0){	// não tava no sistema ainda
				svar[i]++;
				aparece[aux].pb(i); // aparece no sistema i
			}	
	
			if (sis[aux][n + j] == 0){
				svar[n + j]++;
				aparece[aux].pb(n + j);// e no j + n;
			}

			sis[aux][i]++; 
			sis[aux][n + j]++;
		}

		cin>>b[i];
	}

	fr(j, m)
		cin>>b[n + j];

	solve();

	vector<pair<string, int>> ans;
	for (int i = 1; i < nvar; i++)
		ans.pb({rname[i], val[i]});
	sort(all(ans));

	for (auto l : ans)
			cout<<l.fst<<' '<<l.snd<<endl;
}