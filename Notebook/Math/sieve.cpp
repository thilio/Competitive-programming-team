/*
    Title: Linear sieve of Erastothenes
    Description: Find all prime numbers up to MAXN
    Complexity: O(n)

    Details:
        - lp[i] is the smallest prime factor of i
        - pr is the vector of primes up to MAXN

    Credits: https://cp-algorithms.com/algebra/prime-sieve-linear.html 
*/

const int MAXN = 10000010;
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

/*
    Decompose a number in prime factors, using the sieve above.
    It returns a vector of pairs of the form {prime, exp}.

    Complexity: O(log n + number of prime factors)
*/

vector<pair<int, int>> decompose(int n){
    vector<pair<int, int>> ret;
    while(n > 1){
        pair<int, int> p = {lp[n], 0};
        while(lp[n] == p.first){
            p.second++;
            n /= p.first;
        }
        ret.push_back(p);
    }
    return ret;
}