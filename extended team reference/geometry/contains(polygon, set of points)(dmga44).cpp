/**
    tested:https:https://codeforces.com/gym/101128/submission/108558767

    Returns for each point in ps wether it is contained in p.
    Complexity O(m*log(n)+n)
**/
typedef complex<ll> point;
typedef vector<point> polygon;

#define NEXT(i) (((i)+1)%n)
ll dot(point a,point b) {return real(conj(a)*b);}
ll cross(point a,point b) {return imag(conj(a)*b);}
ll area2(point a,point b,point c) {return cross(b-a,c-a);}

namespace std
{
    bool operator<(point a,point b)
    {
        if(a.real()!=b.real())
            return a.real()<b.real();
        return a.imag()<b.imag();
    }
}

polygon convex_hull(polygon& p)
{
    int n=p.size(),k=0;
    vector<point> h(2*n);
    sort(all(p));
    for(int i=0;i<n;h[k++]=p[i++])
        while(k>=2 && area2(h[k-2],h[k-1],p[i])<=0) k--;
    for(int i=n-2,t=k+1;i>=0;h[k++]=p[i--])
        while(k>=t && area2(h[k-2],h[k-1],p[i])<=0) k--;
    return polygon(h.begin(),h.begin()+k-(k>1));
}

enum{OUT,ON,IN};
int contains(const polygon& P,point p)
{
    bool in=0;
    for (int i = 0, n = P.size(); i < n; ++i)
	{
		point a = P[i] - p, b = P[NEXT(i)] - p;
		if (imag(a) > imag(b)) swap(a, b);
		if (imag(a) <= 0 && 0 < imag(b))
			if (cross(a, b) < 0) in = !in;
		if (cross(a, b) == 0 && dot(a, b) <= 0)
			return ON;
	}
	return in ? IN : OUT;
}

point read()
{
    int x,y;
    cin >> x >> y;
    return point(x,y);
}

vector<bool> contains(vector<point> p,vector<point> ps)
{
    int n=p.size();
    int my=0;
    for(int i=0;i<n;i++)
        if(p[my].imag()>p[i].imag())
            my=i;
    polygon pp;
    for(int i=my;i<my+n;i++)
        pp.push_back(p[i%n]);

    point origin=pp[0];
    for(int i=n-1;i>=0;i--)
        pp[i]-=pp[0];
    p=pp;

    int m=ps.size();
    vector<bool> res;
    for(int i=0;i<m;i++)
    {
        point x=ps[i];
        x-=origin;

        int pos=0;
        for(int po=(1<<19);po;po>>=1)
            if(pos+po<n && cross(p[pos+po],x)>=0)
                pos+=po;
        if(pos==0)
        {
            res.push_back(0);
            continue;
        }
        if(pos==n-1)
            pos--;
        res.push_back((bool)(contains(polygon{p[0],p[pos],p[pos+1]},x)));
    }
    return res;
}
