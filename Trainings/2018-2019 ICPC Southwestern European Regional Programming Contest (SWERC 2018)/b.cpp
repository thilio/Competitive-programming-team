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

int a[MAXN], b[MAXN];
int n;

bool test(int x){
	multiset<int> baixo, alto;
	for(int i = 1; i < x; i++){
		baixo.insert(-a[i]);
		alto.insert(b[i]);
	}
	for(int i = x; i <= n; i++){
		baixo.insert(-a[i]);
		alto.insert(b[i]);
		
		int l = -*(baixo.begin()), r = *(alto.begin());
		//if(i == 3) cout << l << " " << r << endl;
		if(r - l >= x - 1) {
			return true;
		}
		baixo.erase(baixo.find(-a[i - x + 1]));
		alto.erase(alto.find(b[i - x + 1]));
	}

	return false;
}

int main(){
	fastio;
	cin >> n;
	frr(i, n) {
		cin >> a[i] >> b[i];
	}
	int l = 0, r = n + 1, m;
	while(l < r - 1){
		m = (l + r)/2;
		if(test(m)) l = m;
		else r = m;
	}

	cout << l << endl;
}
