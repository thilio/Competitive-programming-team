/*
   Title: Manacher's Algorithm
   Description: Finds all palidromes of a string
   Complexity:  manacher O(|string|)
   Details: 
   d1[i] # of odd palindromes centered in i
   d2[i] # of even palindromes centered in i (aab[b]aa) 
   pal[2i] largest palindrome centered in i
   pal[2i + 1] largest palindrome centered in i and i + 1 

   total # of palindromes = d1[1] + ...+ d1[n] + d2[i] + ... + d2[n - 1]
*/

const int MAXN = 1e6 + 10;

int d1[MAXN], d2[MAXN];
int pal[2 * MAXN];

void manacher(string &s){
	int tam = s.size();
	for (int i = 0, l = 0, r = -1; i < tam; i++){
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    	while (0 <= i - k and i + k < tam and s[i - k] == s[i + k]) {
    	    k++;
    	}
    	d1[i] = k--;
    	if (i + k > r) {
    	    l = i - k;
		    r = i + k;
		}
	}

	for (int i = 0, l = 0, r = -1; i < tam; i++) {
	    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	    while (0 <= i - k - 1 and i + k < tam and s[i - k - 1] == s[i + k]) {
	        k++;
	    }
	    d2[i] = k--;
	    if (i + k > r) {
	        l = i - k - 1;
    		r = i + k ;
    	}
	}

	for (int i = 0; i < tam; i++)
		pal[2 * i] = 2 * d1[i] - 1;
	for (int i = 0; i < tam - 1; i++)
		pal[2 * i + 1] = 2 * d2[i + 1];
}