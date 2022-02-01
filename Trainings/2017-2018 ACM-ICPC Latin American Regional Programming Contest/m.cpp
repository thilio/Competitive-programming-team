#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
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
const int MAXN = 5e5 + 10;

const ll mod = 1e9 + 7;

int p[MAXN], c[MAXN], c_new[MAXN], cnt[MAXN], cp[MAXN], lcp[MAXN];
pair<int, int> a[MAXN];

void count_sort(int n){
	fill(cnt, cnt + n, 0);
	for (int i = 0; i < n; i++)
		cnt[c[i] + 1]++;
	for (int i = 1; i < n; i++)
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++){
		int x = c[p[i]];
		cp[cnt[x]] = p[i];
		cnt[x]++;
	}
	for (int i = 0; i < n; i++)
		p[i] = cp[i];
}

// suffix array está em p, o suffixo vazio é incluido (p[0] = n)
void suffix_array(vi &s){
	int n = s.size() + 1;
	for (int i = 0; i < n - 1; i++)
		a[i] = {s[i], i};
	a[n - 1] = {-1, n - 1}; // caractere inferior

	sort(a, a + n);

	p[0] = n - 1;
	c[p[0]] = 0;
	for (int i = 1; i < n; i++){
		p[i] = a[i].second;
		c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
	}

	int k = 0;
	while ((1 << k) < n){
		for (int i = 0; i < n; i++)
			p[i] = (p[i] - (1 << k) + n) % n;

		count_sort(n);

		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++){
			int eq = c[p[i - 1]] != c[p[i]];
			eq |= c[(p[i - 1] + (1 << k)) % n] != c[(p[i] + (1 << k)) % n];
			c_new[p[i]] = c_new[p[i - 1]] + eq;
		}
		for (int i = 0; i < n; i++)
			c[i] = c_new[i];	
		k++;
	}

	k = 0;
	for (int i = 0; i < n - 1; i++){ // calcula lcp
		int pi = c[i]; // é a permutação inversa sufixo -> posição
		int j = p[pi - 1];
		while (s[i + k] == s[j + k]) k++;
		lcp[pi - 1] = k; // lcp[i] é entre o sufixo p[i] -> p[i + 1]
		k = max(k - 1, 0);
	}
}

ll fastxp(ll base, ll exp){
	ll ans = 1;

	while (exp){
		if (exp % 2)
			ans = (ans * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}

	return ans;
}

int pos[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, k, x;
	
	cin>>n;

	vector<int> v;

	fr(i, n){
		cin>>k;
		fr(j, k){
			cin>>x;
			v.pb(x);
		}

		v.pb(301);
		pos[i + 1] = pos[i] + k + 1;
	}

	suffix_array(v);

	priority_queue< pii, vector<pii>, greater<pii> > pq;

	for (int i = 0; i < n; i++) // c é a permutação reversa, c[p] é a
		pq.push({c[pos[i]], i});// posição do sufixo que começa em p.
	
	int stk;
	ll ans = 0, exp = v.size() - n;
	while (!pq.empty()){
		tie(ignore, stk) = pq.top();
		pq.pop();
		
		ans = (ans + ((ll) v[pos[stk]]) * fastxp(365, exp)) % mod;
		pos[stk]++;
		exp--;

		if (v[pos[stk]] != 301)
			pq.push({c[pos[stk]], stk});
	}

	cout<<ans<<endl;
}