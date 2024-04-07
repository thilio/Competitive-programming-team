/* Computes the minimal lex. matching in a bip. graph
Complexity: O(V^4 + matching)
Needs the adjacency of both sides.
Minimizaing with respect to the right side. 
Compute an initial matching. The proof uses simmetrical 
differences to find an alternating cycle*/
int visu[MAXN], visv[MAXN];
void min_lex_matching(){
	hopcroftKarp(); // can be any algorithm.
	
	for (int v = 1; v <= m /*right size*/; v++){
		for (int j = 1; j <= m /*both sides size*/; j++)
			visu[j] = visv[j] = -1;

		queue<int> fila;
		fila.push(v + m); 
		// Here, right vertices are shifted to differentiate
		visv[v] = 0;

		while (!fila.empty()){
			int vtx = fila.front();
			fila.pop();
			if (vtx <= m){ // On the left
				for (auto y : adju[vtx])
					if (y!=matchu[vtx] and visv[y]<0 and y>=v){
						// y >= v because of the lex restriction
						visv[y] = vtx; // I visited through vtx
						fila.push(y + m);
					}
			}
			else{
				vtx -= m;
				if (vtx >= v){ 
// It should be alternating, I can only use matching edge					
					visu[matchv[vtx]] = vtx;
					fila.push(matchv[vtx]);
				}	
			}
		}
		// I'll try a new matching, using an alternating cycle
		for (auto u : adjv[v]){
			if (u < matchv[v] and visu[u] > 0){ 
				// It's better and I can match this
				int pv = matchu[u];matchu[u] = v;matchv[v] = u;
				while (pv != v){
					int pu = visv[pv], aux = matchu[pu];
					matchv[pv] = pu; matchu[pu] = pv; pv = aux;
				}	
				break; // I got the smallest lex, leaving
			}
		}	
	}
}