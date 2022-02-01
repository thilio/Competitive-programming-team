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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int peso[MAXN], esq[MAXN], dir[MAXN], id;

int solve(int a, int b){
	if (a + b == 0) 
		return 0;

	int me = ++id;
	if (b > 0){
		peso[me] = 2;
		b--;
	}
	else{
		peso[me] = 1;
		a--;
	}

	int la, lb, ra, rb;

	la = ra = lb = rb = 0;

	lb = b/2;

	rb = (b + 1)/2;


	if (b % 2 and a > 0){
		la++;
		a--;
	}

	la += (a + 1)/2;
	ra += a/2;


	int pl = la + 2*lb;
	int pr = ra + 2*rb;

	if (abs(pl - pr) > 1){
		cout<<-1<<endl;
		exit(0);
	}

	esq[me] = solve(la, lb);
	dir[me] = solve(ra, rb);

	return me;
		
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b;
	cin>>a>>b;

	solve(a, b);

	frr(i, id)
		cout<<peso[i]<<' '<<esq[i]<<' '<<dir[i]<<endl;
	
}