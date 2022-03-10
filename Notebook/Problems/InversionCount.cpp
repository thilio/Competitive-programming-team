#include "bits/stdc++.h"
using namespace std;

/*
   Title: Number of inversions between two arrays
   Description: given two arrays l and r, returns
   				the minimum number of inversions
   				to transform l in r.
   Complexity: O(n log n)
   Details: inv_count count the number of inversions
   			in a permutation of [1, ..., n].
   			inv_count_2 solves the more general problem
   			reducing to the first case. If it is not
   			possible to transform l in r it returns -1.
   Credits: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/InversionCount.cpp
*/

long long int inv_count(vector<int> &v, int l, int r){
	if(l >= r){
		return 0;
	}

	long long int ans = 0;
	int m = (l + r)/2;

	ans += inv_count(v, l, m);
	ans += inv_count(v, m + 1, r);

	int p = l;
	int q = m + 1;

	vector<int> aux;

	while(p <= m || q <= r){
		if(q > r){
			aux.push_back(v[p++]);
		}
		else if(p > m){
			aux.push_back(v[q++]);
		}
		else{
			if(v[q] < v[p]){
				aux.push_back(v[q++]);
				ans += m - p + 1;
			}
			else{
				aux.push_back(v[p++]);
			}
		}
	}

	for(int i = 0; i < aux.size(); i++)
		v[l + i] = aux[i];

	return ans;

}

long long int inv_count_2(vector<int> l, vector<int> r = {}){
	if(!r.size()){
		r = l;
		sort(r.begin(), r.end());
	}

	vector<pair<int, int>> w;
	vector<int> v;
	for(int i = 0; i < r.size(); i++) w.push_back({r[i], i + 1});

	sort(w.begin(), w.end());

	for(auto x: l){
		auto it = lower_bound(w.begin(), w.end(), make_pair(x, 0));
		if(it == w.end() || it -> first != x) return -1;
		v.push_back(it -> second);
		it -> second = -1;
	}

	return inv_count(v, 0, (int)v.size() - 1);
}
