#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int main(){

	fastio;

	int n;
	cin >> n;
	string t;
	getline(cin,t);
	getline(cin,t);

	int r,p,s;
	r=p=s=0;

	fr(i, t.size()){
		if(t[i] == 'R') r++;
		if(t[i] == 'P') p++;
		if(t[i] == 'S') s++;
	}

	int pr,ps,pp;
	pr = ps = pp = 0;
	pr = s - p;
	ps = p - r;
	pp = r - s;


	vector<int> v;
	if(r != 0) v.pb(pr);
	if(s != 0) v.pb(ps);
	if(p != 0) v.pb(pp);
	sort(all(v));
	int x = v.size() - 1;
	int ans = 0;
	if(pp == v[x]) ans += p;
	if(pr == v[x]) ans += r;
	if(ps == v[x]) ans += s;

	cout << ans << endl;

}
