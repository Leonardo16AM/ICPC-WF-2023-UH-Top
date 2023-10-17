/*
	Given a matrix, this finds the minimum sum of positions 
	such that you take at least one from every row and column.
	Complexity: O(n^2*m*log(n*m))
*/
const ll oo=1e9;

ll at_least_one_per_row_and_column(vector<vector<ll>>& a)
{
    int n=a.size();
    int m=a[0].size();
    vector<ll> minr(n,oo),minc(m,oo);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            minr[i]=min(minr[i],a[i][j]);
            minc[j]=min(minc[j],a[i][j]);
        }
    min_cost_max_flow<ll,ll> mcmf(n+m+2);
    int s=0,t=n+m+1;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            mcmf.add_edge(i+1,j+1+n,1,min((ll)0,a[i][j]-minr[i]-minc[j]));

    ll ans=0;
    for(int i=0;i<n;i++)
    {
        mcmf.add_edge(s,i+1,1,0);
        ans+=minr[i];
    }
    for(int i=0;i<m;i++)
    {
        mcmf.add_edge(i+1+n,t,1,0);
        ans+=minc[i];
    }
    ans+=mcmf.max_flow(s,t).second;
    return ans;
}