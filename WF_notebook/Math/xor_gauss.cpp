/*
    Gauss Elimination algorithm to solve linear system of equations in Z_2.

    Parameters:
        A * ans = b
        "b" comes in the last column of "a" and "A" is the rest 
    
    Return value:
        - It returns 
            - INF if there are infintely many solutions to the system,
            - 0 if there isn't any
            - 1 if there is a unique solution.
        - If there is only one solution, it returns in the vector "ans" this solution
        - If there are infinitely many, in the positions that I have a choice, it returns 0.

    Usage:
        You may call it with any size of bitset

    Complexity: 
        O(n * m * min(n, m)/ 64)
*/
const int INF = 2;
template<size_t N>
int gauss (vector < bitset<N> > a, int m, bitset<N> & ans) {
    int n = (int) a.size();

    for (int it = 0; it < min(n, m); it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (a[i][it]) {
                swap(a[i], a[it]);
                break;
            }
        if (!a[it][it]) continue;

        // Make the eliminations
        for (int i = 0; i < n; i++)
            if (i != it && a[i][it])
                a[i] ^= a[it];
    }       

    ans.reset();
    for (int i = 0; i < m; ++i) 
        if (a[i][i]) ans[i] = a[i][m] & a[i][i];
  
    // Check if actually it solves the system
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) 
            sum ^= ans[j] & a[i][j];
        if (sum != a[i][m]) return 0;
    }

    for (int i = 0; i < m; i++) 
        if (!a[i][i]) return INF;

    return 1;
}