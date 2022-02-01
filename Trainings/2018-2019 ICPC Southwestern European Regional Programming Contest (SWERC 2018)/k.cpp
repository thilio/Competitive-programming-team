#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 710
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int precomp[MAXN][MAXN];
int dp[MAXN][MAXN];
int n;
string s;

void build(int l, int r){
	int ans = 0, tam = r - l + 1;
	int ini = l;
	while(ini + tam - 1 < n){
		int para = 0;
		for(int i = 0; i < tam; i++){
			if(s[i + l] != s[ini + i]) {
				para = 1;
				break;
			}
		}

		if(para) break;
		ans++;
		ini += tam;
	}

	precomp[l][r] = ans;
}

int solve(int l, int r){
	if(dp[l][r] != -1) return dp[l][r];
	if(l == r) return dp[l][r] = 1;

	int tam = r - l + 1, ans = tam;
	for(int i = l; i < r; i++){
		if(tam%(i - l + 1) == 0){
			if(precomp[l][i] >= tam/(i - l + 1)) ans = min(MOD, solve(l, i));
		}

		ans = min(ans, solve(l, i) + solve(i + 1, r));
	}

	return dp[l][r] = ans;
}

int main(){
	fastio;
	cin >> n >> s;
	fr(i, n) for(int j = i; j < n; j++) build(i, j);
	mem(dp, -1);
	build(0, 1);
	cout << solve(0, n-1) << endl;
}
