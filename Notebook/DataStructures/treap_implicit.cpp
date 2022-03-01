/*
    Title: Implicit treap data structure
    Description: It's a Binary tree and a heap by "prior". Hear, the key
    property is implicit, that is, the key is the number of nodes to its left.
    For this reason, it's very useful to handle problems where we have a array and
    need to break it into some parts, reverse it and etc. It's keys are 1-indexed

    Complexity: all operations are O(log size)
    Details:
        1) push(node t):
            Do the push of lazy properties to t's sons
        2) split(node t, K key, node & l, node & r):
            Split the nodes in the subtree rooted on "t" into two:
                - l will contain all nodes which are <= key
                - r will contain all nodes which are > key
        3) merge(node & t, node l, node r):
            Merge trees "l" and "r" int one rooted on t.
        4) push_back(T val):
            Insert a node with "val" in the end of this tree
        5) void erase(node & t, K key)
            Erase the first node with key "key" that it encounters
        6) T query(int l, int r)
            Get the sum of all vals of nodes with keys in [l, r] (1-indexed)
        7) int find(node t, int pos)
            Return the val that is in position "pos" (1-indexed)
        8) void update(int l, int r, T val, bool rev)
            Update everyone in [l, r]. It sums "val" to everyone in 
            this interval and also may reverse this interval.
        
        In general, hard Treap problems require modifying this code
*/
const int NEUT = 0;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
struct ImplicitTreap{
    struct item {
        int prior, sz;
        T val, sum, lazy;
        bool rev;
        item *l, *r;
        item (T v = NEUT){
            prior = rng(), l = r = nullptr;
            val = v, sz = 1, sum = v, rev = lazy = 0;
        }
    };
    typedef item* node;
    node root;
    void push(node t) {
        if(t) {
            t->sum += t->lazy * t->sz, t->val += t->lazy;
            if(t->rev) swap(t->l, t->r);
            if(t->l) t->l->rev ^= t->rev, t->l->lazy += t->lazy;
            if(t->r) t->r->rev ^= t->rev, t->r->lazy += t->lazy;
            t->rev = t->lazy = 0;
        }
    }
    inline int sz(node t){return (t ? t->sz : 0);};
    void upd_sz(node t) {
        if(t){
            t->sz = 1, t->sum = t->val;
            push(t->l), push(t->r);
            if(t->l) t->sz += t->l->sz, t->sum += t->l->sum;
            if(t->r) t->sz += t->r->sz, t->sum += t->r->sum;
        }
    };
    void split (node t, node & l, node & r, int key, int add = 0) {
        if (!t) return void( l = r = 0 );
        push(t);
        int cur_key = add + sz(t->l);
        if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
        else split(t->r, t->r, r, key, add + sz(t->l) + 1), l = t;
        upd_sz(t);
    }
    void merge(node & t, node l, node r) {
        push(l), push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge (r->l, l, r->l), t = r;
        upd_sz(t);
    }
    void push_back(T val){ merge(root, root, new item(val));};
 
    // Interface
    T query(int l, int r){
        node L, M, R;
        split(root, L, M, l - 1), split(M, M, R, r - l + 1);
        T ans = M->sum;
        merge(root, L, M), merge(root, root, R);
        return ans;
    }
    // 1-indexed
    int find(node t, int pos){
        push(t);
        if(t == nullptr) return -100000000;
        if((t->l ? t->l->sz : 0) >= pos) return find(t->l, pos);
        else if(sz(t->l) == pos - 1) return t->val; // You may want to change to t->val
        else return find(t->r, pos - sz(t->l) - 1);
    }
    // 1-indexed
    void update(int l, int r, T val, bool rev) {
        node L, M, R;
        split(root, L, M, l - 1), split(M, M, R, r - l + 1);
        M->lazy += val, M->rev ^= rev;
        merge(root, L, M), merge(root, root, R);
    }
};
