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

int main(){

	fastio;

	int ans = 0;

	string s,t;
	getline(cin,s);
	getline(cin,t);

	string alphs;
	string alpht;

	string nums;
	string numt;

	fr(i,s.size()){
		if(s[i] < '0' || s[i] > '9') alphs.pb(s[i]);
		else nums.pb(s[i]);
	}

	fr(i,t.size()){
		if(t[i] < '0' || t[i] > '9') alpht.pb(t[i]);
		else numt.pb(t[i]);
	}

	bool eq = true;

	fr(i,alphs.size()){
		if(alphs[i] != alpht[i]){
			eq = false;
			if(alphs[i] < alpht[i]) ans = -1;
			else ans = 1;
			break;
		}
	}

	if(eq){
		if(nums.size() != numt.size()){
			if(nums.size() < numt.size()) ans = -1;
			else ans = 1;
		}
		else{
			fr(i,nums.size()){
				if(nums[i] != numt[i]){
					if(nums[i] < numt[i]) ans = -1;
					else ans = 1;
					break;
				}
			}
		}
	}

	if(ans == 0) cout << '=';
	if(ans < 0) cout << '<';
	if(ans > 0) cout << '>';
	gnl;
}
