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

pii carpet[10];

bool intersec(pii a, pii b, int oa, int ob, int ca, int cb){
	if(oa) swap(carpet[ca].f, carpet[ca].s);
	if(ob) swap(carpet[cb].f, carpet[cb].s);

	bool deuh = false, deuv = false;
	if((a.f <= b.f && b.f <= a.f + carpet[ca].f) || (b.f <= a.f && a.f <= b.f + carpet[cb].f)) 
		deuh = true;
	if((a.s <= b.s && b.s <= a.s + carpet[ca].s) || (b.s <= a.s && a.s <= b.s + carpet[cb].s)) 
		deuv = true;

	if(oa) swap(carpet[ca].f, carpet[ca].s);
	if(ob) swap(carpet[cb].f, carpet[cb].s);

	return deuv * deuh;
}

set<pii> pt;
int usado[10], ori[10];
pii pos[10];
int num, tot = 0, w, h;

void backtracking(){
	int sum = 0;
	fr(i, tot){
	    if(usado[i]){
	      	sum += (carpet[i].f + 1)*(carpet[i].s + 1);
	    	//cout << i << ' ' << ori[i] << endl; 
	    }
	}

	if(sum == w*h){
		cout << "yes" << endl;
		exit (0);
	}
	else if(sum > w*h) return;

	if(num == tot) {
		cout << "no" << endl;
		exit (0);
	}

	/* Procuro o primeiro ponto que dá certo*/
	pii davez = {-1, -1};
	for(auto par : pt){
		int deu = 1;
		fr(i, tot){
			if(usado[i] && intersec(pos[i], par, ori[i], 0, i, tot)){
				deu = 0;
				break;
			}
		}
		if(deu) {
			davez = par;
			break;
		}
	}

/*
	cout << davez.f << " " << davez.s << endl;
	cout << endl << endl;
*/

	if(davez == mp(-1, -1)) return;

	/*Agora, vou brutar e tentar todo mundo*/
	fr(cDavez, tot){
		if(usado[cDavez]) continue;

		int deu = 1;
		fr(i, tot){
			if(usado[i] && intersec(pos[i], davez, ori[i], 0, i, cDavez)){
				deu = 0;
				break;
			}
		}

		if(davez.f + carpet[cDavez].f > w || davez.s + carpet[cDavez].s > h) deu = 0;


		if(deu){
			/*com a orientação 0 deu certo, atualizo tudo e continuo o backtracking*/
			usado[cDavez] = 1;
			pos[cDavez] = davez;
			ori[cDavez] = 0;
			num++;

			if(davez.f + carpet[cDavez].f + 1 <= w)
				pt.insert({davez.f + carpet[cDavez].f + 1, davez.s});


			if(davez.s + carpet[cDavez].s + 1 <= h)
				pt.insert({davez.f, davez.s + carpet[cDavez].s + 1});

			backtracking();

    	if(davez.f + carpet[cDavez].f + 1 <= w)
				pt.erase({davez.f + carpet[cDavez].f + 1, davez.s});


			if(davez.s + carpet[cDavez].s + 1 <= h)
				pt.erase({davez.f, davez.s + carpet[cDavez].s + 1});

      
			usado[cDavez] = 0;
			pos[cDavez] = {0, 0};
			ori[cDavez] = 0;
			num--;
		}

		deu = 1;
		fr(i, tot){
			if(usado[i] && intersec(pos[i], davez, ori[i], 1, i, cDavez)){
				deu = 0;
				break;
			}
		}

		if(davez.f + carpet[cDavez].s > w || davez.s + carpet[cDavez].f > h) deu = 0;

		if(deu){
			/*com a orientação 0 deu certo, atualizo tudo e continuo o backtracking*/
			usado[cDavez] = 1;
			pos[cDavez] = davez;
			ori[cDavez] = 1;
			num++;

			if(davez.f + carpet[cDavez].s + 1 <= w)
				pt.insert({davez.f + carpet[cDavez].s + 1, davez.s});


			if(davez.s + carpet[cDavez].f + 1 <= h)
				pt.insert({davez.f, davez.s + carpet[cDavez].f + 1});

			backtracking();
      
      		if(davez.f + carpet[cDavez].s + 1 <= w)
				pt.erase({davez.f + carpet[cDavez].s + 1, davez.s});


			if(davez.s + carpet[cDavez].f + 1 <= h)
				pt.erase({davez.f, davez.s + carpet[cDavez].f + 1});

			usado[cDavez] = 0;
			pos[cDavez] = {0, 0};
			ori[cDavez] = 0;
			num--;
		}
	}
}

int main(){
	fastio;
	int tipos;
	cin >> w >> h >> tipos;		
	fr(i, tipos){
		int ai, wi, hi;
		cin >> ai >> wi >> hi;

		while(ai--){
			carpet[tot] = {wi-1, hi-1};
			tot++;
		}
	}

	pt.insert({1, 1});
	backtracking();

	cout << "no" << endl;
}
