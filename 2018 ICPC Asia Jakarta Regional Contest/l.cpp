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

bool comp(string& a, string& b){ // true se a < b;
	ll la = 0;
	ll lb = 0;

	for(int i = 0; i < a.size(); i++){
		la *= 2;
		la += a[i] - '0';
	}

	for(int i = 0; i < b.size(); i++){
		lb *= 2;
		lb += b[i] - '0';
	}

	//dbg(la);
	//dbg(lb);

	return la < lb;
}

int um(string &a){
	for(int i = 1; i < a.size(); i++) if(a[i] == '1') return i;
	return -1;
}

int main(){

	fastio;

	ll x;
	string s;
	string k;

	cin >> x;
	cin >> s;

	while(x != 0){
		if(x%2) k.pb('1');
		else k.pb('0');
		x /= 2;
	}

	reverse(all(k));

//	dbg(k);
	int bit = 0;

	while(comp(k, s)){
		bit++;
		int pos = um(s);
		if(pos != -1){
			s.erase(s.begin() + pos);
		}
		else{
			s.pop_back();
		}
	}

	cout << bit << endl;

}
