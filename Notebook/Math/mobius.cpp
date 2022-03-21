/*
    Title: Mobius function
    Description: Find the mobius function for all numbers < MAXN
    Complexity: O(n)
    
    Details:
    u[n] = +1 if n is a square-free positive integer with an even number of prime factors.
    u[n] = −1 if n is a square-free positive integer with an odd number of prime factors.
    u[n] = 0 if n has a squared prime factor.

    More details: https://codeforces.com/blog/entry/53925
*/

ll u[MAXN], lp[MAXN];
vector<ll> pr;
void sieve(){
    for (ll i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        for(auto p : pr){
            if(p > lp[i] || i * p >= MAXN) break;
            lp[i * p] = p;
        }
    }
    u[1] = 1;
    for (ll i = 2; i < MAXN; ++i) {
    	if((i / lp[i]) % lp[i] == 0) u[i] = 0;
    	else u[i] = -u[i / lp[i]];
    }
}