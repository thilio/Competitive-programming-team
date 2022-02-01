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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;
const ll mod = 1000003;


int A, B, n;

// lf é o maior sufixo proprio da string que é prefixo do conjunto
// lo é o maior sufixo proprio da string que é prefixo do conjunto e é ocorrencia

int en = 1, tcnt, topo[MAXN], lf[MAXN], lo[MAXN], pa[MAXN], oc[MAXN];
struct no{
	char c;
	int mrk, cnt;
	map<char, int> m;
	no(){mrk = cnt = 0; m.clear();}
} t[MAXN];

inline int new_node(int p, char c){
	t[en].m.clear();
	t[en].mrk = t[en].cnt = 0;
	lf[en] = lo[en] = oc[en] = 0;
	pa[en] = p;
	t[en].c = c;
	return en++;
}

inline void init(){t[0] = no(); en = 1;}

vi lst;

void add(int v, int pos, string &s){
	int u = v;

	while (pos < s.size()){
		if (!t[u].m.count(s[pos]))
			t[u].m[s[pos]] = new_node(u, s[pos]);
		u = t[u].m[s[pos]];
		t[u].cnt++;
		pos++;
	}
	t[u].mrk = 1;
	lst.pb(u);
}

void aux_link(int v){
	lf[v] = lf[pa[v]];
	while (lf[v] != 0 and !t[ lf[v] ].m.count(t[v].c))
		lf[v] = lf[lf[v]];
	
	if (t[ lf[v] ].m.count(t[v].c))
		lf[v] = t[ lf[v] ].m[t[v].c];

	if (t[ lf[v] ].mrk)
		lo[v] = lf[v];
	else
		lo[v] = lo[lf[v]];
}

void aho(){
	queue<int> q;

	for (auto it : t[0].m)
		q.push(it.second);
	
	tcnt = 0;
	while (!q.empty()){
		int v = q.front();
		q.pop();
		topo[tcnt++] = v;
		
		for (auto it : t[v].m){
			aux_link(it.second);
			q.push(it.second);
		}
	}
}

string alfa;

char to_low(char c){
	if ('A' <= c and c <= 'Z')
		return (c - 'A') + 'a';
	if ('0' <= c and c <= '9'){
		if (c == '0') return 'o';
		if (c == '1') return 'i';
		if (c == '3') return 'e';
		if (c == '5') return 's';
		if (c == '7') return 't';
		return 0;
	}
	return c;
}


int get_next(int node, char a){
	if (t[node].m.count(a))
		return t[node].m[a];

	if (node == 0)
		return 0;

	return get_next(lf[node], a);
}


ll memo[2000][20][2][2][2];

// que no estou, tamanho, numeral, pequeno, grande
ll pd(int no, int sz, int num, int low, int high){
	if (lo[no] > 0 or t[no].mrk or sz > B) // tem ocorrencia ou é mto grande!
		return 0;
	
	ll &pdm = memo[no][sz][num][low][high];
	if (pdm != -1)
		return pdm;

	pdm = 0;

	if (A <= sz and num and low and high) // ocorrencia
		pdm = 1;

	for (char a = 'a'; a <= 'z'; a++){
		int nxt = get_next(no, a);
		pdm = (pdm + pd(nxt, sz + 1, num, 1, high)) % mod;
	}

	for (char a = 'A'; a <= 'Z'; a++){
		int nxt = get_next(no, to_low(a));
		pdm = (pdm + pd(nxt, sz + 1, num, low, 1)) % mod;
	}

	for (char a = '0'; a <= '9'; a++){
		if (to_low(a) != 0){
			int nxt = get_next(no, to_low(a));
			pdm = (pdm + pd(nxt, sz + 1, 1, low, high)) % mod;
		}
		else // iterrompe qualquer palavra
			pdm = (pdm + pd(0, sz + 1, 1, low, high)) % mod;
	}

	return pdm;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>A>>B>>n;

	string s;
	fr(i, n){
		cin>>s;
		add(0, 0, s);
	}

	aho(); // cria o aho

 	memset(memo, -1, sizeof memo);
	// nó vazio é o nó 1
	ll ans = pd(0, 0, 0, 0, 0);

	cout<<ans<<endl;
}