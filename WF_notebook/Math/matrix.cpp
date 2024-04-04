using T = double;
typedef vector<vector<T>> matrix;
/*  Complexity: O(n^3)
    - It returns in matrix b the inverse of a, if it exists.
    - Return true if the inverse exists and false otherwise*/
bool inverse (matrix a, matrix & b) {
    int n = (int)a.size();
    b.resize(n);
    for(int i = 0; i < n; i++) b[i].resize(n), b[i][i] = 1;

    for (int it = 0; it < n; it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (abs(a[i][it]) > abs(a[sel][it])) sel = i;
        if (abs(a[sel][it]) < eps) return false;

        for (int i = 0; i < n; i++) 
            swap (a[sel][i], a[it][i]), swap(b[sel][i], b[it][i]);

        T c = a[it][it];
        for (int i = 0; i < n; i++) 
            a[it][i] /= c, b[it][i] /= c;

        // Eliminate all entries in the column it
        for (int i = 0; i < n; i++) 
            if (i != it) {
                c = a[i][it];
                for (int j = 0; j < n; j++)
                    a[i][j] -= a[it][j] * c, b[i][j] -= b[it][j] * c;
            }
    }
    return true;
}
/*  Description: Algorithm to find determinant of matrix A
    Complexity: O(n^3)*/
T determinant(matrix a) {
    int n = (int)a.size();
    T ret = 1;
    for (int it = 0; it < n; it++) {
        // Firtly, take the row with largest entry to be the pivot
        int sel = it;
        for (int i = it; i < n; i++) 
            if (abs(a[i][it]) > abs(a[sel][it])) sel = i;
        if (abs(a[sel][it]) < eps) return false;

        for (int i = 0; i < n; i++) 
            swap (a[sel][i], a[it][i]);
        T c = a[it][it];
        for (int i = 0; i < n; i++) 
            a[it][i] /= c;
        ret *= c;
        // Eliminate all entries in the column it
        for (int i = 0; i < n; i++) 
            if (i != it) {
                c = a[i][it];
                for (int j = 0; j < n; j++)
                    a[i][j] -= a[it][j] * c;
            }
    }
    return true;
}