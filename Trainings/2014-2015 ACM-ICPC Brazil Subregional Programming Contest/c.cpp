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

int m, n;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];

map<string, int> freq;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>m>>n;

	fr(i, m)
		cin>>a[i]>>b[i]>>c[i]>>d[i];

	int ans = 1;

	int x, y, z;
	string s;
	fr(i, n){
		cin>>x>>y>>z;
		s.clear();
		fr(j, m){
			if (a[j] * x + b[j] * y + c[j] * z > d[j])
				s.pb('u');
			else
				s.pb('d');
		}

		freq[s]++;
		ans = max(ans, freq[s]);
	}

	cout<<ans<<endl;
}