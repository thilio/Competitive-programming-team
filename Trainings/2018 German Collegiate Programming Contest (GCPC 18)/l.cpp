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

int mat[200][200];
int in[200][200];
bool ans[200][200];

int n,m;

void desmina(int i,int j){
	fr(k,3){
		fr(l,3){
			mat[i - 1 + k][j - 1 + l]--;
		}
	}
}

void construct (int ind){

	if(mat[ind][0] == 1){
		ans[ind+1][1] = true;
		desmina(ind+1,1);
	}

	frr(j,m-3){
		if(mat[ind][j] > mat[ind][j-1]){
			ans[ind+1][j+1] = 1;
			desmina(ind+1,j+1);
		}
	}

}



int main(){

	fastio;

	cin >> n >> m;
	n+= 2; m += 2;

	fr(i,n){
		fr(j,m){
			cin >> in[i][j];
			mat[i][j] = in[i][j];
		}
	}

	fr(i,n-2){
		construct(i);
	}

	fr(i,n){
		fr(j,m){
			if(ans[i][j]){
				fr(k,3){
					fr(l,3){
						in[i - 1 + k][j - 1 + l]--;
					}
				}
			}
		}
	}

	fr(i,n){
		fr(j,m){
			if(in[i][j] != 0){
				cout << "impossible\n";
				return 0;
			}
		}
	}

	frr(i,n-2){
		frr(j,m-2){
			if(ans[i][j]) cout << 'X';
			else cout << '.';
		}
		gnl;
	}







}
