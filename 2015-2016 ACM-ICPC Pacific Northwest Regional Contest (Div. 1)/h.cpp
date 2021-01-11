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

int n, s;
map<pll,string> m;

void mergesort(vector<pll>& t, int type, pair<double,double> a, pair<double,double> b){
	if(t.size() <= 1) return;
	vector<pll> q1;
	vector<pll> q2;
	vector<pll> q3;
	vector<pll> q4;

	double midx = (a.fst + b.fst)/2;
	double midy = (a.snd + b.snd)/2;

	for(auto p: t){
		if (p.fst <= midx && p.snd <= midy) q1.pb(p);
		if (p.fst <= midx && p.snd > midy) q2.pb(p);
		if (p.fst > midx && p.snd > midy) q3.pb(p);
		if (p.fst > midx && p.snd <= midy) q4.pb(p);
	}

	if(type == 0){
		mergesort(q1, 1, a, {midx,midy});
		mergesort(q2, 0, {a.fst,midy}, {midx, b.snd});
		mergesort(q3, 0, {midx,midy}, b);
		mergesort(q4, 3, {midx,a.snd}, {b.fst,midy});
	}

	if(type == 1){
		mergesort(q1, 0, a, {midx,midy});
		mergesort(q2, 2, {a.fst,midy}, {midx, b.snd});
		mergesort(q3, 1, {midx,midy}, b);
		mergesort(q4, 1, {midx,a.snd}, {b.fst,midy});
	}

	if(type == 2){
		mergesort(q1, 2, a, {midx,midy});
		mergesort(q2, 1, {a.fst,midy}, {midx, b.snd});
		mergesort(q3, 3, {midx,midy}, b);
		mergesort(q4, 2, {midx,a.snd}, {b.fst,midy});
	}

	if(type == 3){
		mergesort(q1, 3, a, {midx,midy});
		mergesort(q2, 3, {a.fst,midy}, {midx, b.snd});
		mergesort(q3, 2, {midx,midy}, b);
		mergesort(q4, 0, {midx,a.snd}, {b.fst,midy});
	}

	t.clear();
	if(type == 0){
		for(auto x : q1) t.pb(x);
		for(auto x : q2) t.pb(x);
		for(auto x : q3) t.pb(x);
		for(auto x : q4) t.pb(x);
	}

	if(type == 1){
		for(auto x : q1) t.pb(x);
		for(auto x : q4) t.pb(x);
		for(auto x : q3) t.pb(x);
		for(auto x : q2) t.pb(x);
	}

	if(type == 2){
		for(auto x : q3) t.pb(x);
		for(auto x : q4) t.pb(x);
		for(auto x : q1) t.pb(x);
		for(auto x : q2) t.pb(x);
	}

	if(type == 3){
		for(auto x : q3) t.pb(x);
		for(auto x : q2) t.pb(x);
		for(auto x : q1) t.pb(x);
		for(auto x : q4) t.pb(x);
	}
}
 
int main(){

	fastio;
	cin >> n >> s;
	vector<pll> v;

	fr(i,n){
		int x,y;
		string s;
		cin >> x >> y;
		cin >> s;
		v.pb(mp(x,y));
		m[mp(x,y)] = s;
	}

	pair<double,double> a = {0,0};
	pair<double,double> b = {s,s};

	mergesort(v, 0, a , b);

	for(auto x: v){
		cout << m[x] << endl;
	}

}
