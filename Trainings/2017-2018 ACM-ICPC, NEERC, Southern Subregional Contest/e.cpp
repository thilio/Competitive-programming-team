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
const int MAXN = 1e3 + 10;

int n, m;
string s;

int in[30], hidden[55], freq[30];	


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;
	cin>>s;

	for (int i = 0; i < n; i++)
		if (s[i] == '*')
			hidden[i] = 1;
		else
			in[s[i] - 'a'] = 1;

	// dbg(s);	
	cin>>m;

	int cnt = 0;	
	fr(i, m){
		string t;
		cin>>t;
	
		int ok = 1;
		for (int j = 0; j < n; j++){
			if (hidden[j] and in[t[j] - 'a']) // palavra invalida	
				ok = 0;
			if (!hidden[j] and t[j] != s[j])
				ok = 0;
		}
		
		if (!ok)
			continue;	
		
		cnt++;
		
		int frqn[33];
		memset(frqn, 0, sizeof frqn);


		for (int j = 0; j < n; j++)
			if (hidden[j])
				frqn[t[j] - 'a'] = 1;

		fr(k, 30)
			freq[k] += frqn[k];	
	}	
	// dbg(cnt);
	int ans = 0;
	if (cnt > 0) // alguem é válido
		fr(i, 30)
			if (freq[i] >= cnt)
				ans++;

	cout<<ans<<endl;

}