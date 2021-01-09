#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()
#define endl '\n'

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
int n;
ll reg[8];
int estou = 0;
int prox = 1;
vector<string> inst[60];

ll stoi(string& k){
	return stol(k);
}

void go_mov(int ind){
	if(inst[ind][2][0] == 'R'){
		int x = inst[ind][1][1] - '0';
		int y = inst[ind][2][1] - '0';
		reg[x] = reg[y];
	}
	else{
		int x = inst[ind][1][1] - '0';
		int val = stoi(inst[ind][2]);
		reg[x] = val;
	}
	prox = estou + 1;
}

void go_add(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	int z = inst[ind][3][1] - '0';
	reg[x] = reg[y] + reg[z];
	prox = estou + 1;
}

void go_sub(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	int z = inst[ind][3][1] - '0';
	reg[x] = reg[y] - reg[z];
	prox = estou + 1;
}

void go_mul(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	int z = inst[ind][3][1] - '0';
	reg[x] = reg[y]*reg[z];
	prox = estou + 1;
}

void go_div(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	int z = inst[ind][3][1] - '0';
	reg[x] = reg[y]/reg[z];
	prox = estou + 1;
}

void go_mod(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	int z = inst[ind][3][1] - '0';
	ll zz = (reg[z]);
	ll mm = ((reg[y]%zz) + zz)%zz;
	reg[x] = mm;
	prox = estou + 1;
}

void go_beq(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	if(reg[x] == reg[y]) prox = stoi(inst[ind][3]);
	else prox = estou + 1;
}

void go_blt(int ind){
	int x = inst[ind][1][1] - '0';
	int y = inst[ind][2][1] - '0';
	if(reg[x] < reg[y]) prox = stoi(inst[ind][3]);
	else prox = estou + 1;
}

void go_jmp(int ind){
	prox = stoi(inst[ind][1]);
}
void go_print(int ind){
	int x = inst[ind][1][1] - '0';
	cout << reg[x] << endl;
	prox = estou + 1;
}
void go_exit(int ind){
	prox = -1;
}

void go(int ind){
	string t;
	t = inst[ind][0];
	if(t == "MOV") go_mov(ind);
	if(t == "ADD") go_add(ind);
	if(t == "SUB") go_sub(ind);
	if(t == "MUL") go_mul(ind);
	if(t == "DIV") go_div(ind);
	if(t == "MOD") go_mod(ind);
	if(t == "BEQ") go_beq(ind);
	if(t == "BLT") go_blt(ind);
	if(t == "JMP") go_jmp(ind);
	if(t == "PRINT") go_print(ind);
	if(t == "EXIT") go_exit(ind);
}

int main(){
	fastio;
   	string s;
   	cin >> n;
  	getline(cin, s);

  	for(int i = 0; i < n; i++){
  		getline(cin,s);
  		stringstream ss(s);
  		while(ss >> s){
  			inst[i].pb(s);
  		}
  	}


  	int ct = 0;

  	while(ct < 100000){
  		ct++;
  		go(estou);
  		estou = prox;
  		if(prox == -1) return 0;
  	}

  	cout << "laco infinito!" << endl;



}
