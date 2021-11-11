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
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define random mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define myrand(a, b) uniform_int_distribution<int>(a, b)(rng)

#define mp make_pair
#define pq priority_queue

#define MAXN 100010
#define MOD 1000000007
#define INF 1000000000000000100

int fr[10];
int tot[10];

bool tenta(deque<int> d, int davez){
	int f[10];
	fr(i, 10) f[i] = fr[i];
	while(d.size()){
		if(d.front() == davez) return true;
		if(f[d.front()] == 0) return false;
		f[d.front()]--;
		d.pop_front();
	}
	return false;
}

vector<int> ans;
void apply(deque<int> & d){
	int ok = 0;
	fr(i, 10) ok += fr[i];
	if(ok == 0){
		for(auto x: ans) cout << x;
		for(auto x: d) cout << x;
		cout << endl;
		exit (0);
	}



	int nxt = -1;
	frm(i, 10){
		if(tenta(d, i)){
			nxt = i;
			break;
		}
	}
	while(d.size()){
		if(d.front() == nxt) break;
		fr[d.front()]--, tot[d.front()]--;
		d.pop_front();
	}

	tot[nxt]--;
	ans.pb(nxt);
	d.pop_front();
}

signed main(){
	fastio;
	deque<int> d;
	string s;
	cin >> s;
	fr(i, s.size()) d.push_back(s[i] - '0'), tot[s[i] - '0']++;
	frr(i, 9) cin >> fr[i];
	
	int i = 0;
	while(i < d.size()){
		if(tot[d[i]] == fr[d[i]]){
			d.erase(d.begin() + i, d.begin() + i + 1);
		}
		else i++;
	}
	while(d.size()){
		apply(d);

		i = 0;
		while(i < d.size()){
			if(tot[d[i]] == fr[d[i]]){
				d.erase(d.begin() + i, d.begin() + i + 1);
			}
			else i++;
		}
	}

	for(auto x: ans) cout << x;
	cout << endl;
}
