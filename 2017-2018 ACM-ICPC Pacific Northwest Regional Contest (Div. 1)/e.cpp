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
     
    double sq(double x){
     
    	if(x <0) return -1;
     
    	double ans = sqrt(x);
    	//dbg(x);
    	double l = ans - 2;
    	double r = ans + 2;
     
     
    	fr(i,60){
    		double m = (l + r)/2;
     
    		if(m*m < x) l = m;
    		else r = m;
     
    		ans = m;
    	} 
     
    	return ans;
     
     
    }
     
    int main(){
     
    	fastio;
     
    	cout << setprecision(3) << fixed;
     
    	int n;
    	double x;
    	double v;
     
    	cin >> n >> x >> v;
     
    	double sum = 0;
     
    	fr(i,n){
    		int l,r;
    		cin >> l >> r;
    		double vv;
    		cin >> vv;
    		sum += (double)(r - l)*vv;
    	}
     
    	double vy = -sum/x;
     
     
    	double vx = sq(v*v - vy*vy);
     
    	
     
    	if(vx < v/2){
    		cout << "Too hard" << endl;
    		return 0;
    	}
     
    	double t = x/vx;
     
    	double  T = x/v;
     
    	
     
    	
    	cout << t << endl;
    	
     
    }