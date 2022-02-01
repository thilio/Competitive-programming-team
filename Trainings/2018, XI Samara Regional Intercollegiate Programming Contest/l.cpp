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
const int MAXN = 2e5 + 10;

int nxt[30][MAXN];
string s;

int32_t main(){
	fastio;
	cin>>s;

	int n = s.size();
	
	memset(nxt, INF, sizeof(nxt));
	frr(i, n)
		nxt[s[i - 1] - 'a'][i - 1] = i;
	
	for (int i = 0; i <= 'z' - 'a'; i++){
		for (int j = n; j >= 0; j--)
			nxt[i][j] = min(nxt[i][j], nxt[i][j + 1]);
	}
	
	// fr(i, 4){
	// 	for (int j = 0; j <= n; j++)
	// 		cout<<nxt[i][j]<<' ';
	// 	gnl;		
	// }


	int q;
	cin>>q;

	char c;
	string t;

	stack<int> in;
	int out = 0;

	in.push(0);


	while (q--){
		cin>>t;

		if (t == "push"){
			cin>>c;
			if (out > 0)
				out++;
			else{
				int aux = in.top();
				if (nxt[c - 'a'][aux] != INF){
					// cout<<aux<<' '<<nxt[c - 'a'][aux]<<endl;
					in.push(nxt[c - 'a'][aux]);
				}
				else
					out++;
			}
		}
		else{
			if (out > 0)
				out--;
			else
				in.pop();
		}

		if (out == 0)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
}