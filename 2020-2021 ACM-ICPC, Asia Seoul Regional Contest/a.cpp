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

#define MAXN 510
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int dist(pii a, pii b){
	return abs(a.f - b.f) + abs(a.s - b.s);
}

void getAns(pii ini, pii fim, int t){
	if(ini.f == fim.f){ // vertical
		if(ini.s < fim.s){
			cout << ini.f << " " << ini.s + t << endl;
		}
		else{
			cout << ini.f << " " << ini.s - t << endl;	
		}
	}
	else{
		if(ini.f < fim.f){
			cout << ini.f + t << " " << ini.s << endl;
		}
		else{
			cout << ini.f - t << " " << ini.s << endl;	
		}
	}

	exit (0);
}

vector<pair<pii, int>> linha[MAXN];
int tipo[MAXN]; // 0 se é hor e 1 se é vert
int fromto[MAXN][MAXN];
pii ini;
int posIni;
pair<pii, pii> reta[MAXN];
int n, tempo;

void read(){
	cin >> n >> tempo;
	cin >> reta[0].f.f >> reta[0].f.s >> reta[0].s.f >> reta[0].s.s;
	ini = reta[0].f;

	if(reta[0].f.f == reta[0].s.f) {
		tipo[0] = 1;
		if(reta[0].f.s > reta[0].s.s) swap(reta[0].f, reta[0].s);
	}
	else {
		tipo[1] = 0;
		if(reta[0].f.f > reta[0].s.f) swap(reta[0].f, reta[0].s);
	}

	frr(i, n-1){
		cin >> reta[i].f.f >> reta[i].f.s >> reta[i].s.f >> reta[i].s.s;

		if(reta[i].f.f == reta[i].s.f) {
			tipo[i] = 1;
			if(reta[i].f.s > reta[i].s.s) swap(reta[i].f, reta[i].s);
		}
		else {
			tipo[i] = 0;
			if(reta[i].f.f > reta[i].s.f) swap(reta[i].f, reta[i].s);
		}
	}
}

void build(){
	fr(l, n){
		linha[l].pb({reta[l].f, l});

		if(tipo[l] == 0){
			for(int i = 0; i < n; i++){
				if(tipo[i] == 1){
					if(reta[i].f.s < reta[l].f.s && reta[l].f.s < reta[i].s.s && reta[l].f.f < reta[i].f.f && reta[i].f.f < reta[l].s.f){
						linha[l].pb({{reta[i].f.f, reta[l].f.s}, i});
					}
				}
			}		
		}
		else{
			for(int i = 0; i < n; i++){
				if(tipo[i] == 0){
					if(reta[l].f.s < reta[i].f.s && reta[i].f.s < reta[l].s.s && reta[i].f.f < reta[l].f.f && reta[l].f.f < reta[i].s.f){
						linha[l].pb({{reta[l].f.f, reta[i].f.s}, i});
					}
				}
			}	
		}

		linha[l].pb({reta[l].s, l});

		sort(linha[l].begin(), linha[l].end());

		frr(j, linha[l].size() - 2){
			fromto[linha[l][j].s][l] = j;
		}
	}
}

void solve(int tot){
	int davez = 0, t = tot, pos = 0, comecou = 1, dir;

	if(tipo[0] == 0){
		if(reta[0].f == ini) {
			pos = 0;
			dir = 0;
		}
		else {
			pos = (int)linha[0].size() - 1;
			dir = 2;
		}
	}
	else{
		if(reta[0].f == ini) {
			pos = 0;
			dir = 1;
		}
		else {
			pos = (int)linha[0].size() - 1;
			dir = 3;
		}
	}

	while(t >= 0){
		//cout << davez << " " << linha[davez][pos].f.f << " " << linha[davez][pos].f.s << " " << t << " " << dir << endl;

		if(pos == MOD){
			assert (0);
		}

		if(dir <= 1){
			if(pos == linha[davez].size() - 1){
				if(linha[davez][pos].f == ini) {
					if(comecou) comecou = 0;
					else t = tot%(tot - t);
				}

				dir = dir + 2;
			}
			else{
				int d = dist(linha[davez][pos].f, linha[davez][pos + 1].f);
				if(d >= t){
					getAns(linha[davez][pos].f, linha[davez][pos + 1].f, t);
				}
				else t -= d;

				int auxp = pos;
				if(auxp != linha[davez].size() - 2){
					pos = fromto[davez][linha[davez][auxp+1].s];
					davez = linha[davez][auxp+1].s;
					dir = (dir + 1)%4;
				}
				else{
					pos = linha[davez].size() - 1;
				}

				//cout << pos << " " << davez << endl;
			}
		}
		else{
			if(pos == 0){
				if(linha[davez][pos].f == ini) {
					if(comecou) comecou = 0;
					else t = tot%(tot - t);
				}

				dir = dir - 2;
			}
			else{
				int d = dist(linha[davez][pos].f, linha[davez][pos - 1].f);
				if(d >= t){
					getAns(linha[davez][pos].f, linha[davez][pos - 1].f, t);
				}
				else t -= d;

				int auxp = pos;
				if(auxp != 1){
					pos = fromto[davez][linha[davez][auxp-1].s];
					davez = linha[davez][auxp-1].s;
					dir = (dir + 1)%4;
				}
				else{
					pos = 0;
				}
			}
		}
	}
}

int main(){
	fastio;

	read();
	fr(i, n) fr(j, n) fromto[i][j] = MOD;

	build();
	/*
	fr(l, n){
		cout << "---------- " << l << " ----------" << endl;
		for(auto x: linha[l]){
			cout << x.f.f << " " << x.f.s << " " << x.s << endl;
		}

		cout << endl;
	}
	fr(l, n){
		fr(j, n){
			cout << fromto[l][j] << ' ';
		}
		cout << endl;
	}
	*/

	solve(tempo);
}
