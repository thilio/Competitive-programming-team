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

map<char, int> fr;

int main(){
	fastio;
	int n;
	cin >> n;
	string s;
	cin >> s;
	fr(i, n) fr[s[i]]++;
	int pi = 0;
	pq<char> odd;
	pq<char> even;
	for(auto x: fr){
		if(x.s%2 == 1){
			odd.push(x.f);
			pi++;
			x.s--;
		}
		fr(j, x.s) even.push(x.f);
	}		

	if(odd.size()==0){
		cout << 1 << endl;
		vector<char> ans;
		fr(j, (n/2)){
			ans.pb(even.top());
			even.pop();
			even.pop();
		}

		fr(j, ans.size()) cout << ans[j];
		frm(j, ans.size()) cout << ans[j];
		cout << endl;
		return 0;
	}

	int tam, num;
	for(int i = pi; i <= n; i++){
		if(n%i == 0 && (i - pi)%2 == 0 && (n/i)%2 == 1){
			tam = n/i;
			num = i;
			break;
		}
	}
	fr(i, num - pi){
		odd.push(even.top());
		even.pop();
	}
	cout << num << endl;
	fr(i, num){
		vector<char> ans;
		fr(j, (tam - 1)/2){
			ans.pb(even.top());
			even.pop();
			even.pop();
		}
		ans.pb(odd.top());
		odd.pop();

		fr(j, ans.size()) cout << ans[j];
		frm(j, ans.size() - 1) cout << ans[j];
		cout << " ";
	}
	cout<< endl;
}
