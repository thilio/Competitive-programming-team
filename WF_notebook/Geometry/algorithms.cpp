/*
   Title: 2D Geometry Algorithms Libary
   Description: 2D Geometry Algorithms
*/

// Sort by augment angle related to o
struct comparator{
	point o;
	comparator(point _o): o(_o){}
	bool operator()(point a, point b){
		// a = a - o; // If o is not in que lower left corner
		// b = b - o;
		// if (a.x < 0 and b.x >= 0)
		// 	return false;
		// if (a.x >= 0 and b.x < 0)
		// 	return true;
		// if (a.x >= 0 and sign(a.y) != sign(b.y))
		// 	return a.y < b.y;

		if (sign((a - o) ^ (b - o)) != 0)
			return sign((a - o) ^ (b - o)) > 0;
		return sign((a - o).norm2() - (b - o).norm2()) < 0;
	}
};

// build convex hull in nlog(n), n > 1, hull is in reverse clockwise order
vector<point> convex_hull(vector<point> v, int border_in){ // should border be in convex?
	swap(v[0], *min_element(all(v))); // lex_sort
	sort(v.begin() + 1, v.end(), comparator(v[0]));
	int sz = 2, s, nv = v.size();
	if (border_in){
		for (s = nv - 1; s > 1 and sign((v[s] - v[0]) ^ (v[s - 1] - v[0])) == 0; s--);
		reverse(v.begin() + s, v.end());	
	}
	vector<point> hull = {v[0], v[1]};
	for (int i = 2; i < nv; i++)
		if (sz < 2)
			hull.push_back(v[i]), sz++;
		else if (sign((hull[sz - 1] - hull[sz - 2]) ^ (v[i] - hull[sz - 1])) >= 1 - border_in)
			hull.push_back(v[i]), sz++;
		else
			hull.pop_back(), i--, sz--;
	return hull;	
}

// find diameter of a polygon in O(n) n > 2, no border
pair<point, point> diameter_polygon(vector<point> v){
	int l, r, p = 2, nv = v.size();
	coord mxdst = 0;
	pair<point, point> ans = {v[0], v[1]};

	for (int i = 0; i < nv; i++){
		l = i, r = (i + 1) % nv;
		point lr = v[r] - v[l]; 
		while (sign(abs((v[(p + 1) % nv] - v[l]) ^ lr) - abs((v[p] - v[l]) ^ lr)) >= 0) 
			p = (p + 1) % nv;
		if (sign((v[l] - v[p]).norm2() - mxdst) > 0)
			mxdst = (v[l] - v[p]).norm2(), ans = {v[l], v[p]};
		if (sign((v[r] - v[p]).norm2() - mxdst) > 0)
			mxdst = (v[r] - v[p]).norm2(), ans = {v[r], v[p]};
	}
	return ans;
}

// check if a is conteined in polygon in O(log(n)) n > 1
bool pol_contain(vector<point> &pol, point a){ // pol must be in clockwise order
	int r = pol.size() - 1, l = 1, meio;
	while (r - l > 1){
		meio = (r + l) / 2;
		if (segment(pol[0], pol[meio]).ccw(a) >= 0) r = meio;
		else l = meio;
	}
	if (r == l) return segment(pol[0], pol[r]).contains(a);
	else{
		coord a1 =	abs((pol[r] - pol[0]) ^ (pol[l] - pol[0]));
		coord a2 =	abs((pol[r] - a) ^ (pol[l] - a)) +
					abs((pol[l] - a) ^ (pol[0] - a)) +
					abs((pol[0] - a) ^ (pol[r] - a));
		return sign(a1 - a2) == 0;			
	}
}

