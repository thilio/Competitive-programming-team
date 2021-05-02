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

#define int long long

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 5e5 + 10;


int p[MAXN], c[MAXN], c_new[MAXN], cnt[MAXN], cp[MAXN], lcp[MAXN];
pair<int, int> a[MAXN];

void count_sort(int n){
	fill(cnt, cnt + n + 1, 0);
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

// O suffix a. está em p, o i-ésimo menor suffixo começa em na posição p[i]
// o suffixo vazio está incluso (p[0] = n)
void suffix_array(vi &s){
	int n = s.size() + 1;
	for (int i = 0; i < n - 1; i++)
		a[i] = {s[i], i};
	a[n - 1] = {-1, n - 1}; // caractere 32, menor legivel

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

	k = 0; lcp[n - 1] = 0;
	for (int i = 0; i < n - 1; i++){ // calcula lcp
		int pi = c[i]; // permutação inversa, na posição i começa - c[i]-ésimo suffixo
		int j = p[pi - 1];
		while (s[i + k] == s[j + k]) k++;
		lcp[pi - 1] = k; // lcp[i] é o maior prefixo entre os sufixos p[i] -> p[i + 1]
		k = max<ll>(k - 1, 0);
	}
}

ll seg[4 * MAXN], lazy[4*MAXN], need[4 * MAXN];

void propagate(int node, ll l, ll r){
	if (lazy[node] != 0){
		if (l != r){
			lazy[node<<1] = lazy[node];
			lazy[node<<1|1] = lazy[node]; 
		}

		seg[node] = (r - l + 1) * lazy[node];
		lazy[node] = 0;
	}
}

void update(int node, int l, int r, int ql, int qr, int val){
	propagate(node, l, r);

	if (qr < l or r < ql)
		return;

	if (ql <= l and r <= qr){
		lazy[node] = val;
		propagate(node, l, r);
		return;
	}

	int meio = (l + r)/2;
	update(node<<1, l, meio, ql, qr, val);
	update(node<<1|1, meio + 1, r, ql, qr, val);
	seg[node] = seg[node<<1] + seg[node<<1|1];
}


ll query(int node, int l, int r, int ql, int qr){
	propagate(node, l, r);

	if (qr < l or r < ql)
		return 0;
	if (ql <= l and r <= qr)
		return seg[node];
	
	int meio = (l + r)/2;
	ll ans = query(node<<1, l, meio, ql, qr);
	ans += query(node<<1|1, meio + 1, r, ql, qr);
	return ans;
}

int limiar[MAXN];

void solve(){
	int n;
	cin>>n;

	fr(i, 4 * n + 10) seg[i] = lazy[i] = 0;

	vi v(n);

	fr(i, n)
		cin>>v[i];

	suffix_array(v);

	for (int i = 0; i <= n; i++)
		limiar[p[i]] = p[i] + lcp[i]; // pego daqui para frente

	stack<pii> stk;
	stk.push({INF, n});

	ll ans = 0;

	for (int p = n - 1; p >= 0; p--){
		while (stk.top().fst < v[p])
			stk.pop();

		update(1, 0, n - 1, p, stk.top().snd - 1, v[p]); // atualiza a seg

		stk.push({v[p], p});

		ans += query(1, 0, n - 1, limiar[p], n - 1);
	}

	cout<<ans<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}