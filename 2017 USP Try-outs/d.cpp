#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second
#define eps 0.00000000000000001


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

pair<double, double> line[MAXN];
pair<double, double> intersec(pair<double, double> a, pair<double, double> b){
	if(abs(a.f - b.f) < eps){
		return {INF, INF};
	}
	double x = (a.s - b.s)/(a.f - b.f);
	return {x, x*a.f + a.s};
}

int n;
pair<double, double> ord(){
	double maximo = -INF, minimo = INF;
	sort(line + 1, line + n + 1);
	for(int i = 1; i < n; i++){
		pair<double, double> pt = intersec(line[i], line[i+1]);

		if(abs(pt.f - INF) > eps){
			minimo = min(pt.f, minimo);
		}
	}
	frr(i, n) line[i].s *= -1;
	sort(line + 1, line + n + 1);
	frr(i, n) line[i].s *= -1;

	for(int i = 1; i < n; i++){
		pair<double, double> pt = intersec(line[i], line[i+1]);

		if(abs(pt.f - INF) > eps){
			maximo = max(pt.f, maximo);
		}
	}


	return {maximo, minimo};
}

void read(){
	cin >> n;
	frr(i, n) cin >> line[i].f >> line[i].s;
}

int main(){
	fastio;
	cin >> n;
	frr(i, n) cin >> line[i].f >> line[i].s;
	pair<double, double> x = ord();

	frr(i, n){
		line[i].s = -line[i].s/line[i].f;
		line[i].f = (double)1/line[i].f;
	}
	pair<double, double> y = ord();
	cout << fixed; 
	cout << setprecision(8);
	cout << x.s <<" " << y.s << " " << x.f <<" " << y.f << endl;

}
