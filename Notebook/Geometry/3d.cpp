/*
   Title: 3D Geometry Basics Libary
   Description: 3D Geometry basics structures
*/

using coord = long double;
const long double pi = acos(-1);
const long double EPS = 1e-8;
 
int sign(coord x) {return (x > EPS) - (x < -EPS);}
 
struct point {
	coord x, y, z;
	point(): x(0), y(0), z(0) {} 
	point(coord _x, coord _y, coord _z): x(_x), y(_y), z(_z) {}
 
	inline point operator+(point p){ return {x + p.x, y + p.y, z + p.z}; }
	inline point operator-(point p){ return {x - p.x, y - p.y, z - p.z}; }
	inline point operator*(coord o){ return {x * o, y * o, z * o}; }
	inline point operator/(coord o){ return {x / o, y / o, z / o}; }
 
	inline coord operator*(point p){ return x * p.x + y * p.y + z * p.z;}
	inline point operator^(point p){ return {y * p.z - z * p.y, z * p.x - x * p.z ,x * p.y - p.x * y };}
 
	inline coord norm(){ return sqrt(x * x + y * y + z * z);}
 	inline coord norm2(){ return x * x + y * y + z * z; }

	inline bool operator==(point p){ return sign(x - p.x) == 0 and sign(y - p.y) == 0 and sign(z - p.z) == 0;}
	inline void operator=(point p){x = p.x; y = p.y; z = p.z;}
};

// transform polar (degree) coordnates to cartesian in a sphere of radius r
point deg_to_cart(coord r, coord tht, coord phi){
	tht *= 2.0 * pi / 360.0;
	phi *= 2.0 * pi / 360.0;
	return point(cos(tht) * cos(phi), cos(tht) * sin(phi), sin(tht)) * r;
}

// shortest distance in a sphere of radius r
coord dist_sph(coord r, point a, point b){
	return r * acos((a * b) / (a.norm() * b.norm())); // arc/raio = rad
}

// return true if p is contained in the arc ab
bool contains(point p, point a, point b){
	return (sign((a ^ p) * (a ^ b)) > 0) and (sign((a ^ p) * (p ^ b)) > 0);
}

// get intersecon of arcs ab and cd in a sphere of radius r
point get_arc_intsec(coord r, point a, point b, point c, point d){
	point nrm1 = a ^ b;
	point nrm2 = c ^ d;
	point p = nrm1 ^ nrm2; // intersection of planes 

	if (sign(p.norm()) == 0)
		return {0, 0, 0};

	p = p * (r / p.norm());
	point pp = p * (-1.0);

	if (contains(p, a, b) and contains(p, c, d)) return p;
	if (contains(pp, a, b) and contains(pp, c, d)) return pp;
	return {0, 0, 0};
}