#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

string oo(string s){
	string aux  = "";
	int i = 0;
	while(i < s.size()){
		if(s[i] == 'u'){
			aux = aux + 'o' + 'o';
		}
		else aux = aux + s[i];
		i++;
	}

	return aux;
}

string kh(string s){
	string aux = "";
	int i = s.size() - 1;
	while(i >= 0){
		if(s[i] == 'h'){
			aux = 'h' + aux;
			i--;
			while(i >= 0 && s[i] == 'k') i--;
		}
		else{
			aux = s[i] + aux;
			i--;
		}
	}

	return aux;
}

int main(){
	fastio;
	int n;
	cin >> n;
	set<string> s;
	string t;
	fr(i, n){
		cin >> t;
		t = kh(oo(t));
		s.insert(t);
	
	//	cout<< t << endl;
	}

	cout << s.size() << endl;
}
