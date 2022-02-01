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

int ts, ps, k;
string txt, pat;

int memo[1000010][110];

int pd(){
	for (int pp = 0; pp <= ps; pp++) // acabou o texto
		memo[ts][pp] = ps - pp;

	for (int pt = 0; pt <= ts; pt++) // acabou o padrão
		memo[pt][ps] = 0;

	for (int pt = ts - 1; pt >= 0; pt--)
		for (int pp = ps - 1; pp >= 0; pp--){
			int &pdm = memo[pt][pp];
			pdm = INF;

			if (txt[pt] == pat[pp]) // match!
				pdm =  min(pdm, memo[pt + 1][pp + 1]);
			pdm = min(pdm, memo[pt + 1][pp] + 1); // adição no padrão
			pdm = min(pdm, memo[pt][pp + 1] + 1); // remoção no padrão
			pdm = min(pdm, memo[pt + 1][pp + 1] + 1); // substituição
		}

	int ans = memo[0][0];
	for (int pt = 1; pt < ts; pt++){
		ans = min(ans, memo[pt][0]);	
	}

	return ans;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>ps>>ts>>k;
	cin>>pat>>txt;

	int ans = pd();

	if (ans <= k)
		cout<<"S"<<endl;
	else
		cout<<"N"<<endl;
}