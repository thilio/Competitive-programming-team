#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

int Y, N, S; // Y = number of days, N = number of nights, S = number of stays
int H, M; //  H = number of hotels, M = Number of rates
vector<array<int, 4>> rates[366]; // {hotel, check-out day, cost, index}

vector<int> ans;

int memo_s[366][51][30];
int memo_n[366][51][51];

int dp_s(int day, int last, int left){
	if(left == 0) return 0;
	if(day > Y){
		return INF;
	}

	int &pdm = memo_s[day][last][left];
	if(pdm != -1) return pdm;

	pdm = dp_s(day + 1, 0, left);

	for(auto x: rates[day]){
		if(x[0] == last) continue;
		pdm = min(pdm, x[2] + dp_s(x[1], x[0], left - 1));
	}

	return pdm;
}

void rec_s(int day, int last, int left){
	if(left == 0) return;
	if(day > Y) return;

	int pdm = dp_s(day, last, left); 

	if(pdm == dp_s(day + 1, 0, left)){
		rec_s(day + 1, 0, left);
		return;
	}

	for(auto x: rates[day]){
		if(x[0] == last) continue;
		if (pdm == x[2] + dp_s(x[1], x[0], left - 1)){
			ans.pb(x[3]);
			rec_s(x[1], x[0], left - 1);
			break;
		}
	}
}

int dp_n(int day, int last, int left){
	if(left == 0) return 0;
	if(day > Y){
		return INF;
	}

	int &pdm = memo_n[day][last][left];
	if(pdm != -1) return pdm;

	pdm = dp_n(day + 1, 0, left);

	for(auto x: rates[day]){
		if(x[0] == last) continue;
		pdm = min(pdm, x[2] + dp_n(x[1], x[0], max(0, left - (x[1] - day))  ));
	}

	return pdm;
}

void rec_n(int day, int last, int left){
	if(left == 0) return;
	if(day > Y) return;

	int pdm = dp_n(day, last, left); 

	if(pdm == dp_n(day + 1, 0, left)){
		rec_n(day + 1, 0, left);
		return;
	}

	for(auto x: rates[day]){
		if(x[0] == last) continue;
		if (pdm == x[2] + dp_n(x[1], x[0], max(0, left - (x[1] - day))) ){
			ans.pb(x[3]);
			rec_n(x[1], x[0], max(0, left - (x[1] - day)));
			break;
		}
	}
}

void print_ans(){
	cout << ans.size() << endl;
	for(auto x: ans){
		cout << x << ' ';
	}
	gnl;
}

void rec_stay(){
	cout << "STAYS" << endl;
	rec_s(1, 0, S);
	print_ans();
}

void rec_night(){
	cout << "NIGHTS" << endl;
	rec_n(1, 0, N);
	print_ans();
}

int main(){

	fastio;

	cin >> Y >> N >> S;
	cin >> H >> M;

	frr(i, M){
		int h, b, e, c;
		cin >> h >> b >> e >> c;

		rates[b].pb({h, e, c, i});
	}

	ms(memo_s, -1); ms(memo_n, -1);

	int stay = dp_s(1, 0, S);
	int night = dp_n(1, 0, N);

	if(stay == night && stay == INF){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}

	if(stay < night){
		rec_stay();
	}
	else{
		rec_night();
	}

}
