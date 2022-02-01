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

int d1[MAXN], d2[MAXN];
int pal[2 * MAXN];

void manacher(string &s){
	int tam = s.size();
	for (int i = 0, l = 0, r = -1; i < tam; i++){
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    	while (0 <= i - k and i + k < tam and s[i - k] == s[i + k]) {
    	    k++;
    	}
    	d1[i] = k--;
    	if (i + k > r) {
    	    l = i - k;
		    r = i + k;
		}
	}

	for (int i = 0, l = 0, r = -1; i < tam; i++) {
	    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	    while (0 <= i - k - 1 and i + k < tam and s[i - k - 1] == s[i + k]) {
	        k++;
	    }
	    d2[i] = k--;
	    if (i + k > r) {
	        l = i - k - 1;
    		r = i + k ;
    	}
	}

	for (int i = 0; i < tam; i++)
		pal[2 * i] = 2 * d1[i] - 1;
	for (int i = 0; i < tam - 1; i++)
		pal[2 * i + 1] = 2 * d2[i + 1];
}

ll h[MAXN];

void solve(){
	int k;
 	string s;
  
 	cin>>k;
	cin>>s;

	int n = s.size();
	for (int i = 0; i < n + 5; i++){
		d1[i] = d2[i] = 0;
		pal[i] = pal[2 * i] = pal[2 * i + 1] = 0;
	}

	manacher(s);

	fr(i, n)
		h[i] = n;

	int p, q;
	p = q = 0;
  
	while (p < n){
		while (q < p)
			q++;

		bool ok = 0;
		while (!ok and q < n){    
		
			if (k % 2){
				if (pal[2 * q] >= k and q - k/2 >= p){
					h[p] = min<ll>(h[p], q + k/2);
					ok = 1;
				}
				if (pal[2 * q + 1] >= k and q - (k - 1)/2 >= p){ /// sjkasjk[q q + 1]iiijsdw
					h[p] = min<ll>(h[p], q + (k + 1)/2);
					ok = 1;
				}
			}
			else{
				if (pal[2 * q] >= k and q - k/2 >= p){
					h[p] = min<ll>(h[p], q + k/2);
					ok = 1;
				}
				if (pal[2 * q + 1] >= k and q - (k - 1)/2 >= p){ /// sjkasjk[q q + 1]iiijsdw
					h[p] = min<ll>(h[p], q + k/2);
					ok = 1;
				}
			}
		
			if (!ok) q++;
		}
		p++;
	}  
  
  	ll ans = 0;
	
	fr(i, n)
		ans += h[i] - i;	

	cout<<ans<<endl;	
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}