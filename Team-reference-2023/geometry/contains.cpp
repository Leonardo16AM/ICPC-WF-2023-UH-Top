// Determine the position of a point relative to a polygon.
// (1) General Polygon
// (2) Convex Polygon
enum { OUT, ON, IN };
int contains(const polygon &P, const point &p){
    bool in = false;
    for (int i = 0, n = P.size(); i < n; ++i){
        point a = P[i] - p, b = P[NEXT(i)] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b))
            if (cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0)
            return ON;
    }
    return in ? IN : OUT;
}
struct convex_container{
    polygon pol;
    // Polygon MUST be in counter clockwise order
    convex_container(polygon p) : pol(p){
        int pos = 0;
        for (int i = 1; i < p.size(); ++i)
            if (p[i].imag() < p[pos].imag() ||
                (p[i].imag() == p[pos].imag() && p[i].real() < p[pos].real()))
                    pos = i;
        rotate(pol.begin(), pol.begin() + pos, pol.end());
    }
    bool contains(point p){
        point c = pol[0];
        if (p.imag() < c.imag() || cross(pol.back() - c, p - c) > 0)
            return false;
        int lo = 1, hi = pol.size() - 1;
        while (lo + 1 < hi){
            int m = (lo + hi) / 2;
            if (cross(pol[m] - c, p - c) >= 0) lo = m;
            else hi = m;
        }
        return abs(cross(c, pol[lo], pol[lo + 1]))
                - abs(cross(p, c, pol[lo]))
                    - abs(cross(p, c, pol[lo + 1]))
                        - abs(cross(p, pol[lo], pol[lo + 1])) == 0;
    }
};