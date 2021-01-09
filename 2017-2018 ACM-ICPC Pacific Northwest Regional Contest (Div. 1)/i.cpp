#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

typedef vector< tuple<ll, ll, ll> > viii;

bool comp(viii &a, viii &b){
	if (a.size() != b.size())
		return true;
	ll x, y, z, xx, yy, zz;
	fr(i, a.size()){
		tie(x, y, z) = a[i];
		tie(xx, yy, zz) = b[i];
		if (x != xx or y != yy or z != zz)
			return true;
	}
	return false;	 
}

void solve(viii &v){
	for (int i = 1; i < v.size(); i++)
		for (int j = i; j > 0; j--){
			if (get<0>(v[j - 1]) == 0 and get<0>(v[j]) == 0 and get<1>(v[j - 1]) <= get<1>(v[j])){
				swap(v[j - 1], v[j]);
				get<1>(v[j - 1])++;
			}
			else if (get<0>(v[j - 1]) == 1 and get<0>(v[j]) == 1 and get<1>(v[j - 1]) >= get<1>(v[j])){
				swap(v[j - 1], v[j]);
				get<1>(v[j])++;
			}
			else if (get<0>(v[j - 1]) == 1 and get<0>(v[j]) == 0){
				if (get<1>(v[j - 1]) < get<1>(v[j])){
					swap(v[j - 1], v[j]);
				 	get<1>(v[j - 1])--;
				}
				else if (get<1>(v[j - 1]) == get<1>(v[j])){
					v.erase(v.begin() + j - 1, v.begin() + j + 1);//[)
					i -= 2;
					break;
				}
				else{
					swap(v[j - 1], v[j]);
					get<1>(v[j])--;
				}
			}
		}
}


int32_t main(){
	fastio;

	viii a, b;
	
	ll p;
	char c, d;
	cin>>c;
	while (c != 'E'){
		if (c == 'D'){
			cin>>p;
			a.pb({0, p, 0});
		}
		else{
			cin>>p>>d;
			a.pb({1, p, d});
		}
		cin>>c;
	}

	cin>>c;
	while (c != 'E'){
		if (c == 'D'){
			cin>>p;
			b.pb({0, p, 0});
		}
		else{
			cin>>p>>d;
			b.pb({1, p, d});
		}
		cin>>c;
	}

	solve(a);
	solve(b);

	cout<<comp(a, b)<<endl;
}