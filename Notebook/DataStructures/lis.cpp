/*
	Longest Increasing Subsequence

	Description: find the longest increasing subsequence of a given vector

	Complexity: O(n log n)
*/

int lis(vector<int> const& a) {
    int n = a.size();
    vector<int> lis;

    for(int i = 0; i < n; i++){
        auto pos = upper_bound(lis.begin(), lis.end(), a[i]);
        if(pos == lis.end()) lis.push_back(a[i]);
        else *pos = a[i];
    }
    
    return ans;
}