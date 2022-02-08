/*
	Title: Library for matrix operations

*/

using T = double;
typedef vector<vector<T>> matrix;

matrix operator * (matrix & a, matrix & b){
    int n = a.size(), m = b[0].size();
    if(a[0].size() != b.size()) assert(0);
    matrix ret;
    ret.resize(a.size());

    for(int i = 0; i < n; i++){
        ret[i].resize(m, 0);
        for(int j = 0; j < m; j++){
            for(int k = 0; k < b.size(); k++){
                ret[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ret;
}

matrix operator + (matrix & a, matrix & b){
    int n = a.size(), m = a[0].size();
    if(n != b.size() || m != b[0].size()) assert(0);
    matrix ret(n)
    for(int i = 0; i < n; i++){
        ret[i].resize(m, 0);
        for(int j = 0; j < m; j++) ret[i][j] = a[i][j] + b[i][j];
    }
    return ret;
}

matrix operator - (matrix & a, matrix & b){
    int n = a.size(), m = a[0].size();
    if(n != b.size() || m != b[0].size()) assert(0);
    matrix ret(n)
    for(int i = 0; i < n; i++){
        ret[i].resize(m, 0);
        for(int j = 0; j < m; j++) ret[i][j] = a[i][j] - b[i][j];
    }
    return ret;
}

/*
	Title: Gauss-Jordan elimination algorithm 
    Description: Find the inverse of a given matrix A
	Complexity: O(n^3)

    Details:
		- It returns in matrix b the inverse of a, if it exists.
		- Return true if the inverse exists and false otherwise
*/
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

/*
	Title: Algorithm to find determinant of matrix A
    Description: Algorithm to find determinant of matrix A
    Complexity: O(n^3)
*/
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