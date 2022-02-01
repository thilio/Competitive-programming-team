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

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int n;
int l, r;
int p[MAXN], sum = 0;
string s[MAXN];
int pmax[MAXN], pmin[MAXN];
int sumPmax = 0, sumPmin = 0;

int main(){
	cin >> n;
	fr(i, n){
		cin >> s[i] >> p[i];
		p[i] *= 100;
		pmax[i] = min(10000, p[i] + 49);
		sumPmax += pmax[i];

		pmin[i] = max(0, p[i] - 50);
		sumPmin += pmin[i];
	}

	fr(i, n){
		int l = max(pmin[i], 10000 - (sumPmax - pmax[i]));
		int r = min(pmax[i], 10000 - (sumPmin - pmin[i]));
		if(l > r){
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}

		cout << s[i] << " ";
		printf("%d.%02d %d.%02d\n", l/100, l%100, r/100, r%100);
	}
}
