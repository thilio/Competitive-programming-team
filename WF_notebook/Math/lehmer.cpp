/*Complexity: Roughly ~O(n^(2/3))
Description:
        - lehmer(n) returns the number of primes not exceeding n
        - phi(n) return the euler totient function for number n*/
/// Magic constants, optimized to answer prime counting queries for n=10^12 but can be tweaked
#define MAXN 20000010
#define MAXPR 7
#define MAXIT 50
const int MAXM = 2 * 3 * 7 * 5 * 11 * 13 * 17; /// Product of the first MAXPR primes
constexpr auto fast_div = [](const long long& a, const int& b) ->long long {return double(a) / b + 1e-9;};
vector<int> primes;
vector<int> lp(MAXN, 0);
int prod[MAXPR], pi[MAXN], dp[MAXIT][MAXM];
void sieve(){
    for (int i=2; i < MAXN; i++) {
        pi[i] = pi[i - 1] + (lp[i] == 0);
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back (i);
        }
        for (int j=0; j<(int)primes.size() && primes[j] <= lp[i] && i*primes[j] < MAXN; ++j)
            lp[i * primes[j]] = primes[j];
    }
}
void gen(){
    int i, j;
    assert(MAXIT >= MAXPR);
    sieve();
    for (prod[0] = primes[0], i = 1; i < MAXPR; i++)
        prod[i] = prod[i - 1] * primes[i];

    for (i = 0; i < MAXM; i++) dp[0][i] = i;
    for (i = 1; i < MAXIT; i++)
        for (j = 1; j < MAXM; j++)
            dp[i][j] = dp[i - 1][j] - dp[i - 1][fast_div(j, primes[i - 1])];
}
uint64_t phi(long long m, int n){
    if (!n) return m;
    if (n < MAXIT && m < MAXM) return dp[n][m];
    if (n < MAXPR) return dp[n][m % prod[n - 1]] + fast_div(m, prod[n - 1]) * dp[n][prod[n - 1]];
    long long p = primes[n - 1];
    if (m < MAXN && p * p >= m) return pi[m] - n + 1;
    if (p * p * p < m || m >= MAXN) return phi(m, n - 1) - phi(fast_div(m, p), n - 1);
    int lim = pi[(int)sqrt(0.5 + m)];
    uint64_t res = pi[m] - (lim + n - 2) * (lim - n + 1) / 2;
    for (int i = n; i < lim; i++){
        res += pi[fast_div(m, primes[i])];
    }
    return res;
}
uint64_t lehmer(long long n){
    if (n < MAXN) return pi[n];
    int s = sqrt(0.5 + n), c = cbrt(0.5 + n);
    uint64_t res = phi(n, pi[c]) + pi[c] - 1;
    for (int i = pi[c]; i < pi[s]; i++){
        res -= lehmer(fast_div(n, primes[i])) - i;
    }
    return res;
}
int main(){
    gen();
    assert(lehmer(7) == 4); assert(lehmer(1000) == 168); 
    assert(lehmer(1e12) == 37607912018LL);
}
