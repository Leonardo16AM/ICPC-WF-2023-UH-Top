/**
Original code from https://codeforces.com/blog/entry/85638

Important facts from Delaunay triangulation:
    -For each Delaunay triangle, its circumcircle does not strictly contain any points in S. (In fact, you can also consider this the defining property of Delaunay triangulation)
    -The number of Delaunay edges is at most 3n−6, so there is hope for an efficient construction.
    -Each point p∈S is adjacent to its nearest neighbor with a Delaunay edge.
    -The Delaunay triangulation maximizes the minimum angle in the triangles among all possible triangulations.
    -The Euclidean minimum spanning tree is a subset of Delaunay edges.

Remember to rotate the points to avoid two points from having the same coordinate x.
**/

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

using ftype = long double;
const ftype EPS = 1e-12, INF = 1e100;

struct pt
{
    ftype x, y;
    pt(ftype x = 0, ftype y = 0) : x(x), y(y) {}

    pt operator+(const pt &o) const
    {
        return pt(x + o.x, y + o.y);
    }
    pt operator-(const pt &o) const
    {
        return pt(x - o.x, y - o.y);
    }
    pt operator*(const ftype &f) const
    {
        return pt(x * f, y * f);
    }

    pt rot() const
    {
        return pt(-y, x);
    }

    ftype dot(const pt &o) const
    {
        return x * o.x + y * o.y;
    }
    ftype cross(const pt &o) const
    {
        return x * o.y - y * o.x;
    }

    ftype len() const
    {
        return hypotl(x, y);
    }

    bool operator<(const pt &o) const
    {
        return make_pair(x, y) < make_pair(o.x, o.y);
    }
};

bool collinear(pt a, pt b)
{
    return abs(a.cross(b)) < EPS;
}

// intersection point of lines ab and cd. Precondition is that they aren't collinear
pt lineline(pt a, pt b, pt c, pt d)
{
    return a + (b - a) * ((c - a).cross(d - c) / (b - a).cross(d - c));
}

// circumcircle of points a, b, c. Precondition is that abc is a non-degenerate triangle.
pt circumcenter(pt a, pt b, pt c)
{
    b = (a + b) * 0.5;
    c = (a + c) * 0.5;
    return lineline(b, b + (b - a).rot(), c, c + (c - a).rot());
}

// x coordinate of sweep-line
ftype sweepx;

// an arc on the beach line is given implicitly by the focus p,
// the focus q of the following arc, and the position of the sweep-line.
struct arc
{
    mutable pt p, q;
    mutable int id = 0, i;
    arc(pt p, pt q, int i) : p(p), q(q), i(i) {}

    ftype gety(ftype x) const
    {
        if (q.y == INF)
            return INF;
        x += EPS;
        pt med = (p + q) * 0.5;
        pt dir = (p - med).rot();
        ftype D = (x - p.x) * (x - q.x);
        return med.y + ((med.x - x) * dir.x + sqrtl(D) * dir.len()) / dir.y;
    }
    bool operator<(const ftype &y) const
    {
        return gety(sweepx) < y;
    }
    bool operator<(const arc &o) const
    {
        return gety(sweepx) < o.gety(sweepx);
    }
};

// the beach line will be stored as a multiset of arc objects
using beach = multiset<arc, less<>>;

// an event is given by
//     x: the time of the event
//     id: If >= 0, it's a point event for index id.
//         If < 0, it's an ID for a vertex event
//     it: if a vertex event, the iterator for the arc to be deleted
struct event
{
    ftype x;
    int id;
    beach::iterator it;
    event(ftype x, int id, beach::iterator it) : x(x), id(id), it(it) {}
    bool operator<(const event &e) const
    {
        return x > e.x;
    }
};

struct fortune
{
    beach line;
    vector<pair<pt, int>> v;
    priority_queue<event> Q;
    vector<pii> edges; // delaunay edges
    vector<bool> valid;
    int n, ti;
    fortune(vector<pt> p)
    {
        n = sz(p);
        v.resize(n);
        rep(i, 0, n) v[i] = {p[i], i};
        sort(all(v));
    }
    // update the remove event for the arc at position it
    void upd(beach::iterator it)
    {
        if (it->i == -1)
            return;
        valid[-it->id] = false;
        auto a = prev(it);
        if (collinear(it->q - it->p, a->p - it->p))
            return;
        it->id = --ti;
        valid.push_back(true);
        pt c = circumcenter(it->p, it->q, a->p);
        ftype x = c.x + (c - it->p).len();

        if (x > sweepx - EPS && a->gety(x) + EPS > it->gety(x))
        {
            Q.push(event(x, it->id, it));
        }
    }
    // add Delaunay edge
    void add_edge(int i, int j)
    {
        if (i == -1 || j == -1)
            return;
        edges.push_back({v[i].second, v[j].second});
    }
    // handle a point event
    void add(int i)
    {
        pt p = v[i].first;

        auto c = line.lower_bound(p.y);

        auto b = line.insert(c, arc(p, c->p, i));
        auto a = line.insert(b, arc(c->p, p, c->i));
        add_edge(i, c->i);
        upd(a);
        upd(b);
        upd(c);
    }
    // handle a vertex event
    void remove(beach::iterator it)
    {
        auto a = prev(it);
        auto b = next(it);
        line.erase(it);
        a->q = b->p;
        add_edge(a->i, b->i);
        upd(a);
        upd(b);
    }
    // X is a value exceeding all coordinates
    void solve(ftype X = 1e9)
    {
        // insert two points that will always be in the beach line,
        // to avoid handling edge cases of an arc being first or last
        X *= 3;
        line.insert(arc(pt(-X, -X), pt(-X, X), -1));
        line.insert(arc(pt(-X, X), pt(INF, INF), -1));
        // create all point events
        rep(i, 0, n)
        {
            Q.push(event(v[i].first.x, i, line.end()));
        }
        ti = 0;
        valid.assign(1, false);
        while (!Q.empty())
        {
            event e = Q.top();
            Q.pop();
            sweepx = e.x;
            if (e.id >= 0)
            {
                add(e.id);
            }
            else if (valid[-e.id])
            {
                remove(e.it);
            }
        }
    }
};