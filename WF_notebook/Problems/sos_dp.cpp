/*Sum over subsets DP (SOS DP)
Apply a function in all subsets of a binary representation.
Complexity: O(n 2**n)
Run through all subsets of a given representation. 
May be used to compute sums, gcd, etc...
Problem : Given a list of 10^6 elements, one most find for 
each number if there is another number in the list such that 
the bitwise AND of the binary represntations is zero. 
If there is, print it */
const int MAXN = 1<<22;
int n, v[MAXN], a[MAXN], memo[MAXN];
void sos(){
	for (int msk = 0; msk <(1<<22); msk++)
		memo[msk] = a[msk]; // I produce this representation 
	for (int i = 0; i < 22; i++)
		for (int msk = 0; msk < (1<<22); msk++)
			if ((msk & (1<<i)))
				memo[msk] = max(memo[msk],memo[msk^(1<<i)]); 
				// there is someone greather than zero
				// memo[msk] += memo[msk^(1<<i)]; for sums
}
/* a[v] original index containing value v
main:
sos();
	int ones = (1<<22) - 1; // 22 ones
	for (int i = 1; i <= n; i++){
		if (memo[v[i]^ones] > 0)
			cout<<v[memo[v[i]^ones]]<<' ';
		else
			cout<<-1<<' ';
	}
	cout<<endl;	
*/