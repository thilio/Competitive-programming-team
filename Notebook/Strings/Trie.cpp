/*
   Title: Trie
   Description: Data structure for strings
   Complexity: O(|P|), where P is the string
   			   being added, removed or searched
*/

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

void add(int node, string &s, int i){ // Add string to trie
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

bool remove(int node, string &s, int i){ // Return true if s was in the trie
	if(i == s.size()){
		if(t[node].wrd){
			t[node].wrd--;
			t[node].cnt--;
			return true;
		}
		return false;
	}

	if(!t[node].m.count(s[i])) return false;
	int son = t[node].m[s[i]];
	if(remove(son, s, i + 1)){
		t[node].cnt--;
		if(t[son].cnt == 0) t[node].m.erase(s[i]);
		return true;
	}
	return false;
}

bool find(int node, string &s, int i){ // Return true if s was in the trie
	if(i == s.size()){
		if(t[node].wrd) return true;
		return false;
	}
	if(!t[node].m.count(s[i])) return false;
	return find(t[node].m[s[i]], s, i + 1);
}