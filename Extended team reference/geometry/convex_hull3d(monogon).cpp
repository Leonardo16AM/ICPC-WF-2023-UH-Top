///n^2
#include <bits/stdc++.h>

#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

typedef long double ftype;

struct pt3 {
    ftype x, y, z;
    pt3(ftype x = 0, ftype y = 0, ftype z = 0) : x(x), y(y), z(z) {}
    pt3 operator-(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    pt3 cross(const pt3 &o) const {
        return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ftype dot(const pt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
};

// A face is represented by the indices of its three points a, b, c.
// It also stores an outward-facing normal vector q
struct face {
    int a, b, c;
    pt3 q;
};

// modify this depending on the coordinate sizes in your use case
const ftype EPS = 1e-9;

vector<face> hull3(const vector<pt3> &p) {
    int n = sz(p);
    assert(n >= 3);
    vector<face> f;

    // Consider an edge (a->b) dead if it is not a CCW edge of some current face
    // If an edge is alive but not its reverse, this is an exposed edge.
    // We should add new faces on the exposed edges.
    vector<vector<bool>> dead(n, vector<bool>(n, true));
    auto add_face = [&](int a, int b, int c) {
        f.push_back({a, b, c, (p[b] - p[a]).cross(p[c] - p[a])});
        dead[a][b] = dead[b][c] = dead[c][a] = false;
    };

    // Initialize the convex hull of the first 3 points as a
    // triangular disk with two faces of opposite orientation
    add_face(0, 1, 2);
    add_face(0, 2, 1);
    rep(i, 3, n) {
        // f2 will be the list of faces invisible to the added point p[i]
        vector<face> f2;
        for(face &F : f) {
            if((p[i] - p[F.a]).dot(F.q) > EPS) {
                // this face is visible to the new point, so mark its edges as dead
                dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = true;
            }else {
                f2.push_back(F);
            }
        }
        // Add a new face for each exposed edge.
        // Only check edges of alive faces for being exposed.
        f.clear();
        for(face &F : f2) {
            int arr[3] = {F.a, F.b, F.c};
            rep(j, 0, 3) {
                int a = arr[j], b = arr[(j + 1) % 3];
                if(dead[b][a]) {
                    add_face(b, a, i);
                }
            }
        }
        f.insert(f.end(), all(f2));
    }
    return f;
}

///nlogn
#include <bits/stdc++.h>

#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

typedef long double ftype;

struct pt3 {
    ftype x, y, z;
    pt3(ftype x = 0, ftype y = 0, ftype z = 0) : x(x), y(y), z(z) {}
    pt3 operator-(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    pt3 cross(const pt3 &o) const {
        return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ftype dot(const pt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    ftype abs() const {
        return sqrt(dot(*this));
    }
};

struct edge;

// The implementation becomes more challenging because we need information of adjacent faces.
// A face will have 3 edges for its adjacent faces
// e1 corresponds to the edge (a,b), e2 to (b,c), and e3 to (c,a)
// A face will store a list of future points that can see it.
// A face will also store "dead" - the index of the point responsible for deleting it (or 1e9 if alive)
struct face {
    int a, b, c;
    pt3 q;
    edge *e1, *e2, *e3;
    vi points;
    int dead = 1e9;
    face(int a, int b, int c, pt3 q) : a(a), b(b), c(c), q(q) {
        e1 = e2 = e3 = NULL;
    }
};

// an edge will store the face it leads to and a pointer to the reverse edge
struct edge {
    edge *rev;
    face *f;
};

// This function will glue two faces together
// e1 is a reference to the F1 edge pointer, and e2 is a reference to the F2 edge pointer
void glue(face *F1, face *F2, edge* &e1, edge* &e2) {
    e1 = new edge;
    e2 = new edge;
    e1->rev = e2;
    e2->rev = e1;
    e1->f = F2;
    e2->f = F1;
};

// modify this to your liking
const ftype EPS = 1e-9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// shuffles the point-set p, making sure the first 4 points are not coplanar.
// if all points are coplanar, an assertion fails
void prepare(vector<pt3> &p) {
    int n = sz(p);
    shuffle(all(p), rng);
    vi ve;
    ve.push_back(0);
    rep(i, 1, n) {
        if(sz(ve) == 1) {
            if((p[ve[0]] - p[i]).abs() > EPS) ve.push_back(i);
        }else if(sz(ve) == 2) {
            if((p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).abs() > EPS) ve.push_back(i);
        }else if(abs((p[i] - p[ve[0]]).dot((p[ve[1]] - p[ve[0]]).cross(p[ve[2]] - p[ve[0]]))) > EPS) {
            ve.push_back(i);
            break;
        }
    }
    assert(sz(ve) == 4);
    vector<pt3> ve2;
    for(int i : ve) ve2.push_back(p[i]);
    reverse(all(ve));
    for(int i : ve) p.erase(p.begin() + i);
    p.insert(p.begin(), all(ve2));
}

vector<face*> hull3(vector<pt3> &p) {
    int n = sz(p);
    prepare(p);
    vector<face*> f, new_face(n, NULL);

    // for a point i, conflict[i] is the list of faces it can see.
    // It might contain faces that were deleted, and we should ignore them
    vector<vector<face*>> conflict(n);
    auto add_face = [&](int a, int b, int c) {
        face *F = new face(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
        f.push_back(F);
        return F;
    };

    // initialize a triangular disk of the first 3 points.
    // The initial tetrahedron is handled automatically when we insert the 4th point
    face *F1 = add_face(0, 1, 2);
    face *F2 = add_face(0, 2, 1);
    glue(F1, F2, F1->e1, F2->e3);
    glue(F1, F2, F1->e2, F2->e2);
    glue(F1, F2, F1->e3, F2->e1);
    rep(i, 3, n) {
        for(face *F : {F1, F2}) {
            ftype Q = (p[i] - p[F->a]).dot(F->q);
            if(Q > EPS) conflict[i].push_back(F);
            // making this second check is an ugly consequence of starting with a degenerate triangular disk.
            // We want to make sure each future point is considered visible to some initial face.
            if(Q >= -EPS) F->points.push_back(i);
        }
    }

    rep(i, 3, n) {
        // mark all visible faces as dead
        for(face *F : conflict[i]) F->dead = min(F->dead, i);

        // If a dead face and alive face are adjacent, we have an exposed edge
        // Vertex v will be a vertex on some exposed edge
        int v = -1;
        for(face *F : conflict[i]) {
            if(F->dead != i) continue;
            int parr[3] = {F->a, F->b, F->c};
            edge* earr[3] = {F->e1, F->e2, F->e3};
            rep(j, 0, 3) {
                int j2 = (j + 1);
                if(j2 >= 3) j2 -= 3;

                if(earr[j]->f->dead > i) {
                    // F is dead and earr[j]->f is alive.
                    // We should add a new face Fn, attach it to earr[j]->f,
                    // combine the point lists of the two faces into Fn,
                    // and store Fn in new_face[parr[j]] so we can glue all the new faces together in a cone.
                    face *Fn = new_face[parr[j]] = add_face(parr[j], parr[j2], i);
                    set_union(all(F->points), all(earr[j]->f->points), back_inserter(Fn->points));
                    Fn->points.erase(stable_partition(all(Fn->points), [&](int k) {
                        return k > i && (p[k] - p[Fn->a]).dot(Fn->q) > EPS;
                    }), Fn->points.end());
                    for(int k : Fn->points) {
                        conflict[k].push_back(Fn);
                    }
                    earr[j]->rev->f = Fn;
                    Fn->e1 = earr[j];
                    v = parr[j];
                }
            }
        }
        // There are no exposed edges
        if(v == -1) continue;

        // Glue all the new cone faces together
        while(new_face[v]->e2 == NULL) {
            int u = new_face[v]->b;
            glue(new_face[v], new_face[u], new_face[v]->e2, new_face[u]->e3);
            v = u;
        }
    }

    // Remove dead faces
    f.erase(remove_if(all(f), [&](face *F) {
        return F->dead < n;
    }), f.end());
    return f;
}
