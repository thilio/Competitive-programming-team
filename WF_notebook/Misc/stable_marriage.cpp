/* Finds a stable marriage between two sets
stable_marriage O(# of preferences + n + m)
A stable marriage is a "matching" where no simple exchange 
leads to a new pair where both members are more satisfied.
This algorithm retuns the best possible assignment for the 
men side and tte worst possible for the women.
A woman may be assined for many men, add the capacity of 
each woman + a priority queue.*/
int n, m; // # of men and women
vector<int> lista[MAXN]; // list of woman for each man
int nota[MAXN][MAXN]; // score of each man for each woman
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
				if (matchm[wom] == -1 or 
					nota[wom][man] > nota[wom][matchm[wom]]) 
					ok = 1;
			}
			if (!ok){ matchn[man] = -1; man = -1; }
			else{
				hubby = matchm[wom];
				matchm[wom] = man; matchn[man] = wom;
				man = hubby;
			}
		}
	}
}
