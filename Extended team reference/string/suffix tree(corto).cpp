/**
    Todavia sin probar
**/
struct suffix_tree{
    string a;
    vector<int> l,r,p,s;
    vector<vector<int>> t;
    int tv,tp,ts,la;
    int n;

    suffix_tree(string _s)
    {
        a=_s;
        n=2*_s.size();
        l.resize(n);
        r.resize(n);
        p.resize(n);
        s.resize(n);
        t=vector<vector<int>>(n,vector<int>(26));
        build();
    }

    void ukkadd (int c) {
        suff:;
        if (r[tv]<tp) {
            if (t[tv][c]==-1) { t[tv][c]=ts;  l[ts]=la;
                p[ts++]=tv;  tv=s[tv];  tp=r[tv]+1;  goto suff; }
            tv=t[tv][c]; tp=l[tv];
        }
        if (tp==-1 || c==a[tp]-'a') tp++; else {
            l[ts+1]=la;  p[ts+1]=ts;
            l[ts]=l[tv];  r[ts]=tp-1;  p[ts]=p[tv];  t[ts][c]=ts+1;  t[ts][a[tp]-'a']=tv;
            l[tv]=tp;  p[tv]=ts;  t[p[ts]][a[l[ts]]-'a']=ts;  ts+=2;
            tv=s[p[ts-2]];  tp=l[ts-2];
            while (tp<=r[ts-2]) {  tv=t[tv][a[tp]-'a'];  tp+=r[tv]-l[tv]+1;}
            if (tp==r[ts-2]+1)  s[ts-2]=tv;  else s[ts-2]=ts;
            tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
        }
    }

    void build() {
        ts=2;
        tv=0;
        tp=0;
        fill(r.data(),r.data()+n,(int)a.size()-1);
        s[0]=1;
        l[0]=-1;
        r[0]=-1;
        l[1]=-1;
        r[1]=-1;
        for(int i=0;i<n;i++)
            for(int j=0;j<26;j++)
                t[i][j]=-1;
        fill(t[1].data(),t[1].data()+26,0);
        for (la=0; la<(int)a.size(); ++la)
            ukkadd (a[la]-'a');
    }

    void show()
    {
        for(int i=0;i<n;i++)
        {
            cout << '\n';
            cout << i << '\n';
            cout << l[i] << ' ' << r[i] << '\n';
            cout << p[i] << '\n';
            for(int j=0;j<26;j++)
                if(t[i][j]!=-1)
                    cout << j << ' ' << t[i][j] << '\n';
        }
    }
};
