/*
   Title: Lagrange Interpolation 
   Description: given n points evaluates the unique polynomial
   				with degree < n. 
   Complexity: interpolate O(n^2), interpolate_linear O(n).
   Details: We recommend using this functions with double or
   			mint (https://github.com/thilio/Competitive-programming-team/blob/main/Notebook/Math/modInt.cpp).
   			When using double the precision errors may be large even for small polynomials (degree ~50).
   			When using mint watch out for negative values in the given points. Moreover, both functions
   			are slow since we have a lot of modular operations. If delta == 1 we can speed up the linear
   			algorithm removing the division by the variable constant.
   			Interpolate() works for any given points, interpolate_linear() needs the points to be equally spaced
   			in the x - axis.
   Interface description:
			Interpolate() receive the x-coordinate of the points and the y-coordinates and evaluate the
			interpolation at point p.
			interpolate_linear() receive a point x[0] and a delta, it assumes that x[i] = x[0] + i*delta,
			it also receives the y-coordinate of the points and evaluate the interpolation at point p.
*/

template<typename T>
T interpolate(vector<T> &x, vector<T> &y, T p){
	T ans = 0;
	int n = x.size();

	for(int i = 0; i < n; i++){
		T term = y[i];
		for(int j = 0; j < n; j++)
			if(j != i){
				term = term*(p - x[j]);
				term = term/(x[i] - x[j]);
			}
		ans = ans + term;
	}

	return ans;
}
template<typename T>
T interpolate_linear(T x0, T delta, vector<T> &y, T p){
	T ans = 0;
	int n = y.size();
	vector<T> pref(n), suf(n), fat(n), ifat(n);

	T constant = 1;

	pref[0] = p - x0;
	for(int i = 1; i < n; i++)
		pref[i] = pref[i - 1]*(p - x0 - (T)i*delta);

	suf[n - 1] = p - x0 - (T)(n - 1)*delta;
	for(int i = n - 2; i >= 0; i--)
		suf[i] = suf[i + 1]*(p - x0 - (T)i*delta);

	fat[0] = 1; 
	for(int i = 1; i < n; i++){
		fat[i] = (T)i*fat[i - 1];
		constant = constant*delta;
	}
	ifat[n - 1] = (T)1/fat[n - 1];
	for(int i = n - 2; i >= 0;i--){
		ifat[i] = (T)(i + 1)*ifat[i + 1];
	}

	for(int i = 0; i < n; i++){
		T term = 1;
		if(i != 0) term = term*pref[i - 1];
		if(i != n - 1) term = term*suf[i + 1];

		term = term/constant;
		term = term*ifat[i];
		term = term*ifat[n - 1 - i];
	
		if((n - 1 - i)&1) term = (T)0 - term; // this line looks silly but it is important for modular arithmetic

		term = term*y[i];
		ans = ans + term;
	}

	return ans;
}
