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
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int s[3], t[3];

	fr(i, 3)
		cin>>s[i];
	fr(i, 3)
		cin>>t[i];

	sort(s, s + 3);
	sort(t, t + 3);			

	fr(i, 3)
		if (s[i] != t[i]){
			cout<<"NO"<<endl;
			return 0;
		}

	if (t[2] * t[2] != t[0] * t[0] + t[1] * t[1])
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;
}