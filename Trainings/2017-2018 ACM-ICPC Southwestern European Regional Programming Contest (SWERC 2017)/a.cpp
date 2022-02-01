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
const int MAXN = 1e5 + 10;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int n, m, in[MAXN], out[MAXN];

	cin>>n>>m;

	fr(i, n)
		cin>>in[i];

	fr(j, m)
		cin>>out[j];

	int tme, frq;
	tme = frq = 0;
	map<int, int> freq;


	fr(i, n)
		fr(j, m)
			if (out[j] >= in[i]){ // sai depois que entra
				int aux = out[j] - in[i];

				freq[aux]++;
				if (freq[aux] > frq){
					frq = freq[aux];
					tme = aux;
				}
				else if (freq[aux] == frq)
					tme = min(tme, aux);
			}

	cout<<tme<<endl;		

}