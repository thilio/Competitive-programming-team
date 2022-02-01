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
const ll mod1 = 1000015553; // primo grande 1
const ll mod2 = 1000028537; // primo grande 2

struct str_hash{
	vi s; // hash de elemento zero é zero (intervalo nulo)
	ll n;
	const ll p = 2;
	vector<ll> hsh1, pwr1, hsh2, pwr2;

	str_hash(vi _s) : n(_s.size()), s(_s), hsh1(n), pwr1(n), hsh2(n), pwr2(n){	
		pwr1[0] = pwr2[0] = 1;
		for (int i = 1; i < n; i++){
			pwr1[i] = (p * pwr1[i - 1]) % mod1;
			pwr2[i] = (p * pwr2[i - 1]) % mod2;
		}
		hsh1[0] = hsh2[0] = s[0];
		for (int i = 1; i < n; i++){
			hsh1[i] = (hsh1[i - 1] * p + (ll)(s[i]))%mod1;
			hsh2[i] = (hsh2[i - 1] * p + (ll)(s[i]))%mod2;
		}
	}
	pair<ll, ll> operator()(int i, int j){ // hash no intervalo [i, j]
		if (i == 0) return {hsh1[j], hsh2[j]};
		ll ret1 = ((hsh1[j] - (hsh1[i - 1] * pwr1[j - i + 1])) % mod1 + mod1) % mod1;
		ll ret2 = ((hsh2[j] - (hsh2[i - 1] * pwr2[j - i + 1])) % mod2 + mod2) % mod2;
		return {ret1, ret2};
	}
};

const pair<ll, ll> nulo = {0, 0};

int n, mxlen;
vi str[MAXN], xr, xrn;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;
	
	string s;
	fr(i, n){
		cin>>s;
		mxlen = max<int>(mxlen, s.size());
		str[i].resize(s.size());
		
		fr(j, s.size())
			str[i][j] = s[j] - '0';
	}

	xr.resize(mxlen);
	xrn.resize(mxlen);
	fill(all(xr), 0);

	fr(i, n)
		fr(j, str[i].size())
			xr[j] ^= str[i][j]; // cor das strings

	str_hash hxr = str_hash(xr);		

	ll ans = 0;
	for (int id = 0; id < n; id++){
		int sz = str[id].size();
		fr(i, mxlen){
			xrn[i] = xr[i];
			if (i < sz) xrn[i] ^= str[id][i]; // xor sem a string atual
		}

		str_hash hstr = str_hash(str[id]);
		str_hash hxrn = str_hash(xrn); // computa o hash todo, mas usa aos poucos


		for (int i = sz - 1; i > 0; i--){
			int mnsz = min(i, sz - i);
			if (hxr(0, mnsz - 1) == hstr(i, i + mnsz - 1)){
				if (mnsz == i){ // caso 1, parte maior foi movida
					if (hstr(i + mnsz, sz - 1) == hxrn(mnsz, sz - mnsz - 1) and hxrn(sz - mnsz, mxlen - 1) == nulo){
						ans++;
					}
				}
				else if (hxr(mnsz, i - 1) == nulo and hxrn(i, mxlen - 1) == nulo){ // caso 2, parte maior ficou
					ans++;
				}
			}
		}
	}

	cout<<ans<<endl;
}