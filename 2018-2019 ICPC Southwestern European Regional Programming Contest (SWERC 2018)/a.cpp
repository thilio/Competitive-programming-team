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

#define MAXN 1000010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int light[MAXN];
int ans = 0, n, cur = 0;

int main(){
	fastio;
	cin >> n;

	int k;
	cin >> k;

	while(k--){
		int x;
		cin >> x;
		for(int i = 1; i*x <= n; i++){
			if(light[i*x] == 0) cur++;
			else cur--;
			light[i*x] ^= 1;
		}

		ans = max(cur, ans);
	}

	cout << ans << endl;
}
