/*
	Title: Knuth-Morris-Pratt algorithm
	Description: Pattern searching algorithm.
	Complexity:
		lps_p : O(|pat|)
		check : O(|pat| + |txt|)

	Details:
		- You may easily change function 'check' to return all ocurrences of pat
*/

template<typename T>
vector<int> lps_p(T pat){
	int i = 1, len = 0, tam = (int)pat.size();
	vector<int> lps(tam, 0);
	lps[0] = 0;

	while(i < tam){
		if(pat[i] == pat[len]) lps[i++] = ++len;
		else if(len != 0) len = lps[len-1];
		else lps[i++] = 0;
	}

	return lps;
}

template<typename T>
int check(T txt, T pat){
	int i = 0, j = 0, tt = (int)txt.size(), tp = (int)pat.size(), ans = 0;
	vector<int> lps = lps_p(pat);

	while(i < tt){
		if(txt[i] == pat[j]) i++,j++;
		if(j == tp) ans++, j = lps[j-1];
		else if(i < tt && txt[i] != pat[j]){
			if(j == 0) i++;
			else j = lps[j-1];
		}
	}

	return ans;
}