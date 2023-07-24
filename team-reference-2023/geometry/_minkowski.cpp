// The sum of Minkowski of two sets A and B is the set C = 
// { a + b : a e A,b e B }. // each element in a set is a vector
// It can be proven that if A and B are convex polygons then C 
// will also be a convex polygon.
// Minkowski sum of two convex polygons. O(n + m)
// Note: Polygons MUST be counterclockwise
polygon minkowski(const polygon &ps, const polygon &qs){
	vector<point> rs;
	int i = distance(ps.begin(), min_element(ps.begin(), ps.end()));
	int j = distance(qs.begin(), min_element(qs.begin(), qs.end()));
	do{
		rs.emplace_back(ps[i] + qs[j]);
		int in = i + 1, jn = j + 1;
		if (in == ps.size()) in = 0;
		if (jn == qs.size()) jn = 0;
		int s = sign(cross(ps[i] - ps[in], qs[j] - qs[jn]));
		if (s >= 0) i = in;
		if (s <= 0) j = jn;
	}
	while (rs[0] != ps[i] + qs[j]);
	return rs;
}
