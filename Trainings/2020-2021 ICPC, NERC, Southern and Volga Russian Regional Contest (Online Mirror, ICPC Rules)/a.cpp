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

#define MAXN 500010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

// lis em n log n com pd e busca binaria

vector<int> pile[MAXN];
deque<int> lis(vector<int> const& a) {
    int n = a.size();
    fr(i, n) pile[i].clear();
    vector<int> lis;

    for(int i = 0; i < n; i++){
        auto pos = upper_bound(lis.begin(), lis.end(), a[i]);
        int k = (int)(upper_bound(lis.begin(), lis.end(), a[i]) - lis.begin());
        if(pos == lis.end()) lis.push_back(a[i]);
        else *pos = a[i];
    	pile[k].pb(i);
    }

    int last = MOD;
    deque<int> ans;
    for(int i = lis.size() - 1; i >= 0; i--){
    	for(int j = pile[i].size() - 1; j >= 0;j--){
    		int davez = pile[i][j];
    		if(a[davez] <= last && (ans.size() == 0 || davez <= ans.front())){
    			last = a[davez];
    			ans.push_front(davez);
    			break;
    		}
    	}
	    /*
	    	for(auto x:pile[i]) cout << x << ' ';
	    	cout << endl;
	    */
    }
    
    return ans;
}

int main(){
	fastio;
	int t;
	cin >> t;

	while(t--){
		int n;
		cin >> n;
		vector<int> a(n);
		fr(i, n) cin >> a[i];
		deque<int> v = lis(a);
	
		cout << v.size() << endl;
		for(auto x: v) cout << x << " ";
		cout << endl;
	
		/*
			for(auto x: v) cout << x << " ";
			cout << endl;
		*/
		v.push_front(-1);
		v.push_back(n);
		int ans = v.size() - 2;
		for(int i = 0; i < v.size() - 1; i++){
			int l = v[i], r = v[i+1];
			for(int j = l+1; j < r; j++){
				if(l == -1 || a[j] > a[l]) {
					ans++;
					break;
				}
			}
		}
		cout << ans << endl;
	}
}
