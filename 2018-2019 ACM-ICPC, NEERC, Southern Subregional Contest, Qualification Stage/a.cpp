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

typedef tuple<int, int, int> tup;

vector<tup> event;
int ans[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, d;
	cin>>n>>m>>d;

	int a;
	fr(i, n){
		cin>>a;
		event.pb({a, 1, i}); // entra
		event.pb({a + d + 1, 0, i}); // sai
	}

	sort(all(event));

	int mstk = 0;
	stack<int> stk;

	int typ, id;
	for (auto x : event){
		tie(a, typ, id) = x;
		if (typ == 1){
			if (stk.size() == 0){
				mstk++;
				stk.push(mstk);
			}
			ans[id] = stk.top();
			stk.pop();
		}
		else
			stk.push(ans[id]);	
	}

	cout<<mstk<<endl;
	fr(i, n)
		cout<<ans[i]<<' ';
	gnl;	
}