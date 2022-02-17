/*
	Title: Implicit Segment Tree
	Description: "Range Query-Point update" data structure that is
	dynamically built.
	Complexity:
		update(): O(log (MAX_POS))
		query(): O(log (MAX_POS))
	
	Details: 
		- You don't need to compress coordinates when using it
		(you just need to define the maximum value of a position
        when building the root)
            - Seg<int> * root = new Seg(0, 1000000000)
		- It is around 1.8 times slower than the Static SegTree 
        - NEUT is the neutral value of the operation
*/
template<typename T>
struct Seg {
    const T NEUT = 0; // Be aware
    int l, r;
    T sum = NEUT;
    Seg * lv = nullptr, * rv = nullptr;

    Seg(int lb = 0, int rb = 0) : l(lb), r(rb) {} ;
    T merge(T left, T right) {return left + right;} // Be aware

    void push() {
        if (!lv && l < r) {
            int m = (l + r) / 2;
            lv = new Seg(l, m);
            rv = new Seg(m + 1, r);
        }
    }
    void update(int k, T s) {
        if(l == r){
            sum = x;
            return;
        }
        else{
            push();
            if (k <= lv->r) lv->update(k, x);
            else rv->update(k, x);
            sum = merge(lv->sum, rv->sum);
        }   
    }
    T query(int lq, int rq) {
        if (lq <= l && r <= rq) return sum;
        if (l > rq || lq > r) return NEUT;
        push();
        return merge(lv->query(lq, rq), rv->query(lq, rq));
    }
};
