#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n, m;
string s,t;
vi a;
vi k;
vi b;

int sub(int aa, int bb){// return aa - bb;
	return (aa - bb + 26)%26;
}

int main(){

	fastio;

	cin >> n >> m;
	a.resize(m + 1);
	k.resize(m + 1);
	b.resize(m + 1);

	cin >> s;
	//dbg(s);

	for(int i = s.size() - 1; i>= 0; i--){
		int j = s.size() - i;
		a[m - j + 1] = s[i] - 'a'; 
	}

	cin >> t;
	//dbg(t);

	for(int i = 0; i < m; i++){
		b[i + 1] = t[i] - 'a';
	}

	int p = m - n;

	while(p >= 1){
		
		k[p + n] = sub(b[p + n], a[p + n]);
			
		a[p] = k[p + n];
		
		p--;
	}

	for(int i = n + 1; i <= m; i++){
		cout << (char)(k[i] + 'a');
	}
	cout << s << endl;


}
