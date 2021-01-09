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

int MaxLexSubstr(string &s){
    int n = s.length(), i = 0, j = 1, k = 0;
    while (j + k < n){
        if (s[i+k] == s[j+k]){ 
        	k++; 
        	continue; 
        }	
        else if (s[i+k] < s[j+k]){ 
        	i = max(i + k + 1, j);
        	j = i + 1;
        }
        else 
        	j += k + 1;
        k = 0;
    }
    return i;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin>>n;

	string s;
	cin>>s;
	int sum = 0;
	for (auto x : s)
		sum += (int)(x - '0');

	if (sum == 0){ // só tem zero
		cout<<0<<' '<<0<<endl;
		return 0	;
	}
	if (sum == n){
		cout<<0<<' '<<0<<endl;
		return 0;
	}

	int l = 0;

	while (s[l] != '0') // sei que tem algum zero
		l++; 

	// l é a posição do primeiro zero, começo do corte

	string t = s.substr(l); // sufixo começa no l


	sum = 0;
	for (auto x : t)
		sum += (int)(x - '0');

	if (sum == 0){ // substring é só zero
		cout<<l<<' '<<0<<endl;
		return 0;
	}

	
	int r = MaxLexSubstr(t);

	cout<<l<<' '<<r<<endl;
}