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

int pr[MAXN];

int main(){
	fastio;
	int q;
	cin >> q;

	pq<pii> richer, comefirst;

	int ind = 1;

	while(q--){
		int op, a;
		cin >> op;

		if(op == 1){
			cin >> a;
			richer.push({a, -ind});
			comefirst.push({-ind, ind});
			ind++;
		}
		else if(op == 2){
			while(pr[comefirst.top().s] == 1){
				comefirst.pop();
			}
			cout << comefirst.top().s << " ";
			pr[comefirst.top().s] = 1;
			
			comefirst.pop();
		}
		else{
			while(pr[-richer.top().s] == 1){
				richer.pop();
			}
			cout << -richer.top().s << " ";
			pr[-richer.top().s] = 1;
			richer.pop();
		}
	}
	cout << endl;
}
