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

int freqa[26];
int freqb[26];

int main(){

	fastio;

	string a, b;
	getline(cin, a);
	getline(cin, b);

	stringstream s (a);
	stringstream t (b);

	while(s >> a){
		t >> b;

		for(auto x: a){
			freqa[x - 'a']++;
		}
		for(auto x : b){
			freqb[x - 'a']++;
		}
		
	}

	fr(i, 26){
		if(freqa[i] != freqb[i]) cout << (char) ('a' + i);
	}
	gnl;
}
