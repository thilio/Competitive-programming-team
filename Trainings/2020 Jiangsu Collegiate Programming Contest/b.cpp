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

ll h[100100], a[100100], d[100100];
int n;

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		cin >> n;
		fr(i, n) cin >> h[i];
		fr(i, n) cin >> a[i];
		fr(i, n) cin >> d[i];

		ll slope, linear;

		slope = linear = 0;
		priority_queue<pll> pq;
		fr(i, n){
			slope += a[i];
			linear -= a[i]*h[i];

			pq.push({h[i], a[i] + d[i]});

			while(slope > 0){
				ll pt, qts;
				tie(pt, qts) = pq.top();
				pq.pop();

				if(qts <= slope){
					slope -= qts;
					linear += pt*qts;
				}
				else{
					qts -= slope;
					pq.push({pt, qts});
					linear += pt*slope;
					slope = 0;	
				}
			}
		}

		cout << linear << endl;
	}

}
