#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000000
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100
	
ll n, m;

vector<ll> vecMaskVert;

bool checkDomVert(ll mask){
	ll a[10];
	fr(i, n+1) a[i] = 0;
	fr(i, n){
		if(mask%2 == 0) a[i] = 0;
		else a[i] = 1;
		mask/=2;
	}

	fr(i, n){
		if(a[i] == 1){
			if(a[i+1] == 0) return 0;
			else a[i] = a[i+1] = 0;
		}
	}

	return 1;
}

matrix operator *(matrix a, matrix b){
    matrix ans((1 << n), vector<ll>((1 << n)));

    fr(i, (1 << n)){
        fr(j, (1 << n)){
            ans[i][j] = 0;

            fr(k, (1 << n)) ans[i][j] = (a[i][k]*b[k][j] + ans[i][j])%MOD;
        }
    }

    return ans;
}

matrix fastxp(matrix a, ll e){
    if(e == 1) return a;

    matrix b = fastxp(a, e/2);

    b = b*b;
    if(e%2 == 1) b=b*a;

    return b;
}

void build(matrix & a){
	fr(mask, (1 << n)){
		for(auto maskVert : vecMaskVert){
			fr(maskHor, (1 << n)){
				if(((maskHor & mask) == (ll)0) && ((maskHor & maskVert) == (ll)0)){
					a[(maskHor | maskVert)][mask]++;
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;

	// Ve as mascaras horizontais que podem ser dominós
	fr(i, (1 << n)) if(checkDomVert(i)) vecMaskVert.pb(i);

	matrix a((1 << n), vector<ll>((1 << n)))	;
	fr(i, (1 << n)){
		fr(j, (1 << n)) a[i][j] = 0;	
	}
	build(a);

	matrix ans = fastxp(a, m);
	
	ll tot = 0;
	fr(i, (1 << n)) tot = (ans[i][(1 << n) - 1] + tot)%MOD;
	cout << tot << endl;
}
