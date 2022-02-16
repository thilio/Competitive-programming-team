/*
   Title: Gale–Shapley's algorithm for the stable marriege problem
   Description: Finds a stable marriage between two sets
   Complexity:  stable_marriage O(# of prefrences + n + m)
   		   
   Details: A stable marriage is a "matching" such that no simple exchange
   leads to a new pair being more satisfied (both members of the new pair
   prefer each other more).

   This algorithm retuns the best possible assignment for the men side and
   te worst possible for the women.

   When a woman may be assined for many men, add the capacity of each woman + a
   priority queue.
*/

int n, m; // # of men and women
vector<int> lista[MAXN]; // list of woman for each man
int nota[MAXN][MAXN]; // rank that each woman give for each man
int matchn[MAXN], matchm[MAXN]; // pair of each member
int p[MAXN]; // progress for each man

void stable_marriage(){
	fill(matchm, matchm + m, -1);
	fill(p, p + n, 0);
	int hubby, man, wom;
	for (int i = 0; i < n; i++){
		man = i;
		while (man != -1){
			bool ok = 0;
			while (!ok and p[man] < lista[man].size()){
				wom = lista[man][p[man]++];
				if (matchm[wom] == -1 or nota[wom][man] > nota[wom][matchm[wom]]) 
					ok = 1;
			}
			if (!ok){
				matchn[man] = -1;
				man = -1;
			}
			else{
				hubby = matchm[wom];
				matchm[wom] = man;
				matchn[man] = wom;
				man = hubby;
			}
		}
	}
}
