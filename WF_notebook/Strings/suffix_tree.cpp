/*
   Title: Ukkonen's algorithm to build Suffix tree
   Description: Construct the suffix tree of a given
   				string 
   Complexity: O(n) time and memory
   Credits: https://bcc.ime.usp.br/tccs/2016/yancouto/tcc.pdf
*/

using namespace std;

const int N = 2000000;
const int NS = 60;
int en = 1;
int ns;
string S[NS];

struct node{
	int l, r, p;
	int si, suf;
	map<char,int> f; //CHANGE WHEN USING INTEGERS
	node(): l(0), r(-1), p(0), si(0) {}
	node(int L, int R, int P, int S): l(L), r(R), p(P), si(S) {}
	inline int len() {return r - l + 1;}
	inline char operator[](int i){return S[si][i + l];} //CHANGE WHEN USING INTEGERS
}t[N];

inline int new_node(int L, int R, int P, int S){
	t[en] = node(L, R, P, S);
	t[en].f.clear();
	return en++;
}

void clear(){
	en = 1;
	t[0].f.clear();
}

void build(string &s, int k){
	s.push_back('!' + k); //CHANGE WHEN USING INTEGERS
	S[k] = s;
	int n = s.size();
	int i,cn,cd;
	i = cn = cd = 0;
	for(int j = 0; j < n; j++){
		for(; i<= j; i++){
			if(cd == t[cn].len() && t[cn].f.count(s[j])){
				cn = t[cn].f[s[j]];
				cd = 0;
			}
			if(cd < t[cn].len() && t[cn][cd] == s[j]){
				cd++;
				break;
			}

			if(cd == t[cn].len()){
				t[cn].f[s[j]] = new_node(j, n - 1, cn, k);
				if(cn){
					cn = t[cn].suf;
					cd = t[cn].len();
				}
			}
			else{
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].p, t[cn].si);
				t[t[mid].p].f[t[mid][0]] = mid;
				t[mid].f[s[j]] = new_node(j, n -1, mid, k);
				t[mid].f[t[cn][cd]] = cn;
				t[cn].p = mid;
				t[cn].l += cd;

				if(ns) t[ns].suf = mid;

				cn = t[mid].p;
				int g;
				if(cn){
					cn = t[cn].suf;
					g = j - cd;
				}
				else{
					g = i + 1;
				}
				while(g < j && g + t[t[cn].f[s[g]]].len() <= j){
					cn = t[cn].f[s[g]];
					g += t[cn].len();  
				}

				if(g == j){
					t[mid].suf = cn;
					cd = t[cn].len();
					ns = 0; 
				}
				else{
					ns = mid;
					cn = t[cn].f[s[g]];
					cd = j - g;
				}
			}
		}
	}
}

