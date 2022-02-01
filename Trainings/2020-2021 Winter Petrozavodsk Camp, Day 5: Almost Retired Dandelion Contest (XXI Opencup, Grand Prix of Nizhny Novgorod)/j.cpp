#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

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

int n;
vi a, b;

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	a.resize(n);
	b.resize(n);

	fr(i, n)
		cin>>a[i];

	fr(i, n)
		cin>>b[i];

	string s;	
	vii ans;

	ans.pb({0, n - 1});
	s.pb('I'); // ordenada


	sort(all(a));


	for (int i = 0; i < n - 1; i++){
		int p = i;

		while (a[p] != b[i]) // achei
			p++;

		int maior = 0;

		for (int j = i; j <= p; j++)
			if (a[j] > a[p])
				maior++;

		int sz = p - i;	

		assert((maior == 0) or (maior == sz));	



		ans.pb({i, p});
	
		if (maior != 0){
			s.pb('I');
			sort(a.begin() + i, a.begin() + p + 1);
		}
		else{
			s.pb('D');
			sort(a.begin() + i, a.begin() + p + 1);
			reverse(a.begin() + i, a.begin() + p + 1);
		}

	}

	fr(i, n)
		assert(a[i] == b[i]);

	cout<<n<<endl;
	fr(i, n)
		cout<<ans[i].fst + 1<<' '<<ans[i].snd + 1<<' '<<s[i]<<endl;
}