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

int g,c,n;
int p[110], s[110], type[110];
int memo[2][110][20010];
string S;

void dp(){
	for(int i = n - 1; i >= 0; i--){

		for(int gold = 0; gold <= 100; gold++){
			for(int silver = 0; silver <= 20000; silver++){
				int &pdm = memo[0][gold][silver];
				pdm = memo[1][gold][silver];
				if(silver >= s[i]){
					pdm = max(pdm, 1 + memo[1][gold][silver - s[i]]);
				}
				if(type[i] != 1 || (type[i] == 1 && silver < s[i])){
					if(gold >= 1){
						int change = g - s[i];
						int qto;

						if(type[i] == 1)  qto = (change + p[i] - 1)/p[i];
						if(type[i] == -1) qto = (change)/p[i];
						if(type[i] == 0){
							if(change%p[i] >= (p[i]+1)/2) qto = (change + p[i] - 1)/p[i];
							else qto = change/p[i];
						}
						//if(gold == 1 && silver == 0 && i == 0) dbg(change); 
						//if(gold == 1 && silver == 0 && i == 0) dbg(silver + qto*p[i]); 
						pdm = max(pdm, 1 + memo[1][gold - 1][silver + qto*p[i]]);
					}
				}
			}
		}

		for(int gold = 0; gold <= 100; gold++){
			for(int silver = 0; silver <= 20000; silver++){
				memo[1][gold][silver] = memo[0][gold][silver];
			}
		}
	}

}


int main(){

	fastio;

	cin >> g >> c >> n;
	fr(i,n){
		cin >> S >> p[i] >> s[i];
		if(S[S.size() - 1] == 'y') type[i] = -1;
		if(S[S.size() - 1] == 't') type[i] = 0;
		if(S[S.size() - 1] == 's') type[i] = 1;
	}

	dp();
	cout << memo[0][c][0] << endl;

}
