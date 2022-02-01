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

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MAXS 500
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

ll dp[30][MAXS][10];
ll tot[MAXS];
ll N, K;
vector<ll> n, k;
ll dpAux[30][MAXS];


void solve(){
	/*Caso base*/
	for(ll i = 0; i < 10; i++){ 
		dp[0][i][i] = 1;
	}
	
	for(ll d = 1; d < n.size() - 1; d++){
		for(ll sum = 0; sum < MAXS; sum++){
			for(ll lead = 0; lead < 10; lead++){
				dp[d][sum][0] += dp[d-1][sum][lead]; 
			}
			for(ll lead = 1; lead < 10; lead++){
				dp[d][sum + lead][lead] += dp[d][sum][0];
			}
		}
	}
	ll D = n.size() - 1;
	for(ll sum = 0; sum < MAXS; sum++){
		for(ll lead = 0; lead < 10; lead++){
			dp[D][sum][0] += dp[D-1][sum][lead]; 
		}
		for(ll lead = 1; lead < n.back(); lead++){
			dp[D][sum + lead][lead] += dp[D][sum][0];
		}
	}

	for(ll i = 0; i <= n[0]; i++) dpAux[0][i] = 1;
	
	for(ll d = 1; d < n.size() - 1; d++){
		for(ll sum = 0; sum < MAXS; sum++){
			dpAux[d][sum + n[d]] += dpAux[d-1][sum];
			for(ll lead = 0; lead < n[d]; lead++){
				dpAux[d][sum + lead] += dp[d][sum + lead][lead];
			}
		}
	}
	for(ll sum = 0; sum < MAXS; sum++){
		dp[D][sum + n[D]][n[D]] = dpAux[D - 1][sum];
	}
}

/*
ll bf[10][6400][10], maxsum = 0;
void brute(ll x){
	ll ind = 0, sum = 0, last = 0, aux = x;
	while(x){
		sum += x%10;
		last = x%10;
		x/=10;
		ind++;
	}
	bf[ind-1][sum][last]++;
	maxsum = max(maxsum, sum);
	for(ll i = ind ; i < n.size(); i++) {
		bf[i][sum][0]++;
	}
}
*/

void build(){
	ll auxN = N;
	while(N){
		n.pb(N%10);
		N/=10;
	}
	//for(ll i = 1; i <= auxN; i++) brute(i);
	while(K){
		k.pb(K%10);
		K/=10;
	}
	solve();
	/*
	for(ll i = 0; i < n.size(); i++){
		for(ll lead = 0; lead < 10; lead++){
			for(ll sum = 1; sum < maxsum; sum++){
				if(dp[i][sum][lead] != bf[i][sum][lead])
					cout << i <<" " << lead <<' ' << sum << " | " << dp[i][sum][lead] << " " << bf[i][sum][lead] << endl;
			}	
		}
	}
	*/
	for(ll lead = 0; lead <= n.back(); lead++){
		for(ll sum = 0; sum < MAXS; sum++){
			tot[sum] += dp[n.size() - 1][sum][lead];
		}
	}
}

ll getPosition(){
	ll pos = 0;
	ll sumK = 0;
	for(auto x: k) sumK += x;
	for(ll i = 1; i < sumK; i++){
		pos += tot[i];
	}

	ll aux = 0;
	for(ll i = k.size() - 1; i >= 0; i--){
		for(ll j = 0; j < k[i]; j++){
			pos += dp[i][sumK - aux][j];
		}
		aux += k[i];
	}
	return pos + 1;
}

ll auxK;
ll getK(){
	ll sum;
	for(sum = 1; auxK - tot[sum] > 0; sum++) auxK -= tot[sum];
	//cout << sum << " " << auxK << endl;

	deque<ll> ans;
	for(ll d = n.size() - 1; d >= 0; d--){
		if(dp[d][sum][0] >= auxK) ans.pb(0);
		else{
			for(ll lead = 0; lead < 10; lead++){
				if(auxK > dp[d][sum][lead])
					auxK -= dp[d][sum][lead];
				else{
					ans.pb(lead);	
					sum -= lead;
					break;
				}
			}
			//cout << auxK <<" | " << d << endl;
		}
	}
	ll ret = 0;
	for(auto x: ans){
		ret *= 10;
		ret += x;
	}
	return ret;
}

int main(){
	fastio;
	cin >> N >> K;
	if(N < 10){
		cout << K << " " << K << endl;
		return 0;
	}
	auxK = K;
	build();
	cout << getPosition() << " " << getK() << endl;
}
