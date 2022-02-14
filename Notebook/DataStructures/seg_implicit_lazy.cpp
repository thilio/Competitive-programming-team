/*
	Title: Implicit Segment Tree with Lazy Propagation
	Description: "Range Query-Range update" data structure that is
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
*/
template<typename T>
struct Seg {
    const T NEUT = 0;
    int l, r;
    T sum = NEUT, lz = NEUT;
    Seg * lv = nullptr, * rv = nullptr;

    Seg(int lb, int rb) : l(lb), r(rb) {} ;
    T merge(T left, T right) {return left + right;}
    void applyLazy(){
        if(lz != NEUT){
           sum = merge(sum, lz * (r - l + 1)); // Be aware
            if(l < r) 
                lv->lz = merge(lv->lz, lz), rv->lz = merge(rv->lz, lz); // Be aware
            lz = NEUT;
        }
    }
    void push() {
        if (!lv && l < r) {
            int m = (l + r) / 2;
            lv = new Seg(l, m);
            rv = new Seg(m + 1, r);
        }
        applyLazy();
    }
    void update(int lq, int rq, T x) {
        push();
        if (l > rq || lq > r) return;
        else if (lq <= l && r <= rq) lz = merge(lz, x), push();        
        else {
            lv->update(lq, rq, x), rv->update(lq, rq, x);
            sum = merge(lv->sum, rv->sum);
        }
    }
    T query(int lq, int rq) {
        if (l > rq || lq > r) return NEUT;
        push();
        if (lq <= l && r <= rq) return sum;
        return merge(lv->query(lq, rq), rv->query(lq, rq));
    }
};
