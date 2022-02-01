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
const int MAXN = 2e6 + 10;

int check[MAXN];
vi fibo;
vii in;

int32_t main(){
	fastio;
	check[1] = 1;
	fibo = {1, 1};
	
	int cnt = 1;
	while (fibo.back() < MAXN){
		fibo.pb(fibo.back() + fibo[fibo.size() - 2]);
		if (fibo.back() < MAXN)
			check[fibo.back()] = cnt++;
	}

	int n, x;
	cin>>n;


	frr(i, n){
		cin>>x;
		if (check[x] > 0)
			in.pb({x, i});
	}
	sort(all(in));

	for (int i = 1; i < in.size(); i++){
		if (check[in[i].fst] == check[in[i - 1].fst] + 1 or in[i].fst == 1){
			cout<<(in[i - 1].snd)<<' '<<(in[i].snd)<<endl;
			return 0;
		}
	}
	cout<<"impossible"<<endl;
}