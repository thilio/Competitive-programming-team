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

int grid[110][110];
int mai[110][110];
int dist[110][110];
int posso[100][100];
int n;

int di[4] = {+1,-1,0,0};
int dj[4] = {0,0,+1,-1};

bool is(int i,int j){
	if(i < 0 || i >= n || j < 0 || j >= n) return false;
	if(dist[i][j] != -1) return false;
	if(posso[i][j] == 0) return false;
	return true;
}

int bfs(int mask){
	queue<pii> q;
	ms(dist, -1);
	fr(i,n){
		fr(j,n){
			posso[i][j] = 0;
			if(mai[i][j] && (mask&(1ll << grid[i][j]))) posso[i][j] = 1;
			if(!mai[i][j] && !(mask&(1ll << grid[i][j]))) posso[i][j] = 1;
		}
	}

	if(posso[0][0] == 0) return INF;

	q.push(mp(0,0));
	dist[0][0] = 1;

	while(!q.empty()){
		//olar;
		pii at = q.front();
		q.pop();

		int i = at.fst;
		int j = at.snd;

		fr(k,4){
			if(is(i + di[k], j + dj[k])){
				dist[i + di[k]][j + dj[k]] = dist[i][j] + 1;
				q.push(mp(i + di[k],j + dj[k]));
			}
		}
	}
	if(dist[n-1][n-1] != -1) return dist[n-1][n-1];
	return INF;

}

int main(){

	fastio;
	cin >> n;

	string s;
	getline(cin,s);
	fr(i,n){
		getline(cin,s);
		fr(j,n){
			if(s[j] >= 'A' && s[j] <= 'Z'){
				mai[i][j] = 1;
				s[j] -= 'A';
				s[j] += 'a';

			}
			grid[i][j] = s[j] - 'a';

		}
	}

	int resp = INF;

	for(int mask = 0; mask < (1<< 10); mask++){
		//dbg(mask);
		resp = min(resp,bfs(mask));
	}

	if(resp == INF) resp = -1;

	cout << resp << endl;

}
