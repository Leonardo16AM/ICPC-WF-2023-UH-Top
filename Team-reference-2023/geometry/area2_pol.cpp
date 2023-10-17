//Double of the signed area of a polygon
double area2(const polygon &P){
	double A = 0;
	for (int i = 0, n = P.size(); i < n; ++i)
		A += cross(P[i], P[NEXT(i)]);
	return A;
}
