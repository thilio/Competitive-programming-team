#include "bits/stdc++.h"
using namespace std;

const int MAXN = 100100; 
int en;

struct trie{
	int cnt, wrd;
	map<char, int> m;
	trie(){
		cnt = 0; wrd = 0;
		m.clear();
	}
	
}t[MAXN];

int new_node(){
	t[en].cnt = t[en].wrd = 0;
	t[en].m.clear();
	return en++;
}

void init(){
	en = 0;
	new_node();
}

void add(int node, string &s,int i){ // add string to trie
	t[node].cnt++;
	if(i == s.size()){
		t[node].wrd++;
		return;
	}
	if(!t[node].m.count(s[i])){
		t[node].m[s[i]] = new_node();
	}
	add(t[node].m[s[i]], s, i + 1);
}

int main(){

}
