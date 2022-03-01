/*
    Title: Treap data structure
    Description: It's a BST by "key" and a heap by "prior" and this property
    makes it sufficiently balanced(its height is O(log size) in general)
    Complexity: all operations are O(log size)
    Details:
        1) push(node t):
            Do the push of lazy properties to t's sons
        2) split(node t, K key, node & l, node & r):
            Split the nodes in the subtree rooted on "t" into two:
                - l will contain all nodes which are <= key
                - r will contain all nodes which are > key
        3) merge(node & t, node l, node r):
            Merge trees "l" and "r" int one rooted on t. It's assumed
            that all keys in "l" <= all keys in "r"
        4) insert(node & t, node it):
            Insert node "it" in the treap rooted in "t". If there is a 
            tie in the key comparison, this node "it" will go more to
            the right
        5) void erase(node & t, K key)
            Erase the first node with key "key" that it encounters
        6) T prefix_sum(node t, K key)
            Return the sum of all values with keys <= "key"
        7) K find(node t, int pos)
            Return the key that is in position "pos" (1-indexed)
        

        In general, hard Treap problems require modifying this code
*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename K, typename T>
struct Treap{
    struct item {
        int prior, sz;
        K key;
        T val, sum;
        item *l, *r;
        item (K k = 0, T v = 0){
            key = k, prior = rng(), l = r = nullptr;
            val = v, sz = 1, sum = v;
        }
    };
    typedef item* node;
    node root;
    void push(node t) {
        if(t) {
            t->sum += t->lazy * t->sz, t->val += t->lazy;
            if(t->l) t->l->lazy += t->lazy;
            if(t->r) t->r->lazy += t->lazy;
           t->lazy = 0;
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
    void split (node t, K key, node & l, node & r) {
        push(t);
        if(!t) l = r = nullptr;
        else if(t->key <= key) split(t->r, key, t->r, r), l = t;
        else split(t->l, key, l, t->l), r = t;
        upd(t);
    }
    // All keys in l must be less than r
    void merge (node & t, node l, node r) {
        push(l), push(r);
        if(!l || !r) t = l ? l : r;
        else if(l->prior > r->prior) merge (l->r, l->r, r), t = l;
        else merge (r->l, l, r->l), t = r;
        upd_sz(t);
    }
    void insert(node & t, node it) {
        push(t);
        if (!t) t = it;
        else if (it->prior > t->prior) split(t, it->key, it->l, it->r), t = it;
        else insert(t->key <= it->key ? t->r : t->l, it);
        upd_sz(t);
    }
    void erase(node & t, K key) {
        push(t);
        if (t->key == key) {
            node th = t;
            merge(t, t->l, t->r);
            delete th;
        }
        else erase (key < t->key ? t->l : t->r, key);
        upd_sz(t);
    }

    // Interface
    void insert(K key, T val){insert(root, new item(key, val));};
    void erase(K key){erase(root, key);};
    T prefix_sum(node t, K key){
        push(t);
        if(t == nullptr) return 0;
        if(t->key > key) return prefix_sum(t->l, key);
        else return (t->l ? t->l->sum : 0) + t->val + prefix_sum(t->r, key);
    }
    K find(node t, int pos){
        push(t);
        if(t == nullptr) return -100000000;
        if((t->l ? t->l->sz : 0) >= pos) return find(t->l, pos);
        else if((t->l ? t->l->sz : 0) == pos - 1) return t->key;// You may want to change to t->val
        else return find(t->r, pos - (t->l ? t->l->sz : 0) - 1);
    }
};