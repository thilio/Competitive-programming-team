/*
   Title: Algorithm for minimal lexicographic perfect matching
   Description: Computes the minimal lex. matching in a bip. graph
   Complexity: O(V^4 + matching)
   Details: We most have the adjacency of both sides.
   		Here, we are minimizaing with respect to the right side, ie, right side 
   		has the preference. One may use any mathing algorithm to compute
   		the initial matching. Must be used aloinde a maximal matching algorithm;

   		The proof use simmetrical difference to produce e alternating cycle (hence, 
   		perfect matching), one may have to modify a bit if the matching is not perfect.
*/

int visu[MAXN], visv[MAXN];
void min_lex_matching(){ // O(V^4 + matching)
	hopcroftKarp(); // We will modify a initial matching, can be any algorithm.
	
	for (int v = 1; v <= m /*right size*/; v++){ // We want to minimize for the right side
		for (int j = 1; j <= m /*both sides size*/; j++)
			visu[j] = visv[j] = -1;

		queue<int> fila;
		fila.push(v + m); // Here, right vertices are shifted to differentiate
		visv[v] = 0;

		while (!fila.empty()){
			int vtx = fila.front();
			fila.pop();

			if (vtx <= m){ // On the left
				for (auto y : adju[vtx])
					if (y != matchu[vtx] and visv[y] < 0 and y >= v){ // y >= v because of the lex restriction
						visv[y] = vtx; // I visited through vtx
						fila.push(y + m);
					}
			}
			else{
				vtx -= m;
				if (vtx >= v){ // It should be alternating, I can only use matching edge
					visu[matchv[vtx]] = vtx;
					fila.push(matchv[vtx]);
				}	
			}
		}

		// Now I will try a new matching, through a alternating cycle
		for (auto u : adjv[v]){
			if (u < matchv[v] and visu[u] > 0){ // It's better and I can match this
				int pv = matchu[u];

				matchu[u] = v;
				matchv[v] = u;

				while (pv != v){
					int pu = visv[pv];
					int aux = matchu[pu];
					
					matchv[pv] = pu;
					matchu[pu] = pv;
					pv = aux;
				}	

				break; // I got the smallest lex, leaving
			}
		}	
	}
}