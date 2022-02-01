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

char v[4] = {'N','E', 'S', 'W'};
vi ans; 

char next(char r){
	int j = 0;
	fr(i,4){
		if(v[i] == r) j = i;
	}
	j++;
	j %= 4;
	return (v[j]);
}

void print(){
	cout << ans.size() << endl;
	for(auto x : ans){
		if(x == -1) cout << 'D' << endl;
		else cout << 'A' << ' ' << x << endl;
	}
}

int main(){

	fastio;
	int xi,yi,xf,yf;

	cin >> xi >> yi;;
	char c;
	cin >> c;
	if(c == 'O') c = 'W';
	cin >> xf >> yf;

	if(xi == xf){
		if(yi > yf){
			while(c != 'S'){
				c = next(c);
				ans.pb(-1);				
			}
			ans.pb(abs(yi - yf));
		}
		if(yf > yi){
			while(c != 'N'){
				c = next(c);
				ans.pb(-1);				
			}
			ans.pb(abs(yi - yf));
		}
		print();
		return 0;
	}
	if(yi == yf){
		if(xi > xf){
			while(c != 'W'){
				c = next(c);
				ans.pb(-1);				
			}
			ans.pb(abs(xi - xf));
		}
		if(xf > xi){
			while(c != 'E'){
				c = next(c);
				ans.pb(-1);				
			}
			ans.pb(abs(xi - xf));
		}
		print();
		return 0;
	}

	if(xf > xi && yf > yi){
		if(c == 'E'){
			ans.pb(abs(xf - xi));
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(abs(yf - yi));
		}
		else{
			while(c != 'N'){
				c = next(c);
				ans.pb(-1);
			}
			ans.pb(abs(yf - yi));
			ans.pb(-1);
			ans.pb(abs(xf - xi));
		}
	}
	else if(xf < xi && yf > yi){
		if(c == 'N'){
			ans.pb(abs(yf - yi));
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(abs(xi - xf));
		}
		else{
			while(c != 'W'){
				c = next(c);
				ans.pb(-1);
			}
			ans.pb(abs(xi - xf));
			ans.pb(-1);
			ans.pb(abs(yf - yi));
		}
	}
	else if(xf < xi && yf < yi){
		if(c == 'W'){
			ans.pb(abs(xf - xi));
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(abs(yi - yf));
		}
		else{
			while(c != 'S'){
				c = next(c);
				ans.pb(-1);
			}
			ans.pb(abs(yi - yf));
			ans.pb(-1);
			ans.pb(abs(xf - xi));
		}
	}
	else if(xf > xi && yf < yi){
		if(c == 'S'){
			ans.pb(abs(yf - yi));
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(-1);
			ans.pb(abs(xi - xf));
		}
		else{
			while(c != 'E'){
				c = next(c);
				ans.pb(-1);
			}
			ans.pb(abs(xi - xf));
			ans.pb(-1);
			ans.pb(abs(yf - yi));
		}
	}

	print();

}
