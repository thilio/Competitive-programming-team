/*
	Title: Convex Hull Trick

	Description: DP optimization from O(n^2) to O(n log n)
		It receives a set of lines and takes the maximum in a given point x

	Complexity:
		- insert: O(n) amortized
		- query: O(log n)

	Details: The angular coeficient must be inserted in increasing order and it
	takes the maximum. To change to minimum is easy
*/
struct CHT{
	using ll = long long;
	using pll = pair<ll, ll>;
	vector<pll> Hull;

	ll getVal(pll a, ll x) {return a.f*x + a.s;}

	ll cmp(pll a, pll b, pll c){
		return ((__int128)(b.s - c.s)*(b.f - a.f) <= 
			(__int128)(a.s - b.s) * (c.f - b.f));
	}

	void insert(ll inc, ll y){
	    Hull.push_back({inc,y});
	    int i = Hull.size(); 
	    while((Hull.size())> 2 && cmp(Hull[i - 3],Hull[i - 2], Hull[i - 1]))
	      	Hull[i - 2]=Hull[i - 1], Hull.pop_back(), i--;
	}
	ll query(ll x) {
	    ll l = -1, r = Hull.size();
	    while (r - l > 1) {
	        ll m = (l + r) / 2;
	        if ((getVal(Hull[m], x) <= getVal(Hull[m + 1], x)))
	           	l = m;
	        else
	            r = m;
	    }
	    return getVal(Hull[r], x);
	}
};

pll l[MAXN];
ll n;
CHT c;

void build(){
	cin >> n;

	frr(i, n) cin >> l[i].f >> l[i].s;
	sort(l + 1, l + 1 + n);
	for(int i = 1; i <= n; i++)
		c.insert(l[i].f, l[i].s);
}

/*
	Title: Convex Hull Trick

	Description: DP optimization from O(n^2) to O(n log n)
		It receives a set of lines and takes the maximum in a given point x

	Complexity:
		- insert: O(log n)
		- query: O(log n)

	Details: The angular coeficient can be inserted in any order
*/

bool Q;
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};
struct Cht : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = INT_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) { // k * m + x and MAX CHT
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.k * x + l.m;
	}
};