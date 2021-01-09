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
const int MAXN = 1e3 + 10;

typedef tuple<int, int, int> tup;

int n, m, k;
vector<tup> sensor;

int sq(int x){
	return x * x;
}

int id[MAXN], sz[MAXN];

int find(int a){
	if (a == id[a]) return a;
	return id[a] = find(id[a]);
}

void merge(int a, int b){
	a = find(a);
	b = find(b);
	if (a == b) return;
	if (sz[a] < sz[b])
		swap(a, b);
	id[b] = a;
	sz[a] += sz[b];
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m>>k; // n eixo x, m eixo y

	for (int i = 0; i < MAXN; i++){ // 0 esq, 1 dir, 2 cima, 3 baixo
		id[i] = i;
		sz[i] = 1;
	}

	int x, y, r, xx, yy, rr;
	fr(i, k){ // id : i + 4
		cin>>x>>y>>r;
		if (x - r <= 0)
			merge(0, i + 4);
		if (x + r >= n)
			merge(1, i + 4);
		if (y + r >= m)
			merge(2, i + 4);
		if (y - r <= 0)
			merge(3, i + 4);
	
		for (int j = 0; j < sensor.size(); j++){
			tie(xx, yy, rr) = sensor[j];
			if ( sq(x - xx) + sq(y - yy) <= sq(r + rr) )
				merge(j + 4, i + 4);
		}

		sensor.pb({x, y, r});
	}

	bool ok = 0;

	// 0 esq, 1 dir, 2 cima, 3 baixo
	ok |= find(0) == find(1); 
	ok |= find(0) == find(3);
	ok |= find(1) == find(2);
	ok |= find(2) == find(3);

	if (!ok)
		cout<<"S"<<endl;
	else
		cout<<"N"<<endl;
}