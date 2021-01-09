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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int sng = 1; // -1 = max, 1 = min

map< tuple<int, int, int>, pair< int, long double> > memo;

vii tirar(int n, int val){
	string s = to_string(n);
	
	vii ans;
	int aux, aux2;	
	
	for (int i = 1; i < 1 << s.size(); i++){
		aux = 0;

		for (int j = 0; j < s.size(); j++)
			if (i & (1 << j))
				aux += s[j] - '0';
		
		if (aux == val){
			aux = aux2 = 0;

			int cnt = 1, cnt2 = 1;
			for (int j = s.size() - 1; j >= 0; j--)
				if (!(i & (1 << j))){
					aux += (s[j] - '0') * cnt;
					cnt *= 10;
				}
				else{
					aux2 += (s[j] - '0') * cnt2;
					cnt2 *= 10;
				}
			
			ans.pb({aux2, aux});	
		}	
	}
	return ans;	
}

pair<int, long double> rec(int n, int d1, int d2){
	vii aux = tirar(n, d1 + d2);
	
	if (aux.empty())
		return {-1, (long double) n};

	if (memo.count({n, d1, d2}))
		return memo[{n, d1, d2}];

	long double ans = sng * INF, p;
	int rt = -1;
	for (auto x : aux){
		p = 0;
		for (int i = 1; i <= 6; i++){
			for (int j = 1; j <= 6; j++){
				p += (1.0/36.0) * (rec(x.snd, i, j).snd);
			}
		}
		if (sng * p < sng * ans){
			ans = p;
			rt = x.fst;
		}
	}

	memo[{n, d1, d2}] = {rt, ans};

	return {rt, ans};	
}

int32_t main(){
	fastio;
	cout << setprecision(5)<<fixed;
	int n, d1, d2;

	cin>>n>>d1>>d2;

	pair<int, long double> aux;

	aux = rec(n, d1, d2);
	cout<<aux.fst<<' '<<aux.snd<<endl;

	memo.clear();
	
	sng = -1;
	aux = rec(n, d1, d2);
	cout<<aux.fst<<' '<<aux.snd<<endl;
}