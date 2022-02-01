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

int state;
int last = 0;

void change(){cout << 'S' << endl;}
void left(){cout << 'L' << endl;}
void right(){cout << 'R' << endl;}
void ans(int n){cout << n << endl;}
void get(){cin >> state;}


void go(int x){
	fr(i, x){
		right();
		get();
		if(state == 1){
			change();
			last = i + 1;
		}
	}
}

void back(int x){
	fr(i, x){
		left();
		get();
	}
}

int main(){

	fastio;

	cin >> state;

	if(state == 0){
		change();
	}

	int i = 0;

	while(true){
		go(1 << i);
		back(1 << i);
		if(state == 0){
			break;
		}
		else{
			i++;
		}
	}

	cout << last << endl;

}
