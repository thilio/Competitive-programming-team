/*
   Title: Aho-Corasick's algorithm
   Description: Multi-pattern parallel string matching algorithm
   Complexity:  aho O(|sum of patterns| * |alphabet|)
   		cnt_ocr O(|sum of patterns| + |text|)
   Details: May be used to make string matching with many patterns.
   However, is mostly useful for DPs.

   Let v be a node of the trie and S[v] be it's associated string.

   lf[v] = is the largest proper suffix of S[v] that is also a prefix of some pattern.
   lo[v] = is the largest proper suffix of S[v] that is also a pattern (ocurrence).

   Remember that transversing the failure links is twice the hight of the tree, what 
   goes down must first go up.

   Be careful with DFS when doing DP on the LF and LO, use BFS.

   Credits: https://bcc.ime.usp.br/tccs/2016/yancouto/tcc.pdf
*/

const int MAXN = 2e6 + 10;

int en = 1, topo[MAXN], lf[MAXN], lo[MAXN], pa[MAXN], oc[MAXN];
vector<int> lst; // Node of the ocurrence of the pattern
struct no{
	char c;
	int cnt, mrk; // How many pass, how many end
	map<char, int> m;
	no(){mrk = cnt = 0; m.clear();}
} t[MAXN];

inline int new_node(int p, char c){
	t[en] = no();
	lf[en] = lo[en] = oc[en] = 0;
	pa[en] = p;
	t[en].c = c;
	return en++;
}

inline void init(){t[0] = no(); en = 1; lst.clear();}

void add(int v, int pos, string &s){
	while (pos < s.size()){
		if (!t[v].m.count(s[pos]))
			t[v].m[s[pos]] = new_node(v, s[pos]);
		v = t[v].m[s[pos]];
		t[v].cnt++;
		pos++;
	}
	t[v].mrk = 1;
	lst.pb(v); // This word end in this node
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
	
	int tcnt = 0;
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

void count_ocr(string &s){ 
	int v = 0;

	for (int i = 0; i <= en; i++) // Dont do this if multiple texts
		oc[i] = 0;

	for (char c : s){
		while (v != 0 and !t[v].m.count(c))
			v = lf[v];

		if (t[v].m.count(c))
			v = t[v].m[c];
		oc[v]++;
	}

	for (int i = en - 1; i > 0; i--) // In case of multiple texts, propagate at the end! O(|sum of patterns|)
		oc[ lf[topo[i]] ] += oc[topo[i]];
}
