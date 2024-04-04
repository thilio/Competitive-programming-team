/*  Complexity: O(n^{log_2(3)})
    Description: 
        - fast multiplication of two polynomials
        - better than FFT when n is small(<= 30000) or when its
        size differs a lot*/
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (n); ++i)
// Complexity O(A * B^0.6) where A >= B.
template<typename T> void rec_kara(T* a, int one, T* b, int two, T* r) { // by UW/Errichto
    if(min(one, two) <= 20) { // must be at least "<= 1"
        REP(i, one) REP(j, two) r[i+j] += a[i] * b[j];
        return;
    }
    const int x = min(one, two);
    if(one < two) rec_kara(a, x, b + x, two - x, r + x);
    if(two < one) rec_kara(a + x, one - x, b, x, r + x);
    const int n = (x + 1) / 2, right = x / 2;
    vector<T> tu(2 * n);
    rec_kara(a, n, b, n, tu.data());
    REP(i, 2 * n - 1) {
        r[i] += tu[i];
        r[i+n] -= tu[i];
        tu[i] = 0;
    }
    rec_kara(a + n, right, b + n, right, tu.data());
    REP(i, 2 * right - 1) r[i+n] -= tu[i], r[i+2*n] += tu[i];
    tu[n-1] = a[n-1]; tu[2*n-1] = b[n-1];
    REP(i, right) tu[i] = a[i]+a[i+n], tu[i+n] = b[i]+b[i+n];
    rec_kara(tu.data(), n, tu.data() + n, n, r + n);
}
template<typename T> vector<T> karatsuba(vector<T> a, vector<T> b) {
    if(a.empty() || b.empty()) return {};
    vector<T> r(a.size() + b.size() - 1);
    rec_kara(a.data(), a.size(), b.data(), b.size(), r.data());
    return r;
}
vector<int> r(int n) {
    vector<int> w;
    for(int i = 0; i < n; ++i) w.push_back(rand() % 10);
    return w;
}