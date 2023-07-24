vector<ll> lagrange_interpolation(vector<ll> &xs,vector<ll> &ys)
{
    int n=xs.size();
    vector<ll> res(n);
    vector<vector<ll>> prec(n);
    for(int i=0;i<n;i++)
    {
        prec[i].resize(n);
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            prec[i][j]=qp(xs[i]-xs[j]+mod,mod-2);
        }
    }
    for(int i=0;i<n;i++)
    {
        vector<ll> add(n);
        add[0]=ys[i];
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            for(int k=n-2;k>=0;k--)
            {
                add[k+1]=(add[k+1]+add[k])%mod;
                add[k]=(add[k]*(mod-xs[j]))%mod;
            }
            for(int k=0;k<n;k++)
                add[k]=(add[k]*prec[i][j])%mod;
        }
        for(int j=0;j<n;j++)
            res[j]=(res[j]+add[j])%mod;
    }
    return res;
}

vector<ld> lagrange_interpolation(vector<ld> &xs,vector<ld> &ys)
{
    int n=xs.size();
    vector<ld> res(n);
    for(int i=0;i<n;i++)
    {
        vector<ld> add(n);
        add[0]=ys[i];
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            for(int k=n-2;k>=0;k--)
            {
                add[k+1]=add[k+1]+add[k];
                add[k]=add[k]*(mod-xs[j]);
            }
            for(int k=0;k<n;k++)
                add[k]/=(xs[i]-xs[j]);
        }
        for(int j=0;j<n;j++)
            res[j]=(res[j]+add[j])%mod;
    }
    return res;
}
