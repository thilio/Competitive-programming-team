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
const int MAXN = 1e5 + 10;
const long double pi = acos(-1);

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n;
	vector<int> v;

	cin>>n;

	int x;
	fr(i, n){
		cin>>x;
		v.pb(x);
	}

	sort(all(v));
	reverse(all(v));

	deque<int> d;

	for (int i = 0; i < n; i++){
		if (i % 2)
			d.push_front(v[i]);
		else
			d.push_back(v[i]);
	}

	long double ans = 0;

	for (int i = 0; i < n; i++)
		ans += d[i] * d[(i + 1)%n];

	ans /= 2.0;

	ans	*= sin((2 * pi)/n);

	cout<<setprecision(3)<<fixed;

	cout<<ans<<endl;
}