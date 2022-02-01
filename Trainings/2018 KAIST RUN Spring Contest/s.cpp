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

int m[5][5] = {	{0, 1, 2, 4, 4},
				{5, 5, 2, 3, 4},
				{5, 5, 6, 7, 7},
				{9, 9, 9, 7, 7},
				{8, 9, 9, 7, 10},};

string out[11] = {"New Customer",
				"Promising",
				"About to Sleep",
				"Hibernating",
				"Lost",
				"Potential Loyalist",
				"Need Attention",
				"About to Leave",
				"Champion",
				"Loyal Customer",
				"Can't Lose Them" };				

map<string, int> crd;

int lst[MAXN], freq[MAXN];

int r[5], f[5];


void status(int rn, int fn){
	for (int rr = 0; rr < 5; rr++)// esquerda ->
		if (rn <= r[rr])
			for (int ff = 0; ff < 5; ff++) // subindo |
				if (fn <= f[ff]){ // achei
					cout<<out[m[ff][rr]]<<endl;
					return;
				}		
	assert(0); // nao vai rolar, mas vai que né;			
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	fr(i, 4)
		cin>>r[i];
	fr(i, 4)
		cin>>f[i];	
	r[4] = f[4] = INF;	

	int n;
	cin>>n;

	int x, id = 0, nm;
	string s;
	for (int t = 1; t <= n; t++){
		cin>>x>>s;
		if (!crd.count(s))
			crd[s] = id++;

		nm = crd[s];

		if (x == 1){
			lst[nm] = t;
			freq[nm]++;
		}
		else{
			if (freq[nm] == 0)
				cout<<"None"<<endl;
			else
				status(t - lst[nm], freq[nm]);
		}
	}
}