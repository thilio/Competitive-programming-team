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
const int MAXN = 1e5 + 100;

vector<int> lps_p(string &pat){
	int i = 1, len = 0, tam = pat.size();
	vector<int> lps(tam, 0);
	lps[0] = 0;

	while(i < tam){
		if(pat[i] == pat[len]) lps[i++] = ++len;
		else if(len != 0) len = lps[len-1];
		else lps[i++] = 0;
	}

	return lps;
}

vector<int> check(string &txt, string &pat){
	int i = 0, j = 0, tt = txt.size(), tp = pat.size(), ans;
	vector<int> lps = lps_p(pat);
    vector<int> ret;

	while(i < tt){
		if(txt[i] == pat[j]){
			i++;
			j++;
		}

		if(j == tp){
			ret.pb(i);
			j = lps[j-1];
		}
		else if(i < tt && txt[i] != pat[j]){
			if(j == 0) i++;
			else j = lps[j-1];
		}
	}

	for (auto &x : ret)
		x -= pat.size();

	return ret;
}

ll matchp[MAXN][110], matchs[MAXN][110], acpref[MAXN], acsuf[MAXN];

void solve(){
	string t, p;
	cin>>t>>p;

	int n = t.size();
	int m = p.size();


	for (int i = 0; i < n + 2; i++)
		acpref[i] = acsuf[i] = 0;

	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < m + 2; j++)
			matchp[i][j] = matchs[i][j] = 0;


	vi ocp = check(t, p);

	for (auto x : ocp)
		matchs[x][m] = matchp[x][m] = 1;

	for (int i = 0; i < n; i++)
		matchp[i][0] = matchs[i][0] = 1;


	string pref;	
	for (int j = 1; j < m; j++){
		pref.pb(p[j - 1]);
		vi oc = check(t, pref);

		for (auto x : oc)
			matchp[x][j]++;
	}

	pref.clear();
	reverse(all(t));
	for (int j = 1; j < m; j++){
		pref.pb(p[m - j]);
		vi oc = check(t, pref);
		for (auto x : oc)
			matchs[n - x - j][j]++;
	}

	for (int i = n - 2; i >= 0; i--)
		for (int j = 0; j <= m; j++)
			matchs[i][j] += matchs[i + 1][j];

	for (int i = 1; i < n; i++)
		for (int j = 0; j <= m; j++)
			matchp[i][j] += matchp[i - 1][j];

	acpref[0] = matchp[0][m];	
	for (int i = 1; i < n; i++)
		acpref[i] = acpref[i - 1] + matchp[i][m];

	acsuf[n - 1] = matchs[n - 1][m];
	for (int i = n - 2; i >= 0; i--)
		acsuf[i] += acsuf[i + 1] + matchs[i][m];



	ll q, l, r;
	cin>>q;

	while (q--){
		cin>>l>>r;
		l--;
		r--;

		ll ans = 0;

		ans += acpref[l - m + 1] * (n - r);
		ans += acsuf[r] * (l + 1);

		for (int j = 1; j < m; j++){
			if (l - j + 1 >= 0){
				ans += matchp[l - j + 1][j] * matchs[r][m - j];
			}
		}

		ll tot = (l + 1) * (n - r);
		ll mdc = __gcd(ans, tot);

		cout<<ans/mdc<<'/'<<tot/mdc<<endl;
	}
}

int32_t main(){
	freopen("string.in", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}
