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

int pr[MAXN];

int main(){
	fastio;
	int t;
	cin >> t;

	while(t--){
		int n, k, m, x;
		cin >> n >> k >> m;

		x = (k - 1)/2;
		frr(i, n) pr[i] = 0;
		frr(i, m){
			int b;
			cin >> b;
			pr[b] = 1; 
		}


		if((n - m)%(k-1) != 0){
			cout << "NO\n";
			continue;
		}

		int acu = 0, deu = 0;
		for(int i = 1; i <= n; i++){
			if(pr[i] == 0) acu++;
			else{
				//cout << i << " " << acu << " "<< (n - m) - acu << endl;
				if(acu >= x && (n - m) - acu >= x) deu = 1;
			}
		}
		if(deu) cout << "YES\n";
		else cout << "NO\n";

	}
}
