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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e6 + 10;

vi ans[MAXN], peca[MAXN], rpeca[MAXN]; 
vii canto;

void abort(int cnt){
	if (cnt < 5)
		return;
	cout<<"impossible"<<endl;
	exit(0);
}

void print(int h, int w){
	cout<<h<<' '<<w<<endl;
	fr(i, h){
		fr(j, w)
			cout<<ans[i][w - j - 1]<<' ';
		gnl;	
	}
	exit(0);
}

// 	 1 
// 0   2	
//   3
void rot(int a){ // anti
	int aux = peca[a][0];
	frr(i, 3)
		peca[a][i - 1] = peca[a][i];
	peca[a][3] = aux;	
}

int other(int a, int b){
	if (b == 0)
		abort(5);

	if (rpeca[b][0] == a)
		return rpeca[b][1];
	
	return rpeca[b][0];
}

int get_p(int v, int p){
	return peca[v][p];
}

// 	 1 
// 0   2	
//   3
bool check(int h, int w){
	fr(i, h){
		if (ans[i].size() != w)
			return false;
		if (get_p(ans[i][0], 0) != 0 or get_p(ans[i][w - 1], 2))
			return false;
	}
	
	fr(i, w){
		if (get_p(ans[0][i], 1) != 0 or get_p(ans[h - 1][i], 3) != 0)
			return false;
	}

	for(int i = 1; i < h; i++)
		for (int j = 0; j < w - 1; j++)
			if (get_p(ans[i][j], 1) != get_p(ans[i - 1][j], 3) or get_p(ans[i][j], 2) != get_p(ans[i][j + 1], 0))
				return false;
	return true;				
}

int32_t main(){
	fastio;

	int n, a, b, c, d;

	cin>>n;

	frr(i, n){
		cin>>a>>b>>c>>d;
		peca[i] = {a, b, c, d};
	
		int cnt = 0;
		fr(k, 4){
			if (peca[i][k] > 0)
				rpeca[peca[i][k]].pb(i);
			else
				cnt++;
		}
		if (cnt >= 2)
			canto.pb({i, cnt});			
	}
	if (canto.empty()){
		abort(5);
	}

	if (canto.size() == 1){
		if (n > 1 or canto[0].snd < 4)
			cout<<"impossible"<<endl;
		else
			cout<<1<<' '<<1<<endl<<1<<endl;
		return 0;
	}


	int v = -1, cnt, at;

	if (canto.size() == n){// só tem uma linha e uma coluna
		for (auto x : canto)
			if(x.snd == 3)
				v = x.fst;
		if (v == -1)
			abort(5);	

		cnt = 0;
		while (peca[v][2] == 0  and  cnt++ < 5)
			rot(v);

		abort(cnt);
		ans[0].pb(v);

		while (peca[v][2] != 0){
			at = v;
			v = other(v, peca[v][2]);
			ans[0].pb(v);

			cnt = 0;
			while ((peca[at][2] != peca[v][0]) and cnt++ < 5){
				rot(v);
			}
		}
		if (check(1, n))
			print(1, n);
		else
			abort(5);
	}

	v = -1;
	for (auto x : canto){
		if (x.snd == 2)
			v = x.fst;
		if (x.snd == 3)
			abort(5);
	}
	if (v == -1)
		abort(5);	

	cnt = 0;
	while ( (peca[v][3] == 0 or peca[v][2] == 0)  and  cnt++ < 5)
		rot(v);
	abort(cnt);
	ans[0].pb(v);

	while (peca[v][2] != 0){
		at = v;
		v = other(v, peca[v][2]);
		ans[0].pb(v);

		cnt = 0;
		while ((peca[at][2] != peca[v][0]) and cnt++ < 5){
			rot(v);
		}

		abort(cnt);
	}
	
	int w = ans[0].size();
	int h = n/w;

	if (w * h != n)
		abort(5);


	for (int i = 1; i < h; i++){
		v = other(ans[i - 1][0], get_p(ans[i - 1][0], 3)); // pega pra baixo
		cnt = 0;
		while (peca[v][1] != get_p(ans[i - 1][0], 3) and cnt++ < 5)
			rot(v);
		abort(cnt);

		ans[i].pb(v);

		while (peca[v][2] != 0){
			at = v;
			v = other(v, peca[v][2]);
			ans[i].pb(v);

			cnt = 0;
			while ((peca[at][2] != peca[v][0]) and cnt++ < 5){
				rot(v);
			}

			abort(cnt);
		}
	}

	if (check(h, w))
		print(h, w);
	else
		abort(5);
}
