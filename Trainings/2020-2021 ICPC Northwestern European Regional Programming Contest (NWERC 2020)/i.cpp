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
const int MAXN = 4e2 + 10;

bool c[3][MAXN][MAXN]; // pares 01, 02 e 12
ll n, d[MAXN], a[3][MAXN];

int inp[MAXN], outp[MAXN], inq[MAXN], outq[MAXN];

void calc(int par, int i, int j){
	int p = 0, q = 2;
	if (par == 0)
		q = 1;
	if (par == 2)
		p = 1;

	// calcula pro p
	int pos = (i + 1) % n;
	int tme = a[p][i] + d[i];

	inp[i] = 0;
	outp[i] = a[p][i]; // dou o primeiro passo

	while (pos != i){
		inp[pos] = tme;
		outp[pos] = tme + a[p][pos];
		tme += a[p][pos] + d[pos];
		pos = (pos + 1) % n;
	}

	// calcula pro q
	pos = (j + 1) % n;
	tme = a[q][j] + d[j];

	inq[j] = 0;
	outq[j] = a[q][j]; // dou o primeiro passo

	while (pos != j){
		inq[pos] = tme;
		outq[pos] = tme + a[q][pos];
		tme += a[q][pos] + d[pos];
		pos = (pos + 1) % n;
	}

	bool ok = 1;

	fr(i, n){ // entrou no lugar que eu estava?
		if (inp[i] <= inq[i] and inq[i] < outp[i])
			ok = 0;
		if (inq[i] <= inp[i] and inp[i] < outq[i])
			ok = 0;
	}

	c[par][i][j] = ok;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;
	fr(i, n)
		cin>>d[i];

	fr(i, 3)	
		fr(j, n)
			cin>>a[i][j];

	for (int par = 0; par < 3; par++){ // 01, 02, 12
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j)
					calc(par, i, j);
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (i != j and i != k and j != k){
					if (c[0][i][j] and c[1][i][k] and c[2][j][k]){
						cout<<i + 1<<' '<<j + 1<<' '<<k + 1<<endl;
						return 0;
					}
				}	

	cout<<"impossible"<<endl;			
}