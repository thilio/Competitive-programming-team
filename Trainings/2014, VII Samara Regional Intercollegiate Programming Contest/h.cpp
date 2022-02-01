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

int n, m;
string s, d = "desmond";

bool check(int l, int r){
	for (int i = l; i < min(r + 1, n); i++){
		int p = 0;
		while (s[i + p] == d[p] and p < 7 and (i + p) < n)
			p++;

		if (p == 7)
			return true;
	}

	return false;
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>s;

	n = s.size();

	cin>>m;

	if (check(0, n)){
		cout<<"I love you, Desmond!"<<endl;
		cout<<0<<endl;
		return 0;
	}

	char c;
	int p;
	frr(i, m){
		cin>>p>>c;

		s[p - 1] = c;

		if (check(max(0, p - 7), min(n - 1, p + 7))){
			cout<<"I love you, Desmond!"<<endl;
			cout<<i<<endl;
			return 0;
		}
	}

	cout<<"Goodbye, my love!"<<endl;
}	