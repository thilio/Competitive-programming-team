/*
    Title: Fast Fourier transform
    Description: It's used to multiply two polynomials
    Complexity: O(n log n)

    Details: The values must not be so large(must fit long long)
*/

namespace FFT {
	using cd = complex<double>;
    using ll = long long;
    const double PI = acos(-1);
    void fft(vector<cd> &a, int logN, int sign) {
        for (int i = 0; i < a.size(); i++) {
            int mask = 0;
            for (int j = 0; j < logN; j++) {
                if (i >> j & 1) mask |= (1 << logN - j - 1);
            }
            if (i < mask) swap(a[i], a[mask]);
        }
 
        for (int k = 1; k < a.size(); k <<= 1) {
            cd wDelta = polar(1.0, PI * sign / k);
            cd w(1, 0);
            for (int i = 0; i < k; i++, w *= wDelta) {
                for (int j = i; j < a.size(); j += k * 2) {
                    cd foo = a[j];
                    cd bar = w * a[j + k];
                    a[j] = foo + bar;
                    a[j + k] = foo - bar;
                }
            }
        }
    }
 
    vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
        int sz = a.size() + b.size() - 1, logN = 0;
        while ((1 << logN) < sz) logN++;

        vector<cd> aa(1 << logN, 0), bb(1 << logN, 0);

        for (int i = 0; i < a.size(); i++) aa[i] = a[i];
        for (int i = 0; i < b.size(); i++) bb[i] = b[i];

        fft(aa, logN, 1), fft(bb, logN, 1);
        for (int i = 0; i < aa.size(); i++) aa[i] *= bb[i];
        
        fft(aa, logN, -1);
        vector<ll> res(sz);
        for (int i = 0; i < sz; i++) 
            res[i] = (ll)(aa[i].real() / (1 << logN) + 0.5);

        return res;
    }
};