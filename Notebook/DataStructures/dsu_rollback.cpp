/*
   Title: Disjoint Set Union with rollback
   Description: DSU which you may undo last successful operation
   Complexity:  find O(log(n))
   		merge O(log(n))
   		rollback O(1)
  
   Details: One may only undo the last SUCCESSFUL operation

   Together with the dfs tick this may be used for OFFLINE 
   total persistance. Just save the operations as a tree.

   Drop success restriction is easy, just store -1 in the stack
   (stack may be bigger now, careful)
*/

int id[MAXN], sz[MAXN];
vector<int> stk;

void init(){
	for (int i = 0; i < MAXN; i++){
		id[i] = i;
		sz[i] = 1;
	}
	stk.clear();
}

int find(int a){
	if (a == id[a])
		return a;
	return find(id[a]); // DO NOT use path compression
}

bool merge(int a, int b){
	a = find(a);
	b = find(b);

	if (a == b) // BE CAREFUL, unsuccessful operations do not join stack
		return false;

	if (sz[a] < sz[b])
		swap(a, b);

	id[b] = a;
	sz[a] += sz[b];
	stk.push_back(b);

	return true;
}

void rollback(){ // undo last successful operation
	if (stk.empty())
		return; // One assert here, you may be doing something wrong

	int x = stk.back();
	stk.pop_back();

	sz[id[x]] -= sz[x];
	id[x] = x;
}
