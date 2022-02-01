#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

// #define endl '\n'
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
const int MAXN = 1e5 + 10;

const long double EPS = 1e-8;
int sign(long double x) { return (x > EPS) - (x < -EPS); }

ll n, p;

long double tenta(ll k){
	stack<long double> up, down;

	up.push(p);

	for (int i = n - p + 2; i <= n; i++)		
		up.push(i);

	for (int i = n + k - p + 1; i <= n + k; i++)		
		down.push(i);
	
	long double ans = k;

	while (!up.empty() and !down.empty()){
		if (sign(ans - 1) >= 0){
			ans /= down.top();
			down.pop();
		}
		else{
			ans *= up.top();
			up.pop();
		}
	}

	while (!up.empty()){
		ans *= up.top();
		up.pop();
	}

	while (!down.empty()){
		ans /= down.top();
		down.pop();
	}

	return ans;
}



int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>p;

	ll l = 1;
	while (l <= n and (p + l * p <= n + l + 1))
		l++;
	
	long double ans = tenta(l);

	cout<<setprecision(12)<<fixed;
	cout<<ans<<endl;
}