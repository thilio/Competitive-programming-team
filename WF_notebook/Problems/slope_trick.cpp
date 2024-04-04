/*
   Title: Slope trick for concave/convex function
   Description: DP optimization
   Complexity: O(nlog(n))
   Solves: Given a vector h, with a[i]/d[i] for cost increase/decrease
   entry i, what is the minimun cost to make it non decreasing?
   
   Solves:  https://codeforces.com/blog/entry/77298
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;

int32_t main(){
	ll T, n, a[MAXN], h[MAXN], d[MAXN];

	cin>>T;

	while (T--){
		cin>>n;
		for (int i = 0; i < n; i++) cin>>h[i];
		for (int i = 0; i < n; i++) cin>>a[i];
		for (int i = 0; i < n; i++) cin>>d[i];
		
		ll slope = 0, linear = 0;
		priority_queue< pair<ll, ll> > pq;

		for (int i = 0; i < n; i++){
			slope += a[i]; 
			linear -= a[i] * h[i];
			pq.push({h[i], a[i] + d[i]});

			while (slope > 0){
				ll pnt, frq;
				tie(pnt, frq) = pq.top();
				pq.pop();
				ll aux = min(slope, frq);
				slope -= aux;
				frq -= aux;
				linear += pnt * aux;
				if (frq > 0)
					pq.push({pnt, frq});
			}
		}

		cout<<linear<<endl;
	}
}