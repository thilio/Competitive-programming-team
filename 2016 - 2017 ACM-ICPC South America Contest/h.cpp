#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, k;

	cin>>n>>k;

	priority_queue<int, vi, greater<int>> pq;

	int credit = 0, p, sum = 0;
	fr(i, n){
		cin>>p;
		sum += p;

		if (credit == k){ // free
			pq.push(p);
			credit = 0;
		}
		else{
			credit++;
			if (!pq.empty() and pq.top() < p){
				pq.pop();
				pq.push(p);
			}
		}
	}

	while (!pq.empty()){
		sum -= pq.top();
		pq.pop();
	}

	cout<<sum<<endl;
}