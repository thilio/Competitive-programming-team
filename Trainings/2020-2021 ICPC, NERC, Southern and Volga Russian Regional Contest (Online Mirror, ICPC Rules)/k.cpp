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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n;
string s;
vii v;

pii move(pii pos, int iter){
	if (s[iter] == 'D') return {pos.fst, pos.snd - 1};
	if (s[iter] == 'U') return {pos.fst, pos.snd + 1};
	if (s[iter] == 'L') return {pos.fst - 1, pos.snd};
	return {pos.fst + 1, pos.snd};
}

bool check(int idx){
	pii pos = {0, 0};

	pii block = v[idx], aux;

	for (int i = 0; i < n; i++){
		aux = move(pos, i);
		if (aux != block)
			pos = aux;
	}

	return (pos == make_pair(0, 0));

}

void solve(){
	v.clear();
	cin>>s;

	n = s.size();

	pii pos = {0, 0};
	for (int i = 0; i < n; i++){
		pos = move(pos, i);
		v.pb(pos);	
	}

	for (int i = 0; i < n; i++)
		if (check(i)){
			cout<<v[i].fst<<' '<<v[i].snd<<endl;
			return;
		}
	
	cout<<0<<' '<<0<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}