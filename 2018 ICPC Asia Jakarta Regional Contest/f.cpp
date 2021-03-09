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

ll n,M;
vector<ll> A, B;
vector<ll> deltab;
vector<ll> ans;
int mx[100100];

bool ganhei = false;

void read(){
	cin >> n >> M;
	ll x = 0;

	fr(i,n){
		cin >> x;
		A.pb(x);
	}

	fr(i,n){
		cin >> x;
		B.pb(x);
		deltab.pb(x);
	}

	for(int i = 1; i < n; i++){
		A[i] += A[i - 1];
		B[i] += B[i - 1];
	}

	while(A.size() > 0 && A[A.size() - 1] > M) A.pop_back();

	while(B.size() > 0 && (B.size() > A.size() || B[B.size() - 1] > M)) B.pop_back();

	if(A.size() > B.size()) ganhei = true;

	int id = B.size() - 1;
	for(int i = B.size() - 1; i >= 0; i--){
		if(deltab[i] > deltab[id]){
			id = i;
		}
		mx[i] = id;
	}
}

int main(){

	fastio;

	read();

	if(ganhei){
		cout << 0 << endl;
		gnl;
		return 0;
	}

	if(A.size() == 0){
		cout << -1 << endl;
		return 0;
	}

	int j = 0;
	int i = 0;
	int b = 0;
	ll delta = 0;

	while(j < B.size()){
		while(j != mx[j]) j++;
		
		while(i < A.size() && A[i] <= B[j] + delta){
			i++;
			b++;
			ans.pb(B[j] + delta);
			delta += deltab[j];
		}
		j++;
	}

	if(B[B.size() - 1] + delta <= M){
		cout << -1 << endl;
	}

	else{
		while(ans.size() && ans[ans.size() - 1] > M) ans.pop_back();
		cout << ans.size() << endl;
		for(auto x: ans) cout << x << ' ';
		gnl;
	}

}
