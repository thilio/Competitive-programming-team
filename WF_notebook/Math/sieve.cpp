int lp[MAXN];
vector<int> pr;

void sieve(){
    for (int i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        for(auto p : pr){
            if(p > lp[i] || i * p >= MAXN) break;
            lp[i * p] = p;
        }
    }
}