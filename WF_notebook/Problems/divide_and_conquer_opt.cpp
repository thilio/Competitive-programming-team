/*Divide and conquer DP optimization
Divides n elements in m non-empty groups O(nmlog(n))

We can optimize this naive DP
pd(m, n) = min_{1<=k<n}{pd(m - 1, k) + c[k + 1][n]}, O(nm^2)
if A[i][j]<=A[i][j+1], where A[i][j] is a opt. split point
(k from the rec.) for the interval v[1...j] with i parts.
Opt. spliting is monotone increasing in j.
Sufficient cond: C[a][d]+C[b][c]>=C[a][c]+C[b][d], a<b<c<d.

Problem: Split n elements in k continuous groups such that
the sum of the product of the weights moved is minimized*/
ll n, m, u[MAXN]; 
ll sum[MAXN], acum[MAXN];
ll dp_before[MAXN], dp_cur[MAXN];
// Opt splitting for l <= j <= r is in [optl, optr] 
void compute(ll l, ll r, ll optl, ll optr){//O(nmlong(m))
	if (l > r) return;

	ll mid = (l + r) >> 1, vmid = llINF, opt = optl;
	for (ll k = optl; k <= min(mid, optr); k++){
		ll val = dp_before[k] + sum[mid] - sum[k] - 
											(acum[mid] - acum[k]) * k;
		if (vmid > val) vmid = val, opt = k;
	}
	dp_cur[mid] = vmid;
	compute(l, mid - 1, optl, opt); //A[m][mid-1]<=A[m][mid]
	compute(mid + 1, r, opt, optr); //A[m][mid]<=A[m][r]
}
 ll pd(){
	for (int i = 1; i <= n; i++) // 1 group
		dp_cur[i] = sum[i];
	dp_cur[0] = llINF;
	
	for (ll i = 1; i < m; i++){ // all group sizes
		memcpy(dp_before, dp_cur, sizeof dp_cur); // i groups.
		compute(1, n, 1, n); // i + 1 groups.
	}
	return dp_cur[n];
}
/* acum[i] -> sum of the weights from 1 to i
	sum[i] -> cost of moving a pile from i to 1*/