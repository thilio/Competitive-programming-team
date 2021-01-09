#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e5 + 10;

int n, v[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;

	fr(i, n)
		cin>>v[i];

	set<int> q;
	
	int x;
	fr(i, n){
		x = v[i];
		while ((x % 2) == 0)
			x /= 2;
		q.insert(x);
	}

	if (q.size() > 1){
		cout<<-1<<endl;
		return 0;
	}	


	int cost = 0, c;
	priority_queue<int, vector<int>, greater<int>> pq;

	fr(i, n){
		x = v[i];
		c = 0;
		while ((x % 2) == 0){
			x /= 2;
			c++;
		}
		pq.push(c);
	}

	int a, b;
	while (pq.size() != 1){
		a = pq.top();
		pq.pop();
		b = pq.top();
		pq.pop();

		if (a == b)
			pq.push(a + 1);
		else{
			pq.push(b);
			pq.push(a + 1);
			cost++;
		}
	}

	cout<<cost<<endl;
}