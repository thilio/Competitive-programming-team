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

string s;
string t;
vi ans;
int lps[20020];

void build(){
	int i= 1;
	int j = 0;
	int m = t.size();
	lps[0] = 0;

	while(i<m){
		if(t[j] == t[i]){
			j++;
			lps[i] = j;
			i++;
		}
		else{
			if(j == 0){
				lps[i] = 0;
				i++;
			}
			else j = lps[j-1];
		}
	}
}

void kmp(){
	build();

	int i,j;
	i = j = 0;
	int n = s.size();
	int m = t.size();
	while(i < n){
		if(t[j] == s[i]){
			j++;
			i++;
			if(j==m){
				ans.pb(i - j);
				j = lps[j-1];
			}
		}
		else{
			if(j == 0) i++;
			else{
				j = lps[j-1];
			}
		}
	}
}

int run(){
	ms(lps,0);
	ans.clear();
	//dbg(ans.size());
	kmp();
	//fr(i,ans.size()) dbg(ans[i]);
	int x = ans.size();
	return x;
}

bool caso(){
	getline(cin,t);
	if(t == "EOF") return false;
	int resp = 0;

	getline(cin,s);
	while(s.size() > 0){
		resp += run();
		getline(cin,s);
	}


	int n;
	cin >> n;

	int index = -1;
	getline(cin,t);
	frr(i,n){
		int tent = 0;
		getline(cin,t);


		getline(cin,s);
		while(s.size() > 0){
			tent += run();
			getline(cin,s);
		}

		if(tent > resp){
			resp = tent;
			index = i;
		}
	}

	cout << index << endl;
	return true;

}

int main(){

	fastio;
	while(caso()){};
}
