#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 510
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int backrow(int n, int A[][MAXN], int b[], int trans){
	int i, j;
	if(trans){
		for(i = n-1; i >= 0; i--){
			if(A[i][i] == 0) return -1;

			for(j = 0; j < i; j++){
				b[j] = (b[j] + A[i][j*b[i]])%2;
			}
		}
	}
	else{
		for(i = n-1; i >= 0; i--){
			for(j = i + 1; j < n; j++){
				b[i] = (b[i] + A[i][j]*b[j])%2;
			}

			if(A[i][i] == 0) return -1;
		}
	}

	return 0;
}

int lurow(int n, int A[][MAXN], int p[]){
	for(int k = 0; k < n-1; k++){
		int m = k;
		for(int i = k + 1; i < n; i++){
			if(A[i][k] > A[m][k]){
				m = i;
			}
		}

		if(A[m][k] == 0) return -1;

		p[k] = m;

		if(m != k){
			for(int i = 0; i < n; i++){
				swap(A[m][i], A[k][i]);
			}
		}

		for(int i = k + 1; i < n; i++){
			int aux = A[i][k];
			for(int j = k + 1; j < n; j++){
				A[i][j] = (A[i][j] + aux*A[k][j])%2;
			}
		}
	}

	if(A[n-1][n-1] == 0) return -1;
	p[n-1] = n-1;
	return 0;
}

int ssrow(int n, int A[][MAXN], int p[], int b[]){
	for(int i = 0; i < n; i++){
		swap(b[i], b[p[i]]);
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			b[i] = (b[i] + A[i][j]*b[j])%2;
		}
	}

	if(backrow(n, A, b, 0) == -1){
		cout << -1 << endl;

		exit (0);
	}

	return 0;
}

int A[MAXN][MAXN], p[MAXN], b[MAXN];
int n;

int main(){
	fastio;
	cin >> n;
	fr(i, n) fr(j, n) cin >> A[j][i];

	if(lurow(n, A, p) == -1){
		cout << -1 << endl;
		exit (0);
	}
/*
	fr(i, n){
		fr(j, n) cout << A[i][j] << " ";
		cout << endl;
	}
*/
	fr(i, n){

		fr(j, n) b[j] = 0;
		b[i] = 1;

		if(ssrow(n, A, p, b)){
			cout << -1 << endl;
			exit(0);
		}

		fr(j, n) if(b[j]) cout << j + 1 << " ";
		cout << endl;
	}
}
