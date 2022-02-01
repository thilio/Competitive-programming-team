#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

using coord = long double;
const long double pi = acos(-1);
const long double EPS = 1e-8;

int sign(coord x) { return (x > EPS) - (x < -EPS); }
coord sq(coord x) { return x * x; }

struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){ return {x + p.x, y + p.y}; }
	inline point operator-(point p){ return {x - p.x, y - p.y}; }
	inline point operator*(coord o){ return {x * o, y * o}; }
	inline point operator/(coord o){ return {x / o, y / o}; }
	inline void operator=(point p){ x = p.x, y = p.y; }

	inline coord operator*(point p){ return x * p.x + y * p.y; } // |a||b|cos(tht)
	inline coord operator^(point p){ return x * p.y - y * p.x; } // |a||b|sin(tht), this -> p

	inline int ccw(point p){ return sign(*this ^ p); } // ccw  1 left, 0 over, -1 right

	inline coord norm(){ return hypot(x, y); }
	inline coord norm2(){ return x * x + y * y; }

	inline point rot90(){return {-y, x}; }
	inline point rot(long double ang){ return {cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y}; }
	inline point project(point p){return p * (((*this) * p)/p.norm2()); }

	inline bool operator<(point &p){ return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lex_sort
	inline bool operator==(point p){ return sign(x - p.x) == 0 and sign(y - p.y) == 0; }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

void swap(point &a, point &b){ point aux = a; a = b; b = aux; }

struct line {
	point p; coord c; //p * <x,y> = c
	line() {} line(point _p, coord _c): p(_p), c(_c) {}
	line(point a, point b) : p((b - a).rot90()), c(p * a) {}
	line get_parall(point v){ return line(p, p * v); }// parallel line at point v
	line get_perp(){ return line(p.rot90(), c); }// perpendicular line

	bool contains(point v){ return sign(p * v - c) == 0; }
	bool intsec(line l){ return sign(p ^ l.p) != 0; } // false if is the same line

	coord dist(point v){ return abs(p * v - c) / p.norm(); }

	point get_intsec(line l){ coord d = p^l.p; return point((c*l.p.y - l.c*p.y)/d, (p.x*l.c - c*l.p.x)/d); }
};

struct segment {
	point a, b; // a != b
	segment() {} segment(point _a, point _b): a(_a), b(_b) {}

	bool contains(point p){ return sign((p-a)^(b-a)) == 0 and sign((p-a)*(b-a)) >= 0 and sign((p-b)*(a-b)) >= 0; }
	
	int ccw(point p){ return((b - a).ccw(p)); } // ccw  -1 left, 0 over, 1 right  of seg a->b

	bool intsec(segment q){ segment p = *this;
		if (p.contains(q.a) or p.contains(q.b) or q.contains(p.a) or q.contains(p.b))
			return true;
		return p.ccw(q.a-p.a)*p.ccw(q.b-p.a) == -1 and q.ccw(p.a-q.a)*q.ccw(p.b-q.a) == -1;	
	}
	
	coord len2(){ return (a - b).norm2(); }

	coord dist(segment q){segment p = *this; 
		return p.intsec(q)? 0 : min({p.dist(q.a), p.dist(q.b), q.dist(p.a), q.dist(p.b)});	}

	coord dist(point p){
		if (sign(((p - a) * (b - a))) >= 0 and sign((p - b) * (a - b)) >= 0)
			return abs((p - a) ^ (b - a)) / (b - a).norm();
		return min((p - a).norm(), (p - b).norm());
	}

	line getline(){return line(a, b); }
};

segment wall[MAXN];
line sweep;
point center, refp;
int s, k, w;

/*
	se second é 0, então o ponto é criança, se não:
	é o índice da parede.*/
vector<pair<point, int>> points;

struct CustomCompare{
    bool operator()(const int& lhs, const int& rhs){
        point inter1 = sweep.get_intsec(wall[lhs].getline()), inter2 = sweep.get_intsec(wall[rhs].getline());
        return (inter1 - center).norm() < (inter2 - center).norm();
    }
};

coord angle[MAXN];

bool comp(pair<point, pii> & a, pair<point, pii> & b){
	return angle[a.s.s] < angle[b.s.s];
}

bool intersecSegLine(line l, segment s){
	line aux = s.getline();
	if(l.intsec(aux)){
		point inter = l.get_intsec(aux);
		if(min(s.a.x, s.b.x) <= inter.x && (inter.x <= max(s.a.x, s.b.x)) && 
			min(s.a.y, s.b.y) <= inter.y && (inter.y <= max(s.a.y, s.b.y))
			&& (refp.x - center.x)*(inter.x - center.x) >= 0 && (refp.y - center.y)*(inter.y - center.y) >= 0) 
			return true;
		else return false;
	}
	else return false;
}

int solve(point c){
	if(k == 1) return 0;
	set<int, CustomCompare> curWalls;
	deque<pair<point, pii>> v;
	center = c;
	fr(i, points.size()){
		pair<point, pii> x = {points[i].f, {points[i].s, i}};
		if(x.f == center) continue;
		v.pb(x);
		angle[i] = asin((x.f.y - center.y)/(x.f - center).norm());
		if((x.f.x - center.x) < 0) angle[i] = (acos(-1)) - angle[i];
	}
	sort(v.begin(), v.end(), comp);

	while(v[0].s.f <= w){
		v.push_back(v.front());
		v.pop_front();
	}

	int tipo = -1;
	sweep = line(v[0].f, center);
	refp = v[0].f;
	int ans = 0;

	/*Coloca as paredes que estão ativas no momento em que começo o sweep*/
	frr(i, w){
		if(intersecSegLine(sweep, wall[i])){
			curWalls.insert(i);
		}
	}

	for(auto p : v){
		sweep = line(p.f, center);
		if(p.s.f > w){
			/*
				É criança
			*/
			if(curWalls.size() == 0)
				ans++;
			else{
				int frente = *(curWalls.begin());
				ans += ((p.f - center).norm() < (sweep.get_intsec(wall[frente].getline()) - center).norm());
			}
		}
		else{
			if(curWalls.find(p.s.f) != curWalls.end()) curWalls.erase(p.s.f);
			else curWalls.insert(p.s.f);
		}
	}

	return ans;
}

int main(){
	fastio;
	while(cin >> s >> k >> w){
		vector<point> toDo;
		frr(i, s){
			point davez;
			cin >> davez.x >> davez.y;
			toDo.pb(davez);
			points.pb({davez, w + i});
		}

		frr(i, k - s){
			point davez;
			cin >> davez.x >> davez.y;
			points.pb({davez, w + i + s});
		}
		frr(i, w){
			cin >> wall[i].a.x >> wall[i].a.y >> wall[i].b.x >> wall[i].b.y;

			points.pb({wall[i].a, i});
			points.pb({wall[i].b, i});
		}

		for(auto x: toDo){
			cout << solve(x) << endl;
		}

		points.clear();
	}
}
