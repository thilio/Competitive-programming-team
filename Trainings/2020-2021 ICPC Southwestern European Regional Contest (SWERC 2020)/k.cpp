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
const int MAXN = 300300;

int n;
int p[MAXN], c[MAXN], lcp[MAXN], cnt[MAXN], p_new[MAXN], c_new[MAXN];

pair<char, int> a[MAXN];

void count_sort(){
	fill(cnt, cnt + n + 1, 0);

	for(int i = 0; i < n; i++) cnt[c[i] + 1]++;
	cnt[0] = 0;

	for(int i = 1; i < n; i++){
		cnt[i] += cnt[i - 1];
	}

	for(int i = 0; i < n; i++){
		int j = c[p[i]];
		p_new[cnt[j]] = p[i];
		cnt[j]++;
 	}

 	for(int i = 0; i < n; i++){
 		p[i] = p_new[i];
 	}
}

void build(string &s){
	s.push_back('$');
	n = s.size();

	fr(i, n) a[i] = {s[i], i};
	sort(a, a + n);

	p[0] = n - 1;
	c[p[0]] = 0;

	for(int i = 1; i < n; i++){
		p[i] = a[i].snd;
		c[p[i]] = c[p[i - 1]] + (a[i].fst != a[i - 1].fst);
	}

	int k = 0;
	while((1 << k) < n){
		for(int i = 0; i < n; i++){
			p[i] = (p[i] - (1 << k) + n)%n;
		}

		count_sort();

		c_new[p[0]] = 0;
		for(int i = 1; i < n; i++){
			pii at = {c[p[i]],c[(p[i] + (1 << k))%n]};
			pii prev = {c[p[i - 1]],c[(p[i - 1] + (1 << k))%n]};
			c_new[p[i]] = c_new[p[i - 1]] + (at != prev);
		}

		for(int i = 0; i < n; i++){
			c[i] = c_new[i];
		}
		k++;
	}

	k = 0;

	for(int i =0; i< n - 1; i++){
		int pi = c[i];
		int j = p[pi - 1];
		while(s[i + k] == s[j + k]) k++;
		lcp[pi] = k;
		k = max(0, k - 1);
	}

}

int main(){

	fastio;

	string s;
	getline(cin, s);
	build(s);

	int ans = INF;
	int ini = llINF;

	for(int i = 1; i < n; i++){
		int j = lcp[i];
		if(i != n - 1){
			j = max(j, lcp[i + 1]);
		}
		j++;
		if(p[i] + j - 1 >= n - 1) continue;
		if(j < ans ||(j == ans && p[i] < ini)){
			ans = j;
			ini = p[i];
		}
	}

	for(int i = ini; i < ans + ini; i++) cout << s[i];
	gnl;

}
