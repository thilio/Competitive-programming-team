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
const int MAXN = 2e5 + 10;

int n;
int mp[MAXN];
vi pos;

int dif(string &s, string &t){
	int ans = 0;
	for (int i : pos)
		ans += (s[i] != t[i]);
	return ans;
}

int32_t main(){
	fastio;

	string s, t, u;
	cin>>s>>t>>u;

	n = s.size();

	fr(i, n)
		if (s[i] != t[i]){
			if (mp[i] == 0){
				mp[i] = 1;
				pos.pb(i);
			}
		}
	
	fr(i, n)
		if (s[i] != u[i]){
			if (mp[i] == 0){
				mp[i] = 1;
				pos.pb(i);
			}
		}
	
	if (pos.size() > 4){
		cout<<"Impossible"<<endl;
		return 0;
	}

	int cnt = 0;
	string ans, aux;

	if (dif(s, t) <= 1 and dif(s, u) <= 1){
		cnt++;
		ans = s;
	}

	aux = s;
	for (int p = 0; p < n; p++){
		if (mp[p] == 0)
			pos.pb(p);

		for (char c = 'a'; c <= 'z'; c++){
			if (c != s[p]){
				aux[p] = c;
				if (dif(aux, t) <= 1 and dif(aux, u) <= 1){
					ans = aux;
					cnt++;
				}
			}
		}
		
		aux[p] = s[p];

		if (mp[p] == 0)
			pos.pop_back();

		if (cnt > 1)
			break;
	}

	if (cnt == 0)
		cout<<"Impossible"<<endl;
	else if (cnt == 1)
		cout<<ans<<endl;
	else	
		cout<<"Ambiguous"<<endl;
}