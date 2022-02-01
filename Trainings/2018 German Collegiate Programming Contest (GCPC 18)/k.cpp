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

bool memo[66][2000];
int n, g, d[66];

int32_t main(){
	fastio;
	cin>>n>>g;

	frr(i, n)
		cin>>d[i];

	memo[0][0] = 1;

	for (int k = 1; k <= n; k++)
		for (int i = k; i >= 0; i--)
			for (int j = 0; j < 2000 - d[k] - 1; j++)
				memo[i + 1][j + d[k]] |= memo[i][j];

	bool ok = 0;			
	long double x = 0, aux;	

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 2000; j++){
			if (memo[i][j] and j >= g - 10){
				aux = ((long double) 10 + j - g)/( (long double) i + 1); 
				if (aux - 5 <= 0){
					ok = 1;
					x = max(x, aux);
				}
			}
		}	

	if (ok)		
		cout<<setprecision(8)<<x<<endl;	
	else
		cout<<"impossible"<<endl;
}