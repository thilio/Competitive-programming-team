/*
	Title: Division trick
	Description: Generate the set floor(n / i) for all 1 <= i <= n
	Complexity: O(sqrt(n))
	Credits: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/divisionTrick.cpp
*/
for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// n / i has the same value for l <= i <= r
}

/*
	Title: All submasks
	Description: Iterate over all submasks of all masks
	Complexity: O(3^n)
*/
for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)

/*
	Title: All inverse
	Description: Find all inverses mod m
	Complexity: O(m)
    Credits: https://cp-algorithms.com/algebra/module-inverse.html#toc-tgt-3
*/

const int MOD = 1000001;
int inv[MOD];
void all_inverse(){
	inv[1] = 1;
	for(int i = 2; i < m; ++i)
	    inv[i] = m - (m/i) * inv[m%i] % m;
}


/*
	Pick Theorem: 
	Given a not necessarily convex polygon P whose verties with lattice
	coordinates, its area is given by:

		Area = B / 2 + I - 1

	B = number of lattice points in the border of P
	I = number of lattice points strictly inside P
*/

/*
	Euler Theorem(Planar graphs):
	Given a planar graph, we have the following:

		V - E + F = C + 1

	V = number of vertices
	A = number of edges
	F = number of faces
	C = number of components
*/