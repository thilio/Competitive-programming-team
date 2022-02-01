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
const int MAXN = 1e4 + 10;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, v[MAXN];

	cin>>n;
	fr(i, n)
		cin>>v[i];

	int p = n; // começa a segunda parte	

	for (int i = 1; i < n; i++)
		if (v[i] < v[i - 1]){ // achei começo
			p = i;
			break;
		}

	vi a;
	
	for (int i = p; i < n; i++)
		a.pb(v[i]);

	for (int i = 0; i < p; i++)
		a.pb(v[i]);

	bool srt = 1;		

	for (int i = 1; i < n; i++)
		if (a[i] < a[i - 1])
			srt = 0;	

	if (srt)
		cout<<"Phew"<<endl;
	else
		cout<<"Lie"<<endl;		


}