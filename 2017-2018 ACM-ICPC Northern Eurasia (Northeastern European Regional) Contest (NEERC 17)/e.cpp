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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int freq[MAXN];
vi ans;

int32_t main(){
	fastio;
	int n;
	cin>>n;

	int x;
	fr(i, n){
		cin>>x;
		if (x >= 0)
			freq[x]++;
		else{
			if (freq[-x] > 0)
				freq[-x]--;
			else if (freq[0] > 0){
				freq[0]--;
				ans.pb(-x);
			}
			else{
				cout<<"No"<<endl;
				return 0;
			}
		}
	}

	cout<<"Yes"<<endl;
	for (int x : ans)
		cout<<x<<' ';
	while (freq[0] > 0){
		cout<<1<<' ';
		freq[0]--;
	}
	gnl;	

}