#include <bits/stdc++.h>
#define db(x) cout << (x) << '\n';
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef pair<double,ll> pdi;
typedef pair<string,ll> psi;
typedef pair<ll,string> pls;
typedef pair<ll,pii> pip;
typedef pair<pii,pii> ppp;

typedef complex<double> point;
typedef vector<point> polygon;

#define NEXT(i) (((i) + 1) % n)

struct circle { point p; double r; };
struct line { point p, q; };
using segment = line;

const double eps = 1e-9;

// fix comparations on doubles with this two functions
int sign(double x) { return x < -eps ? -1 : x > eps; }

int dblcmp(double x, double y) { return sign(x - y); }

double dot(point a, point b) { return real(conj(a) * b); }

double cross(point a, point b) { return imag(conj(a) * b); }

double area2(point a, point b, point c) { return cross(b - a, c - a); }

int ccw(point a, point b, point c)
{
    b -= a; c -= a;
    if (cross(b, c) > 0) return +1; // counter clockwise
    if (cross(b, c) < 0) return -1; // clockwise
    if (dot(b, c) < 0) return +2; // c--a--b on line
    if (dot(b, b) < dot(c, c)) return -2; // a--b--c on line
    return 0;
}

namespace std
{
    bool operator<(point a, point b)
    {
        if(a.imag()==0 && b.imag()==0)
            return a.real()>b.real();
        if(a.real()==0 && b.real()==0)
            return a.imag()<b.imag();
        if(a==point(0,0))
            return 1;
        if(a.real()==0)
            return 0;
        if(b.real()==0)
            return 1;
        if(atan(a.imag()/a.real())==atan(b.imag()/b.real()))
            return a.imag()<b.imag();
        return atan(a.imag()/a.real())<atan(b.imag()/b.real());
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,x,y;
    cin >> n;
    set<point> ch;
    int res=0;
    bool ox=0,oy=0;
    for(int i=0;i<n;i++)
    {
        cin >> x >> y;
        point a=point(x,y);
        ch.insert(a);

        auto it=ch.find(a);
        if((*it)!=a)
        {
            auto ita1=it;
            if(ita1!=ch.begin())
                ita1--;
            if((*ita1)==a)
                it=ita1;

            auto ita2=it;
            ita2++;
            if(ita2!=ch.end() && (*ita2)==a)
                it=ita2;
        }

        vector<point> sacar;
        auto ita=it;
        auto itp=it;
        itp++;

        ///quitar al tipo
        if(ita!=ch.begin())
        {
            ita--;
            if((*ita).real()>x && (*ita).imag()>y)
            {
                res++;
                db(res)
                ch.erase(a);
                continue;
            }
            ita++;
        }
        if(itp!=ch.end())
        {
            if((*itp).real()>x && (*itp).imag()>y)
            {
                res++;
                db(res)
                ch.erase(a);
                continue;
            }
        }
        if(ita!=ch.begin() && itp!=ch.end())
        {
            ita--;
            if((*ita).real()>x && (*ita).imag()>y)
            {
                res++;
                db(res)
                ch.erase(a);
                continue;
            }
            if(ccw((*itp),a,(*ita))==1)
            {
                res++;
                db(res)
                ch.erase(a);
                continue;
            }
            ita++;
        }

        ///anteriores
        if(ita!=ch.begin())
        {
            ita--;
            while((*ita).real()<x && (*ita).imag()<y)
            {
                sacar.push_back((*ita));
                if(ita==ch.begin())
                    break;
                ita--;
            }

            if(ita!=ch.begin())
            {
                auto ita2=ita;
                ita2--;
                while(ccw(a,(*ita),(*ita2))==1)
                {
                    sacar.push_back((*ita));
                    if(ita2==ch.begin())
                        break;
                    ita--;
                    ita2--;
                }
            }
        }

        ///posteriores
        if(itp!=ch.end())
        {

            while(itp!=ch.end() && (*itp).real()<x && (*itp).imag()<y)
            {
                sacar.push_back((*itp));
                itp++;
            }

            if(itp!=ch.end())
            {
                auto itp2=itp;
                itp2++;
                while(itp2!=ch.end() && ccw((*itp2),(*itp),a)==1)
                {
                    sacar.push_back((*itp));
                    itp++;
                    itp2++;
                }
            }
        }

        for(auto y : sacar)
            ch.erase(y);

        res+=sacar.size();
        db(res)
    }

    return 0;
}
