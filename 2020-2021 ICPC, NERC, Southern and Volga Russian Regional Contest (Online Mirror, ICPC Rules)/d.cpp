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

#define MAXN 200010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int n, a, b, m;
int fr[MAXN];

int main(){
	fastio;

	int t;
	cin >> t;

	while(t--){
		cin >> n >> m >> a >> b;
		frr(i, m) cin >> fr[i];
		sort(fr + 1, fr + m + 1);
		int tmax;

		if(a < b) tmax = b - 1;
		else tmax = n - b;

		int ans = 0;
		for(int i = m; i >= 1; i--){
			/*
			cout << ans + fr[i] << endl;
			db;
			*/
			if(ans + 1 + fr[i] <= tmax) ans++;
		}

		cout << min(ans, abs(a - b) - 1) << endl;
	}
}
