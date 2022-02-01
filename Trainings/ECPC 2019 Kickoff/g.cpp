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

int32_t main(){
	freopen("gcd.in","r",stdin);	
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n, gcd, l, r;

	cin>>n;

	cin>>l>>r;

	if (r > l)
		gcd = 1;
	else
		gcd = l;

	n--;
	while (n--){
		cout<<gcd<<endl;
		cin>>l>>r;
		if (r > l)
			gcd = 1;
		else
			gcd = __gcd(l, gcd);
	}

	cout<<gcd<<endl;
}