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
const ll mod = 1e9+7;

int32_t main(){
	fastio;
	ll a, b;
	cin>>a>>b;

	if (a <= b){
		cout<<b - a<<endl;
		return 0;
	}

	int cnt = 0;
	while (a != b){
		if (a < b){
			cnt += b - a;
			a = b;
			continue;
		}
		else if (a % 2){
			a++;
			cnt++;
			continue;
		}
		else{
			a = a/2;
			cnt++;
		}
	}

	cout<<cnt<<endl;
}