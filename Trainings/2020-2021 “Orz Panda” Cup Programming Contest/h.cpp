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

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int k;
string s;
int v[MAXN];
int a[MAXN];

void build(int x){
	int i = 0;
	int aux = x;
	while(x){
		if(x%2){
			a[(1 << i)] ^= v[aux];
		}
		i++;
		x/=2;
	}
}

int simula(){
	/*retorna -1 se deu certo ou o bit que tá errado se deu errado*/
	fr(i, (1 << k)) a[i] = 0;
	frr(i, k){
		for(int j = (1 << (i-1)) + 1; j < (1 << i); j++) {
			build(j);
		}
	}

	vector<int> ruim;
	fr(i, k){
		if(a[(1 << i)] != v[(1 << i)]) ruim.pb(i);
	}

	if(ruim.size() == 0) return -1;
	else{
		int x = 0;
		for(auto y: ruim){
			x ^= (1 << y);
		}

		return x;
	}
}

int main(){
	fastio;
	while(cin >> k){
		cin >> s;
		fr(i, (1 << k)) v[i] = s[i] - '0';

		int xor0 = 0;
		frr(i, (1 << k) - 1) xor0 ^= v[i];

		if(v[0] == xor0){
			/*tem 0 ou 2*/
			int val = simula();
			if(val == -1){
				cout << "good" << endl;
			}
			else{
				cout << "broken" << endl;
			}
		}
		else{
			/*tem 1*/
			int val = simula();
			if(val == -1) val = 0;
			cout << "d(" << val << ") is changed" << endl;
		}
	}
}
