#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

// #define endl '\n'
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
const int MAXN = 1e3 + 10;

int get_dir(char c){
	if (c == 'U') return 0;
	if (c == 'R') return 1;
	if (c == 'D') return 2;
	return 3;
}

int atx, aty, dir;
int mapa[MAXN][MAXN];

int mx[4] = {-1, 0, 1, 0}; // U R D L
int my[4] = {0, 1, 0, -1};

bool valid(){ return mapa[atx + mx[dir]][aty + my[dir]]; }

void walk(){ atx += mx[dir]; aty += my[dir]; }

bool possible(pii obj){
	int ox, oy, od;
	ox = atx; oy = aty; od = dir;

	while (!valid())
		dir = (dir + 1) % 4;

	walk();

	if (make_pair(atx, aty) == obj)
		return true;

	atx = ox; aty = oy; dir = od;
	return false;
}

int preciso(pii obj){	
	int ox, oy, od;
	ox = atx; oy = aty; od = dir;

	for (int i = 1; i < 4; i++){
		dir = (od + i) % 4;
	
		while (!valid())
			dir = (dir + 1) % 4;

		walk();
	
		if (make_pair(atx, aty) == obj)
			return i + 1;
		
		atx = ox;
		aty = oy;
	}
	assert(0);
}

void solve(){
	int n, m, q, sx, sy;
	char d;

	cin>>n>>m>>q;
	cin>>sx>>sy>>d;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m)
			mapa[i][j] = (s[j] == '.'); // 1 se pode, 0 se não
	}

	atx = sx - 1; aty = sy - 1;
	dir = get_dir(d);

	int x;
	char c;
	vii passei;
	while (q--){
		cin>>c;
		if (c == 'R')
			dir = (dir + 1) % 4;
		else{
			cin>>x;
			while (x--){
				while (!valid())
					dir = (dir + 1) % 4;
				walk();
				passei.pb({atx, aty});
			}
		}
	}

	int ans = 1, p = 0; // ans = 1, já começo andando Cuidado!

	atx = sx - 1; aty = sy - 1;
	dir = get_dir(d);

	while (p < passei.size()){
		while (p < passei.size() and possible(passei[p]))
			tie(atx, aty) = passei[p++];
		if (p == 0) // vou ter que rodar antes de andar
			ans--;
		if (p == passei.size())
			break;
		ans += preciso(passei[p]);
		tie(atx, aty) = passei[p++];
	}

	if (passei.size() == 0)
		ans = 0;
	cout<<ans<<endl;
}

int32_t main(){
	freopen("reduce.in", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}