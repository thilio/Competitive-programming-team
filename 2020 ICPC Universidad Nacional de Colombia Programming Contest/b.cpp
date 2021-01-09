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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

string s, t;

// Recebe um string e retorna o começo da maior substring lexicográfica
// A maior substring lexicográfica é sempre um sufixo
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

int main(){
	fastio;

	cin>>s>>t;

	char mxs = *max_element(all(s));
	char mxt = *max_element(all(t));

	if(mxs < mxt){
		cout << mxs + t.substr(MaxLexSubstr(t))<<endl;
		return 0;
	}

	vector<string> v;
	string aux;
	int p = 0;
	while (p < s.size()){
		for (int j = p; j < s.size(); j++){
			if (s[j] >= mxt){ 
				aux.pb(s[j]);
				if (j < s.size() - 1)
					continue;
			}

			v.pb(aux);
			aux.clear();
			p = j + 1;
			break;
		}
	}

	sort(all(v));

	cout << v.back() + t.substr(MaxLexSubstr(t))<< endl;

}