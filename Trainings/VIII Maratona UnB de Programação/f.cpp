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
const int MAXN = 1e5 + 10;

int n, v[MAXN], prv[MAXN], nxt[MAXN];

bool solve(int l, int r){
	if (l >= r)
		return false;	

	int x, y;
	x = l;
	y = r;

	while (x <= y){
		if (prv[x] < l and nxt[x] > r)
			return solve(l, x - 1) or solve(x + 1, r);
		if (prv[y] < l and nxt[y] > r)
			return solve(l, y - 1) or solve(y + 1, r);
		x++;
		y--;
	}

	return true;
}

map<int, int> pos;
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;

	frr(i, n)
		cin>>v[i];

	for (int i = 1; i <= n; i++){
		if (!pos.count(v[i]))
			pos[v[i]] = 0;
	
		prv[i] = pos[v[i]];
		pos[v[i]] = i;
	}		
	
	pos.clear();

	for (int i = n; i >= 1; i--){
		if (!pos.count(v[i]))
			pos[v[i]] = n + 1;
	
		nxt[i] = pos[v[i]];
		pos[v[i]] = i;
	}

	cout<<(solve(1, n) ? "N" : "Y")<<endl;
}