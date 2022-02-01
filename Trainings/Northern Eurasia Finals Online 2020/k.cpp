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

int p[1010];
int t[1010][3];


int main(){

	fastio;

	int n;
	cin >> n;

	int index = 0;
	p[index] = INF;

	frr(i, n){
		cin >> p[i];
		string s;
		cin >> s;

		for(auto x: s){
			if(x == '0') t[i][0]++;
			if(x == '1') t[i][1]++;
			if(x == '2') t[i][2]++;
		}

		if(t[i][0] >= 1 && t[i][1] >= 1 && t[i][2] >= 2){
			if(p[i] < p[index]) index = i;
		}
	}

	cout << index << endl;






}
