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

pll a[100100];
pll asum[100100];

pair<long double, long double> point[100100];

pll liml[100100];
pll limr[100100];

long double queryx(int l, int r){
	return asum[r].fst - asum[l - 1].fst;
}

long double queryy(int l, int r){
	return asum[r].snd - asum[l - 1].snd;
}

long double new_x(int j){
	return queryx(liml[j].fst, limr[j].fst)/(limr[j].fst - liml[j].fst + 1);
}

long double new_y(int j){
	return queryy(liml[j].snd, limr[j].snd)/(limr[j].snd - liml[j].snd + 1);
}

int main(){

	fastio;

	cout << setprecision(10) << fixed;

	int n;
	cin >> n;

	frr(i, n){
		cin >> a[i].fst >> a[i].snd;
		asum[i].fst = a[i].fst + asum[i - 1].fst;
		asum[i].snd = a[i].snd + asum[i - 1].snd; 
	}

	int t = 1;
	frr(i,n){
		if(a[i].fst > point[t - 1].fst){
			point[t].fst = a[i].fst;
			liml[t].fst = i;
			limr[t].fst = i;
			t++; 
		}
		else{
			int j = t - 1;
			limr[j].fst = i;
			point[j].fst = new_x(j);

			while(j > 0 && point[j].fst < point[j - 1].fst){
				limr[j - 1].fst = limr[j].fst;
				limr[j].fst = -1;
				point[j - 1].fst = new_x(j - 1);
				j--;
				t--;
				
			}

		}
	}

	t = 1;
	frr(i,n){
		if(a[i].snd > point[t - 1].snd){
			point[t].snd = a[i].snd;
			liml[t].snd = i;
			limr[t].snd = i;
			t++; 
		}
		else{
			int j = t - 1;
			limr[j].snd = i;
			point[j].snd = new_y(j);

			while(j > 0 && point[j].snd < point[j - 1].snd){
				limr[j - 1].snd = limr[j].snd;
				limr[j].snd = -1;
				point[j - 1].snd = new_y(j - 1);
				j--;
				t--;
				
			}

		}
	}

	int i = 1;
	int j = 1;
	long double ans = 0;

	while(j <= n){
		if(j > limr[i].fst) i++;
		ans += (a[j].fst - point[i].fst)*(a[j].fst - point[i].fst);
		j++;
	}

	j = 1;
	i = 1;
	while(j <= n){
		if(j > limr[i].snd) i++;
		ans += (a[j].snd - point[i].snd)*(a[j].snd - point[i].snd);
		j++;
	}

	cout << ans << endl;


}
