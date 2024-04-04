/*
	Title: Z-function
	Description: algorithm to compute the z-function of a given string
 	Complexity: O(n)
	Details:
			0-indexed.
			z[i] is the largest common prefix between the string s
			and the suffix of s starting at i.
			z[0] = 0 for convenience.
	Credits: https://cp-algorithms.com/string/z-function.html
*/

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;	
    }
    return z;
}
