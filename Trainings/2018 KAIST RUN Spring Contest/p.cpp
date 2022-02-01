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

int n, m, k, v[40][40];

vector< tuple<int, int, int, int> > ans;

void stk(int freq, int col){
	if (freq % 2 == 0){
		for (int i = 0; i < freq - 1; i += 2)
			ans.pb({1, col + 1, v[i + 1][col], v[i][col]}); // vert, col, upper, lower
	}
	else{
	
		int aux = v[freq - 1][col] == 1? 2 : 1;
	
		for (int i = 0; i < 5; i++)
			v[freq + i][col] = aux;
		
		freq += 5;
		
		for (int i = 0; i < freq - 1; i += 2)
			ans.pb({1, col + 1, v[i + 1][col], v[i][col]});	
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m>>k;

	vii freq(m);

	fr(j, m)
		freq[j] = {0, j};

	fr(i, n)
		fr(j, n){
			cin>>v[n - i - 1][j];
			if (v[n - i - 1][j] != 0)
				freq[j].fst++;
		}

	sort(all(freq));

	for (auto x : freq)
		if (x.fst != 0)
			stk(x.fst, x.snd);

	cout<<ans.size()<<endl;			

	int a, b, c, d;
	for (auto x : ans){
		tie(a, b, c, d) = x;
		cout<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
	}
}