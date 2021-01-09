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
//cout << setprecision(9)<<fixed;

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
	fastio;
	string s, t;

	cin>>s>>t;
	int p, q, n;
	p = 0;
	n = q = s.size();

	while (s[p] == t[p] and p < n)
		p++;
	while (s[q] == t[q] and q >= p)
		q--;

	if (p == n){
		cout<<"YES"<<endl;
		return 0;
	}

	reverse(s.begin() + p, s.begin() + q + 1);

	if (s == t)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
}