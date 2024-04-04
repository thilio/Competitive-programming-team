/*  1) Pollard-rho algorithm (rho(n))
        - Find a prime factor of a givern number n
        - Complexity: O(n^{1/4})
    2) Miller Rabin (isPrime(n))
        - Determine if a given number is prime
        - Works for all n up to 7 * 10^18
        - Complexity: O(7 * log(n))
    3) Factorization (factor(n))
        - Factorize a number give number n
        - Complexity: O(n^{1/4} * log(n))*/
namespace randNT{
    typedef long long int u64;
    u64 modmul(u64 a, u64 b, u64 M) {
        ll ret = a * b - M * u64(1.L / M * a * b);
        return ret + M * (ret < 0) - M * (ret >= (ll)M);
    }
    u64 modpow(u64 b, u64 e, u64 mod) {
        u64 ans = 1;
        for (; e; b = modmul(b, b, mod), e /= 2)
            if (e & 1) ans = modmul(ans, b, mod);
        return ans;
    }
    bool isPrime(u64 n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        u64 A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
            s = __builtin_ctzll(n-1), d = n >> s;
        for (u64 a : A) {   // ^ count trailing zeroes
            u64 p = modpow(a%n, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = modmul(p, p, n);
            if (p != n-1 && i != s) return 0;
        }
        return 1;
    }
    u64 pollard(u64 n) {
        auto f = [n](u64 x) { return modmul(x, x, n) + 1; };
        u64 x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 || __gcd(prd, n) == 1) {
            if (x == y) x = ++i, y = f(x);
            if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
            x = f(x), y = f(f(y));
        }
        return __gcd(prd, n);
    }
    vector<long long> factor(u64 n) {
        if (n == 1) return {};
        if (isPrime(n)) return {(long long)n};
        u64 x = pollard(n);
        auto l = factor(x), r = factor(n / x);
        l.insert(l.end(), all(r));
        return l;
    }
};  