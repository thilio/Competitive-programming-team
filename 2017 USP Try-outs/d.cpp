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
typedef long double ld;
typedef pair<ld,ld> pld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;
const ld EPS = 1e-18;

vector<pair<ld,ld>> v;

bool is(ld a){
	if(a < EPS && a > -EPS) return true;
	return false;
}

bool get(pld a,pld b, pld &c){
	if(is(a.fst - b.fst)) return false;
	c.fst = (b.snd - a.snd)/(a.fst - b.fst);
	c.snd = a.fst*c.fst + a.snd;
	return true;
}

bool comp1(pld a, pld b){
	if(!is(a.fst - b.fst)){
		if(a.fst < b.fst) return true;
		else return false;
	}
	return a.snd < b.snd;
}

bool comp2(pld a, pld b){
	if(!is(a.fst - b.fst)){
		if(a.fst < b.fst) return false;
		return true;
	}
	return a.snd < b.snd;
}


int main(){

	fastio;

	cout << setprecision(9) << fixed;

	int n;
	cin >> n;
	v.resize(n);
	fr(i,n){ 
		cin >> v[i].fst >> v[i].snd;
		v[i].snd = -v[i].snd;
	}

	pld aux;

	ld xmax,xmin,ymax,ymin;
	bool xma,xmi,yma,ymi;
	xma = xmi = yma = ymi = false;

	sort(all(v),comp1);
	for(int i = 0; i < n - 1; i++){
		if(xma == false){
			if(get(v[i],v[i + 1], aux)){
				xma = true;
				xmax = aux.fst;
			}
		}
		else{
			if(get(v[i],v[i + 1], aux)){
				xmax = max(xmax, aux.fst);
			}

		}
	}

	sort(all(v),comp2);
	for(int i = 0; i < n - 1; i++){
		if(xmi == false){
			if(get(v[i],v[i + 1], aux)){
				xmi = true;
				xmin = aux.fst;
			}
		}
		else{
			if(get(v[i],v[i + 1], aux)){
				xmin = min(xmin, aux.fst);
			}
		}
	}

	fr(i,v.size()){
		v[i].fst /= (v[i].fst)*(v[i].fst);
		v[i].snd = -v[i].snd*v[i].fst;
	}

	sort(all(v),comp1);
	for(int i = 0; i < n - 1; i++){
		if(yma == false){
			if(get(v[i],v[i + 1], aux)){
				yma = true;
				ymax = aux.fst;
			}
		}
		else{
			if(get(v[i],v[i + 1], aux)){
				ymax = max(ymax, aux.fst);
			}

		}
	}

	sort(all(v),comp2);
	for(int i = 0; i < n - 1; i++){
		if(ymi == false){
			if(get(v[i],v[i + 1], aux)){
				ymi = true;
				ymin = aux.fst;
			}
		}
		else{
			if(get(v[i],v[i + 1], aux)){
				ymin = min(ymin, aux.fst);
			}
		}
	}

	cout << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << endl;





}
