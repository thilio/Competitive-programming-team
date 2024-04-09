/*
Description:number of distinct elements in range
Complexity: O(n + q sqrt(n))
Details: Mo's algorithm can be used when queries are
offline and it is easy to insert and erase one element
in the answer. Another example is dynamic connectivity
when you can add edges easily ,say DSU, and remove easily
with rollback
*/
vector<int> v, resp;
int freq[MAXA];

int l = 0, r = -1;
int ans, sq;

struct qry{
	int l, r, ind;

	qry() : l(0), r(0), ind(0) {} 
	qry(int _l, int _r, int _ind): l(_l), r(_r), ind(_ind) {}
 
	bool operator < (const qry& x) const{
		if (l/sq == x.l/sq) return (r < x.r);
		return l < x.l;
	}
};
 
void add(int val){
	freq[val]++;
	if(freq[val] == 1) ans++;
}
 
void remove(int val){
	freq[val]--;
	if(freq[val] == 0) ans--;
}
 
int query(int x, int y){
	while(r < y) add(v[++r]);
	while(l > x) add (v[--l]);
	while(r > y) remove(v[r--]);
	while(l < x) remove(v[l++]);
	return ans;
}
 
int main(){
	int n, q;
	cin >> n;
	v.resize(n);
	sq = (int)ceil(sqrt(n));
	for(int i = 0; i < n; i++){
		cin >> v[i];
	}
	cin >> q;
	vector<qry> Q;
	resp.resize(q);
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		Q.push_back({a, b, i});
	}
	sort(Q.begin(), Q.end());
	for(auto x: Q){
		resp[x.ind] = query(x.l, x.r);
	}
	for(auto x: resp){
		cout << x << endl;
	}
}