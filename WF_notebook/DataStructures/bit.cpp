struct BIT{
    vector<int> bit;
    int n;
    BIT(int tam = 0){n = tam, bit.resize(n + 1, 0);}
    BIT(vector<int> & a){
        n = (int)a.size(), bit.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) update(i, a[i-1]);
    }
    BIT(int a[], int tam){
        n = tam, bit.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) update(i, a[i-1]);
    } 
    inline int op(int x, int y) {return x + y;}
    void update(int i, int val){
        for(; i <= n; i += i & (-i)) bit[i] = op(bit[i], val);
    }
    int query(int i){
        int sum = 0; // NEUTRAL: if op=min, use sum=INF
        for(; i > 0; i -= i & (-i)) sum = op(sum, bit[i]);
        return sum;
    }
    int lower_bound(int v){
	    int pos = 0, sum = 0; // NEUTRAL: if op=min, use sum=INF
        for(int i = (int)ceil(log2(n)); i >= 0; i--){
            if(pos + (1 << i) < n && op(sum, bit[pos + (1 << i)]) < v){
                sum = op(sum, bit[pos + (1 << i)]);
                pos += (1 << i);
            }
        }
	    return pos + 1; 
    } 
};