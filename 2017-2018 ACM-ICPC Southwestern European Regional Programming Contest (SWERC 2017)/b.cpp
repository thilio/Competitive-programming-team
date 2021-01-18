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

#define MAXN 2001
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
ll x, y, n, d;
ll mapa[MAXN][MAXN];
ll m[MAXN][MAXN];
ll ans[100010];
vector<pii> valores[MAXN];
vector<pii> query[MAXN];

class BIT{
    public:
        ll bit[MAXN];
        ll n;

        void update(ll i, ll val){
        	while(i <= n){
                bit[i] += val;
                i += i & (-i);
            }
        }

        ll queryBIT(ll i){
            ll sum = 0;
           	while(i > 0){
                sum += bit[i];
                i -= i & (-i);
            }

            return sum;
        }
        ll query(ll i){
        	return queryBIT(x) - queryBIT(i-1);
        }
};

BIT b0, b1;

class DSU{
public:
	ll sz[MAXN], pai[MAXN], apareceu[MAXN];
	ll find(ll davez){
		if(davez == pai[davez]) return davez;
		else return pai[davez] = find(pai[davez]);
	}

	void join(ll A, ll B){
		A = find(A), B = find(B);
		if(A == B) return;
		if(sz[A] < sz[B]) swap(A, B);
		sz[A] += sz[B];
		pai[B] = A;
	}

	void update(ll pos){
		apareceu[pos] = 1;
		if(pos < x-1 && apareceu[pos + 1]){
      ll f = find(pos+1);
			b0.update(sz[f], -1);
			b1.update(sz[f], -sz[f]);
			join(pos, pos+1);
		}
		
		if(pos > 0 && apareceu[pos - 1]){
      ll f = find(pos-1);
			b0.update(sz[f], -1);
			b1.update(sz[f], -sz[f]);
			join(pos, pos-1);
		}
    
    ll f = find(pos);
		b0.update(sz[f], 1);
		b1.update(sz[f], sz[f]);
	}
};

static DSU linha[MAXN];

void read(){
	scanf("%lld %lld %lld %lld", &x, &y, &n, &d);
	fr(i, n){
		ll p[2], q[2];
		scanf("%lld %lld %lld %lld", &p[0], &p[1], &q[0], &q[1]);

		for(ll j = p[0]; j < p[1]; j++){
			for(ll k = q[0]; k < q[1]; k++) mapa[k][j] = 1;
		}
	}
	fr(i, d){
		ll p, q;
		scanf("%lld %lld", &p, &q);
		query[q].pb({p, i});
	}

	/*Precomputar m*/

	for(ll i = y-1; i >= 0; i--){
		for(ll coluna = 0; coluna  < x; coluna++){
	    	if(mapa[i][coluna] == 0) 
	        m[i][coluna] = m[i+1][coluna]+1;
	    	else m[i][coluna] = 0;
   		}
	}

	fr(i, y){
		fr(j, x) valores[m[i][j]].pb({i, j});
	}

	/*Inicializar as DSU's e a BIT*/
	b0.n = x;
    b1.n = x;
    
    fr(i, x+1) b0.bit[i] = 0, b1.bit[i] = 0;
    fr(i, y){
    	fr(j, x) {
    		linha[i].sz[j] = 1;
    		linha[i].pai[j] = j;
    		linha[i].apareceu[j] = 0;
    	}
   	}
}
int main(){
	//fastio;
	read();

	for(ll i = y; i >= 1; i--){
		//Coloca os caras na DSU
		for(auto casa : valores[i]){
			linha[casa.f].update(casa.s);
		}

		//Resolvo as queries	
		for(auto q: query[i]){
			ans[q.s] += b1.query(q.f) - (q.f-1)*b0.query(q.f);
		}
	}

	fr(i, d) printf("%lld\n", ans[i]);
}

