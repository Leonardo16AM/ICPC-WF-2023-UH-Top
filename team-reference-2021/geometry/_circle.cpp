// circle-circle intersection
vector<point> intersect(circle C, circle D){
	double d = abs(C.p - D.p);
	if (sign(d - C.r - D.r) > 0) return {};      // too far
	if (sign(d - abs(C.r - D.r)) < 0) return {}; // too close
	double a = (C.r*C.r - D.r*D.r + d*d) / (2*d);
	double h = sqrt(C.r*C.r - a*a);
	point v = (D.p - C.p) / d;
	if (sign(h) == 0) return {C.p + v*a};         // touch
	return {C.p + v*a + point(0,1)*v*h,           // intersect
			C.p + v*a - point(0,1)*v*h};
}
// circle-line intersection
vector<point> intersect(line L, circle C){
	point u = L.p - L.q, v = L.p - C.p;
	double a = dot(u, u), b = dot(u, v), c = dot(v, v) - C.r*C.r;
	double det = b*b - a*c;
	if (sign(det) < 0) return {};             // no solution
	if (sign(det) == 0) return {L.p - b/a*u}; // touch
	return {L.p + (-b + sqrt(det))/a*u,
			L.p + (-b - sqrt(det))/a*u};
}
// circle tangents through point
vector<point> tangent(point p, circle C){
	double sin2 = C.r*C.r/norm(p - C.p);
	if (sign(1 - sin2) < 0) return {};
	if (sign(1 - sin2) == 0) return {p};
	point z(sqrt(1 - sin2), sqrt(sin2));
	return {p + (C.p - p)*conj(z), p + (C.p - p)*z};
}
bool incircle(point a, point b, point c, point p){
	a -= p; b -= p; c -= p;
	return norm(a) * cross(b, c)
			+ norm(b) * cross(c, a)
			+ norm(c) * cross(a, b) >= 0;
			// < : inside, = cocircular, > outside
}
point three_point_circle(point a, point b, point c){
	point x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
	return (y - x) / (conj(x) * y - x * conj(y)) + a;
}
// Get the center of the circle with minimum ratio that enclose all points
circle min_enclosing_circle(vector<point> P){
	int n = P.size();
	shuffle(P.begin(), P.end(), random_device{});
	double r = 0.0; point p = P[0];
	for (int i = 1; i < n; ++i)
		if (dblcmp(abs(P[i] - p), r) > 0){
			r = abs(P[0] - P[i]) * 0.5;
			p = (P[0] + P[i]) * 0.5;
			for (int j = 1; j < i; ++j)
				if (dblcmp(abs(P[j] - p), r) > 0){
					r = abs(P[i] - P[j]) * 0.5;
					p = (P[i] + P[j]) * 0.5;
					for (int k = 0; k < j; ++k)
						if (dblcmp(abs(P[k] - p), r) > 0){
							p=three_point_circle(P[i],P[j],P[k]);
							r = abs(p - P[i]);
						}
				}
		}
	return {r, p};
}
