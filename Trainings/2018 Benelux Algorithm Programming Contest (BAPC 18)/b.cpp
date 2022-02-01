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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int month[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int to_num(string s){
	int m, d;
	m = (s[0] - '0') * 10 + (s[1] - '0');
	d = (s[3] - '0') * 10 + (s[4] - '0');

	return month[m - 1] + d;
}

void to_date(int x){
	int m = 1, d = 0;
	for (int i = 1; i <= 12; i++)
		if (month[i] >= x){
			m = i;
			break;
		}

	d = x - month[m - 1];
	
	if (m < 10)
		cout<<0;
	cout<<m<<"-";

	if (d < 10)
		cout<<0;
	cout<<d<<endl;	
}

vi v;

int32_t main(){
	fastio;
	int n;
	cin>>n;

	string s;
	fr(i, n){
		cin>>s;
		cin>>s;
		v.pb(to_num(s));
	}

	sort(all(v));
	v.pb(v[0] + 365); // virar o ano;

	int mx = -1;

	vi ans;

	for (int i = 0; i < n; i++){
		if (v[i + 1] - v[i] > mx){
			ans.clear();
			ans.pb(v[i + 1] - 1);
			mx = v[i + 1] - v[i];
		}
		else if (v[i + 1] - v[i] == mx){
			ans.pb(v[i + 1] - 1);
		}
	}

	sort(all(ans));

	int d = -1;
	for (int x : ans)
		if (x > 300){
			d = x;
			break;
		}
	if (d == -1)
		d = ans[0];

	if (d > 365)
		d -= 365;

	to_date(d);		
}