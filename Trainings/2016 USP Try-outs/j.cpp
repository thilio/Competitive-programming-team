#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define endl '\n'

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

long double memo[7][7][7][5];
pair<pii,pii> help[7][7][7][5]; 
long double fat[7];

long double xp(double a, int exp){
	long double k = 1;

	while(exp > 0){
		k /= a;
		exp--;
	}

	return k;
}

void dp(){
	fat[0] = 1;
	frr(i,6) fat[i] = fat[i - 1]*i;

	for(int p1 = 0; p1 <= 6; p1++){
		for(int p2 = 0; p2 <= 6 - p1; p2++){
			for(int p3 = 0; p3 <= 6 - p1 - p2; p3++){
				if(p1 >= 3) 
					memo[p1][p2][p3][0] += 1 + (p1 - 3);
				if(p2 >= 3) 
					memo[p1][p2][p3][0] += 2 + (p2 - 3);
				if(p3 >= 3) 
					memo[p1][p2][p3][0] += 3 + (p3 - 3);
			}
		}
	}

	for(int k = 1; k <= 4; k++){
		for(int p1 = 0; p1 <= 6; p1++){
			for(int p2 = 0; p2 <= 6 - p1; p2++){
				for(int p3 = 0; p3 <= 6 - p1 - p2; p3++){
					memo[p1][p2][p3][k] = 0;
					int letras = 6 - p1 - p2 - p3;

					for(int i1 = 0; i1 <= p1; i1++){
						for(int i2 = 0; i2 <= p2; i2++){
							for(int i3 = 0; i3 <= p3; i3++){
								for(int ile = 0; ile <= letras; ile++){
									long double exp = 0;
									long double prob = 0;
									int total = i1 + i2 + i3 + ile;

									for(int j1 = 0; j1 <= total; j1++){
										for(int j2 = 0; j2 <= total - j1; j2++){
											for(int j3 = 0; j3 <= total - j1 - j2; j3++){
						
												prob = fat[total]*xp(6,j1 + j2 + j3)*xp(2, total - j1 - j2 - j3)/(fat[j1]*fat[j2]*fat[j3]*fat[total - j1 -j2-j3]);
												exp += prob*(memo[p1 - i1 + j1][p2 - i2 + j2][p3 - i3 + j3][k-1]);
											}
										}
									}
									//if(p1 == 2 && p2 == 2 && p3 == 2 && i1 == 2 && i2 == 2 && i3 == 0 && k == 1) dbg(sum);
									if(exp > memo[p1][p2][p3][k]){
										memo[p1][p2][p3][k] = exp;
										help[p1][p2][p3][k] = mp(mp(i1,i2),mp(i3,ile));
									}
								}
							}
						}
					} 
				}
			}
		}
	}
}

int main(){

	fastio;
	cout << setprecision(10) << fixed;
	dp();
	int t;
	cin >> t;
	while(t--){
		int k; string s;
		cin >> k >> s;
		int p1,p2,p3;
		p1 = p2 = p3 = 0;
		int pa,pv,pe;
		pa = pv = pe = 0;
		fr(i,s.size()){
			if (s[i] == '1') p1++;
			if (s[i] == '2') p2++;
			if (s[i] == '3') p3++;
			if (s[i] == 'A') pa++;
			if (s[i] == 'V') pv++;
			if (s[i] == 'E') pe++;
		}

		cout << memo[p1][p2][p3][k] << endl;
		if(k == 0){
			cout << '-' << endl;
		}
		else{
			pair<pii,pii> aux = help[p1][p2][p3][k];
			if(aux.fst.fst + aux.fst.snd + aux.snd.fst + aux.snd.snd == 0){
				cout << '-' << endl;
			}
			else{
				fr(i,aux.fst.fst) cout << 1;
				fr(i,aux.fst.snd) cout << 2;
				fr(i,aux.snd.fst) cout << 3;
				fr(i,aux.snd.snd){
					if(i < pa) cout << 'A';
					else if (i < pa + pv) cout << 'V';
					else cout << 'E';
				}
				gnl;
			}
		}

	}

}
