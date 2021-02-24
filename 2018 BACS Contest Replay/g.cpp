#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(__int128 i = 0; i < n; i++)
#define frr(i, n) for(__int128 i = 1; i <= n; i++)
#define frm(i, n) for(__int128 i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<__int128,__int128> pii;
typedef pair<__int128, __int128> p__int128;
typedef pair<double, double> ponto;
typedef vector<vector<__int128>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

const __int128 N = 10000000;
__int128 lp[N+1];
vector<__int128> pr;

void sieve(){
	for (__int128 i=2; i<=N; ++i) {
	    if (lp[i] == 0) {
	        lp[i] = i;
	        pr.push_back (i);
	    }
	    for (__int128 j=0; j < (__int128)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
	        lp[i * pr[j]] = pr[j];
	}
}

__int128 solve(__int128 f, __int128 g){
	//cout << f << " | " << g << endl;
	if(f == 2*g) return 1;
	if(f < 2*g) return 0;

	if(f%2 == 0)
		return (f/2 - g - 1)*6 + 3 + 3;
	else
		return ((f-1)/2 - g)*6 + 3;
}

__int128 solveEqual(__int128 f, __int128 g){
	//cout << f << " | " << g << endl;
	if(f == 2*g) return 1;
	if(f < 2*g) return 0;

	if(f%2 == 0)
		return 2;
	else
		return 1;
}

int main(){
	fastio;
	sieve();

	ll t;
	cin >> t;

	while(t--){
		ll F, G;
		__int128 f, g;
		cin >> F >> G;
		f = F;
		g = G;

		if(f == g*g){
			cout << 1 << endl;
			continue;
		}

		/*
		Não tem como os 3 serem iguais
		*/

		__int128 x = 1, y = 1;

		for(auto p : pr){
			if(f == 1 && g == 1) break;
			__int128 fi = 0, gi = 0;

			while(f%p == 0){
				f/=p;
				fi++;
			}

			while(g%p == 0){
				g/=p;
				gi++;
			}

			x *= solve(fi, gi);
			y *= solveEqual(fi, gi);
		}

		if(g > 1){
			cout << 0 << endl;
			continue;
		}

		if(f > 1){
			x *= solve(1, 0);
			y *= solveEqual(1, 0);
		}

		if(x == 0){
			cout << 0 << endl;
			continue;
		}

		y *= 3;

		cout << (ll)((x - y)/6 + y/3) << endl;
	}
}
