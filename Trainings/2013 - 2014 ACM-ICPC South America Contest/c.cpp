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
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

deque<ll> dig;

void build(ll davez){
	dig.clear();
	while(davez){
		dig.push_front(davez%2);
		davez /= 2;
	}
}

/*
	first é a qtde de uns
	second é a qtde de numeros
*/

pll solve(ll d){
	if(dig.size() == 0) return {(ll)0, (ll)0};
	if(d == dig.size() - 1){
		if(dig[d] == 0) return {(ll)0, (ll)1};
		else return {(ll)1, (ll)2};
	}
	if(dig[d] == 0) {
		pll aux = solve(d + 1);
		//cout << aux.f << " " << aux.s <<' ' << d << endl;
		return aux;
	}
	else {
		pll aux = solve(d + 1);
		aux.f += ((ll)1 << (dig.size() - d - 2))*(dig.size() - d - 1) + aux.s;

		aux.s += ((ll)1 << (dig.size() - d - 1));

		//cout << aux.f << " " << aux.s <<' ' << d << endl;
		return aux;
	}
}

int main(){
	fastio;
	
	ll a, b;

	while(cin >> a >> b){
		build(b);
		pll B = solve(0);
		build(a-1);
		pll A = solve(0);

		//cout << B.f << endl;
		cout << B.f - A.f << endl;
	}
}