// Return the minimun squared distance for a set of points in nlog(n)
vector<point> auxv; // auxiliary array
coord closest_pair(vector<point> &v, int l, int r, int srt = 0){ // (array, 0, array.size())
	if (l + 1 >= r) return 1e100; // [l, r)
	if (!srt) sort(v.begin(), v.end()), auxv.resize(r); // lex_compare	
	int meio = (l + r)/2;
	coord x = v[meio].x;

	coord h = min(closest_pair(v, l, meio, 1), closest_pair(v, meio, r, 1));
	
	auto cmp = [](point &a, point &b){ return a.y < b.y; };
	merge(v.begin() + l, v.begin() + meio, v.begin() + meio, v.begin() + r, auxv.begin(), cmp);
	copy(auxv.begin(), auxv.begin() + r - l, v.begin() + l);

	int asz = 0;
	for (int i = l; i < r; i++)
		if (sign(sq(v[i].x - x) - h) <= 0){
			for (int j = asz - 1; j >= 0 and sign(sq(v[i].y - auxv[j].y) - h) <= 0; j--)
				h = min(h, (v[i] - auxv[j]).norm2());
			auxv[asz++] = v[i];
		}
	return h;
}

//Get area of a general polygon, O(n)
long double get_area(vector<point> &P){
	if (P.size() < 3) 
		return 0;

	coord area = 0;
	for (int i = 0; i + 1 < P.size(); i++)
		area += P[i] ^ P[i + 1];

	return abs(area + (P[P.size() - 1]^P[0])) / 2.0;
}

coord max_manhattan(vector<point> &p){
	coord mas, mad, mis, mid;
	mis = mas = p[0].x + p[0].y;
	mid = mad = p[0].x - p[0].y;

	for (int i = 1; i < p.size(); i++){
		mis = min(mis, p[i].x + p[i].y);
		mas = max(mas, p[i].x + p[i].y);
		mid = min(mid, p[i].x - p[i].y);
		mad = max(mad, p[i].x - p[i].y);
	}

	return max(mas - mis, mad - mid);
} // May be generalized to 3d, just use x+y+z, x+y-z, x-y+z, and x-y-z. Expand the formula


// Retuns the polygon of the intersection of all halfplanes in nlog(n)
// BE CAREFUL with the INF value for unbounded cases
vector<point> halfp_intersect(vector<halfplane>& H) { 
	point box[4] = {point(INF, INF), point(-INF, INF), point(-INF, -INF), point(INF, -INF)};
	// Build bounding box to deal with unbound cases
	for (int i = 0; i < 4; i++)
		H.push_back(halfplane (box[i], box[(i+1) % 4]));

	// Sort and remove duplicates
	sort(H.begin(), H.end());
	H.erase(unique(H.begin(), H.end()), H.end());

	deque<halfplane> dq;
	int len = 0;
	for (int i = 0; i < int(H.size()); i++){
		while (len > 1 and H[i].out(inter(dq[len-1], dq[len-2])))
			dq.pop_back(), len--;

		while (len > 1 and H[i].out(inter(dq[0], dq[1])))
			dq.pop_front(), len--;

		dq.push_back(H[i]);
		++len;
	}

	while (len > 2 and dq[0].out(inter(dq[len-1], dq[len-2])))
		dq.pop_back(), len--;

	while (len > 2 and dq[len-1].out(inter(dq[0], dq[1])))
		dq.pop_front(), len--;

	if (len < 3) 
		return vector<point>(); // empty intersection

	// Reconstruct the convex polygon from the remaining half-planes.
	vector<point> ret(len);
	for(int i = 0; i+1 < len; i++)
		ret[i] = inter(dq[i], dq[i+1]);
	ret.back() = inter(dq[len-1], dq[0]);

	return ret;
}

circle min_circle_cover (vector<point> v) { // Minimum circle that covers all points. O(n)
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	int i,j,k;
	int n = v.size();
	shuffle(v.begin(), v.end(), rng);
	circle c(point(), 0);

	for (i = 0; i < n; i++) if (!c.contains(v[i]))
		for (c = circle(v[i],0), j = 0; j < i; j++) if (!c.contains(v[j]))
			for (c = circle((v[i] + v[j])/2, (v[i]-v[j]).norm()/2), k = 0; k < j; k++) if (!c.contains(v[k]))
					c = circuns_triang(v[i],v[j],v[k]);
	return c;
}

void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}
vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < P.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}