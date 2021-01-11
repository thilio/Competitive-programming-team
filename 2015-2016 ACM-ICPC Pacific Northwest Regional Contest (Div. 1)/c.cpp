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

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int n;

bool comp(pair<deque<int>, string> a, pair<deque<int>, string> b){
	int i = a.f.size() - 1;

	while(i >= 0){
		if((a.f)[i] == (b.f)[i]) i--;
		else return (a.f)[i] > (b.f)[i];
	}

	return a.s < b.s;
}

pair<deque<int>, string> p[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin >> n;

	int maximo = 0;

	fr(i, n){
		string a, b;
		cin >> a >> b;
		while(b != "class"){
			if(b[0] == 'u') p[i].f.pb(3);
			else if(b[0] == 'm') p[i].f.pb(2);
			else p[i].f.pb(1);

			cin >> b;
		}

		maximo = max(maximo, (int)p[i].f.size());
		p[i].s = a;
	}

	fr(i, n) while(p[i].f.size() < maximo) p[i].f.push_front(2); 
	/*
	fr(i, n){
		cout << p[i].s << " ";
		for(auto x: p[i].f) cout << x << ' ';
		cout << endl;
	}
	*/
	

	sort(p, p + n, comp);

	fr(i, n){
		fr(j, p[i].s.size() - 1) cout << (p[i].s)[j];
		cout << endl;
	}
}
