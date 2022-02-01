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
int n;
string s;
vi pos;
int ast[1000*1001];

int query(int l,int r){
	r = min(r, n -1);
	if(l > r) return 0;
	if(l == 0) return ast[r];
	else return ast[r] - ast[l - 1];
}

void corner(){
	int q1,t1;
	int q2,t2;
	q1 = q2 = t1 = t2 = 0;

	for(int i = pos[0];i < n; i++){
		if(s[i] == '*'){
			q1++;
			t1 = i - pos[0];
		}
	}

	for(int i = pos[0]; i >= 0; i--){
		if(s[i] == '*'){
			q2++;
			t2 = pos[0] - i;
		}
	}

	if(q1 != q2){
		if(q1 > q2){
			cout << q1 << ' ' << t1 << endl;
		}
		else{
			cout << q2 << ' ' << t2 << endl;
		}
	}
	else{
		if(t1 <= t2) cout << q1 << ' ' << t1 << endl;
		else cout << q2 << ' ' << t2 << endl;
	}
}

int memo[1000*1001];

bool ok(int tempo){
	int sz = pos.size();

	for(int i = 0; i < sz; i++){
		if(query(memo[i], pos[i] - tempo - 1) > 0) return false;

		if(query(memo[i],pos[i]) > 0){
			memo[i + 1] = pos[i] + 1;
			if(i > 0 && query(memo[i - 1], pos[i] - tempo - 1) == 0)
				memo[i + 1] = max(memo[i + 1], pos[i - 1] + tempo + 1);
		}
		else{
			memo[i + 1] = pos[i] + tempo + 1;
		}

	}

	return (query(memo[sz], n - 1) == 0);
}

int main(){

	fastio;

	cin >> n;
	getline(cin,s);
	getline(cin,s);

	fr(i,s.size()){
		if(s[i] == 'P') pos.pb(i);
		if(s[i] == '*') ast[i]++;
	}

	fr(i,n){
		if(i != 0) ast[i] += ast[i - 1];
	}

	if(pos.size() == 1){
		corner();
	}
	else{
		int l = 0;
		int r = 1000*1000;
		int best = -1;
		while(l <= r){
			int m = (l + r)/2;
			if(ok(m)){
				r = m - 1;
				best = m;
			}
			else{
				l = m + 1;
			}
		}

		cout << ast[n - 1] << ' ' << best << endl;
	}





}