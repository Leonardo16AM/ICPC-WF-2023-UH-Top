/**
    Sorts the points of v putting first the points from 1st quadrant and so on

    Tested:
    https://codeforces.com/contest/1284/problem/E
**/

#include <bits/stdc++.h>
#define db(x) cout << (x) << '\n';
#define all(v) (v).begin(),(v).end()

typedef complex<double> point;
typedef vector<point> polygon;

double cross(point a, point b) { return imag(conj(a) * b); }

int quad(point x)
{
    if(x.imag()>=0 && x.real()>0) return 0;
    if(x.imag()>0 && x.real()<=0) return 1;
    if(x.imag()<=0 && x.real()<0) return 2;
    return 3;
}

vector<point> angular_sort(vector<point> &v)
{
    sort(all(v),[&](point &a,point &b){
        if(quad(a)!=quad(b)) return quad(a)<quad(b);
        return cross(a,b)>0;
    });

    return v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    polygon p;
    for(int i=0;i<n;i++)
    {
        ll x,y;
        cin >> x >> y;
        p.push_back(point(x,y));
    }

    ll res=0;
    for(int i=0;i<n;i++)
    {
        vector<point> angs;
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            point v=p[j]-p[i];
            angs.push_back(v);
        }

        angular_sort(angs);

        for(int j=0;j<n-1;j++)
            angs.push_back(angs[j]);

        int act=0,pos=1;
        while(cross(angs[0],angs[pos])>0)
            pos++;
        int r=pos;
        for(int l=1;l<pos;l++)
        {
            while(cross(angs[l],angs[r])>0)
                r++;
            act+=(r-pos);
        }

        res+=act;
        for(int j=1;j<n-1;j++)
        {
            int pa=pos;
            if(j==pos)
                pos++;
            while(cross(angs[j],angs[pos])>0)
                pos++;
            int dif=pos-pa;
            int p1=pa-j;
            int p2=n-1-p1-dif;
            act+=(dif*(p2-p1));
            res+=act;
        }
    }

    db(res)

    return 0;
}
