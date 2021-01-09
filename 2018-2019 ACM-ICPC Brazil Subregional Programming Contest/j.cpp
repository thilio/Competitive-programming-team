#include "bits/stdc++.h"
using namespace std;

const long long int llINF = (long long)(1e18) + 100;   
const int MAXN = 2e2 + 10;

int n, k;
long double x[MAXN], y[MAXN];
long double memo[2048][MAXN];

long double dist(int a, int b){
	return hypot(x[a] - x[b], y[a] - y[b]);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>k;

	for (int i = 0; i < n; i++)
		cin>>x[i]>>y[i];
	
	for (int i = 0; i < 2048; i++)
		fill(memo[i], memo[i] + MAXN, llINF);

	for (int v = k; v < n; v++)
		for (int t = 0; t < k; t++)
			memo[1<<t][v] = dist(v, t);

	for (int mask = 1; mask < (1 << k); mask++){
		for (int v = k; v < n; v++){
			for (int smask = (mask - 1) & mask; smask > 0; smask = (smask - 1) & mask)
				memo[mask][v] = min(memo[mask][v], memo[smask][v] + memo[mask ^ smask][v]);

			if (memo[mask][v] < llINF)
				for (int u = k; u < n; u++)
					memo[mask][u] = min(memo[mask][u], memo[mask][v] + dist(u, v));
		}
	}
	
	cout<<setprecision(5)<<fixed;
  
	long double ans = llINF;
	for (int v = k; v < n; v++)
		ans = min(ans, memo[(1<<k) - 1][v]);
	cout<<ans<<endl;		
}