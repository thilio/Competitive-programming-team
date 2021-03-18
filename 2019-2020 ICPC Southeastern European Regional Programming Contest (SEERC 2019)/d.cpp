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

string s, ans;
int n, freq[400];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>s;

	n = s.size();

	int mx = 0, mxf = 'a';
	for (auto x : s){
		freq[x]++;
		if (mx < freq[x]){
			mx = freq[x];
			mxf = x;
		}
	}

	if (mx <= n/2){
		cout<<"YES"<<endl;
		sort(all(s));
		cout<<s<<endl;
		return 0;
	}

	int ndif = 0;
	for (int i = 'a'; i <= 'z'; i++)
		ndif += freq[i] > 0;

	if (ndif > 2 or mx < n - 2){
		fr(i, n/2){	
			ans.pb((char) mxf);
			freq[mxf]--;	
		}	
		
		for (int i = 'a'; i <= 'z'; i++)
			if (i != mxf and freq[i] > 0){
				ans.pb((char) i);
				freq[i]--;
				break;
			}
			
		while (freq[mxf] > 0){
			ans.pb((char) mxf);
			freq[mxf]--;
		}
		for (int i = 'a'; i <= 'z'; i++)
			while (freq[i] > 0){
				ans.pb((char) i);
				freq[i]--;
			}
		
		cout<<"YES"<<endl;	
		cout<<ans<<endl;
	}
	else
		cout<<"NO"<<endl;
}