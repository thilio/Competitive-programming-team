/*
    Title: Euler totient function

    Description: Build phi[i] for all i < MAXN

    Complexity: O(n)
*/

const int MAXN = 10000010;
int lp[MAXN], phi[MAXN];
vector<int> pr;

void sieve(){
    for (int i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        for(auto p : pr){
            if(p > lp[i] || i * p >= MAXN) break;
            lp[i * p] = p;
        }
    }

    for (int i = 2; i < MAXN; ++i) {
        if((i / lp[i]) % lp[i] == 0) phi[i] = phi[i / lp[i]] * lp[i];
        else phi[i] = phi[i / lp[i]] * (lp[i] - 1);
    }
}