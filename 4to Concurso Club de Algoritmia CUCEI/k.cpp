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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int mn, mx;
int qry;

void solve(vi &v, int p){
	if (v.size() == 1){
		cout<<"! "<<v[0]<<endl;
		exit(0);
	}

	int n = v.size(), x;
	vi menor, maior;
	int mid = v[uniform_int_distribution<int>(0, n - 1)(rng)];

	menor.pb(mid);

	for (int i = 0; i < n; i++){
		if (v[i] == mid)
			continue;

		if (qry == 7777)
			while(true);

		cout<<"? "<<mn<<' '<<mid<<' '<<v[i]<<endl;
		cin>>x;
		qry++;

		if (x == mid)
			maior.pb(v[i]);
		else
			menor.pb(v[i]);
	}	

	if (menor.size() > p)
		solve(menor, p);
	solve(maior, p - menor.size());
	
}

int32_t main(){
//	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, aux, x;
	cin>>n;

	mn = 1;
	mx = 2;
	aux = 3;	

	for (int i = 3; i <= n; i++){
		cout<<"? "<<mn<<' '<<mx<<' '<<aux<<endl;
		cin>>x;
		qry++;

		if (mn == x)
			swap(mn, aux);
		if (mx == x)
			swap(mx, aux);
		aux = i + 1;	
	}

	vi v;
	for (int i = 1; i <= n; i++)
		if (i != mn and i != mx)
			v.pb(i);

	shuffle(all(v), rng); // aquele shuffle inicial

	solve(v, n / 2 - 1);
}