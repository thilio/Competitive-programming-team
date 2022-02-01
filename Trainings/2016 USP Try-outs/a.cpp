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
typedef pair<long double, long double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

ponto grande[4];
ponto pequeno[4];
long double h, w;
long double razao, angulo;

long double dist(ponto a, ponto b){
	return sqrt((a.f - b.f)*(a.f - b.f) + (a.s - b.s)*(a.s - b.s));
}


long double dot(ponto a, ponto b){
	return a.f*b.f + a.s*b.s;
}

long double cross(ponto a, ponto b){
	return a.f*b.s - a.s*b.f;
}

long double r[2][2];
// 0 se tem a mesma orientação e 1 caso contrário
int tipo;

void read(){
	cin >> h >> w;
	grande[0] = {0.0, 0.0};
	grande[3] = {0.0, h};
	grande[2] = {w, h};
	grande[1] = {w, 0.0};

	fr(i, 4) cin >> pequeno[i].f >> pequeno[i].s;
	razao = w/dist(pequeno[0], pequeno[1]);
	ponto aux = {pequeno[1].f - pequeno[0].f, pequeno[1].s - pequeno[0].s};
	ponto aux2 = {pequeno[2].f - pequeno[0].f, pequeno[2].s - pequeno[0].s};

	if(cross(aux, aux2)*cross(grande[1], grande[3]) > 0.0) tipo = 0;
	else tipo = 1;

	angulo = acos(dot(aux, grande[1])/(dist(grande[0], aux)*w));

	if(tipo){
		if(aux.s < 0) angulo = -angulo;
	}
	else{
		if(aux.s > 0) angulo = -angulo;
	}
}

long double mat[2][2];
	
int main(){
	read();
	r[0][0] = cos(angulo);
	r[0][1] = -sin(angulo);
	r[1][0] = sin(angulo);
	r[1][1] = cos(angulo);

	if(tipo){	
		r[0][1] = -r[0][1];
		r[1][1] = -r[1][1];
	}

	// construir a matriz para inverter
	long double to_inv[2][2], inv[2][2];
	fr(i, 2) fr(j, 2) to_inv[i][j] = razao*r[i][j];
	to_inv[0][0] -= 1.0;
	to_inv[1][1] -= 1.0;

	long double det = to_inv[0][0]*to_inv[1][1] - to_inv[0][1]*to_inv[1][0];
	inv[0][0] = to_inv[1][1]/det;
	inv[1][1] = to_inv[0][0]/det;
	inv[0][1] = -to_inv[0][1]/det;
	inv[1][0] = -to_inv[1][0]/det;

	fr(i, 2){
		fr(j, 2){
			fr(k, 2){
				mat[i][j] += inv[i][k]*r[k][j];
			}
			mat[i][j] *= razao;
		}
	}

	printf("%.8Lf %.8Lf\n",
		mat[0][0]*pequeno[0].f + mat[0][1]*pequeno[0].s , mat[1][0]*pequeno[0].f + mat[1][1]*pequeno[0].s);
}
