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