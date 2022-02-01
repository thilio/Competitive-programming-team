#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

struct vv{
	int v[9];
};

typedef struct vv vv;

vv seg[400400];
int lazy[800400];

void merge(vv a, vv b,vv& c){
	
	fr(i,9){
		c.v[i] = a.v[i] + b.v[i];
	}
	
	
}

void unlazy(int node,int l,int r){
	int lc = 2*node;int rc = lc + 1;
	if(lazy[node] == 0) return;
	int f[9];
	int k = lazy[node];
	fr(i,9){
		f[i] = seg[node].v[i];
	}
	fr(i,9){
			seg[node].v[(k+i)%9] = f[i];
	}
	if(1){
		lazy[lc] += k;
		lazy[rc] += k;
	}
	lazy[node] = 0;

}

void build(int node,int l,int r){
	int lc = 2*node;int rc = lc + 1;
	int mid = (l+r)/2;
	if(l==r){
		seg[node].v[1] = 1;
		return;
	}
	build(lc,l,mid);
	build(rc,mid+1,r);

	merge(seg[lc],seg[rc],seg[node]);

}

void update(int node,int l,int r,int a,int b,int k){
	int lc = 2*node;
	int rc = lc+1;
	int mid = (l+r)/2;
	unlazy(node,l,r);

	if(r < a ||b < l||l > r) return;
	if(l >=a && r <= b){
		int f[9];
		fr(i,9){
			f[i] = seg[node].v[i];
		}
		fr(i,9){
			seg[node].v[(k+i)%9] = f[i];
		}
		
		if(l!=r){
			lazy[lc] += k;
			lazy[rc] += k;
		}
	}
	else{
		update(lc,l,mid,a,b,k);
		update(rc,mid+1,r,a,b,k);
		merge(seg[lc],seg[rc],seg[node]);
	}

}

vv null(){
	vv a;
	fr(i,9){
		a.v[i] = 0;
	}
	return a;
}

vv query(int node,int l,int r,int a,int b){
	unlazy(node,l,r);
	if(r < a || l > b|| l > r) return null();
	if(l >= a && r <= b) return seg[node];
	int lc = 2*node;int rc = lc + 1;int mid = (l+r)/2;
	vv c;
	merge(query(lc,l,mid,a,b),query(rc,mid+1,r,a,b),c);
	return c;
}


int main(){

	
	int n,q;
	scanf("%d %d",&n,&q);
	build(1,1,n);
	fr(i,q){
		int a,b;
		scanf("%d %d",&a,&b);
		a++;b++;
		vv aux = query(1,1,n,a,b);
		int ct = -1;
		int ind = 0;
		for(int i = 8;i >= 0;i--){
			if(aux.v[i] > ct){
				ct = aux.v[i];
				ind = i; 
			}
		}

		update(1,1,n,a,b,ind);
		//fr(i,9)
		//	dbg(seg[1].v[i]);
		//frr(i,n){
		//	vv aux = query(1,1,n,i,i);
		//	cout << aux.com << endl;
		//}

	}

	frr(i,n){
		vv aux = query(1,1,n,i,i);
		int ct = -1;
		int ind = 0;
		for(int i = 8;i >= 0;i--){
			if(aux.v[i] > ct){
				ct = aux.v[i];
				ind = i; 
			}
		}
		printf("%d\n",ind);
	}

}
