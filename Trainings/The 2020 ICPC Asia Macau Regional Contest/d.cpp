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


map<string, double> values;


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	values["Crit Rate"] = 5;
	values["Crit DMG Rate"] = 50;

	fr(i, 25){
		string s;
		getline(cin, s);

		int p = 0;
		while (s[p] != '+')
			p++;

		string nme = s.substr(0, p);
		s = s.substr(p + 1);

		if (s.back() == '%')
			s.pop_back();

		values[nme] += stod(s);
	}

	double atkv = values["ATK"];
	double atkr = values["ATK Rate"];
	double critd = values["Crit DMG Rate"];
	double critr = min(100.00, values["Crit Rate"]);


	double atk = 1500.00 * (100.00 + atkr)/100.00 + atkv;

	double ans = (atk * (100.00 - critr)/100.00) + (atk * (100 + critd) * critr/10000.00);

	cout<<setprecision(12)<<fixed;

	cout<<ans<<endl;
}