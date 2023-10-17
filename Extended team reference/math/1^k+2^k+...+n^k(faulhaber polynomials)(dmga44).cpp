/**
    generate_bernoulli: genera los numeros de bernoulli O(k^2)
    fualhaber_polynomial: devuelve el k-esimo polinomio de faulhaber,
    el que al evaluarlo en n retorna 1^k+2^k+...+n^k
**/

ll dp[2][MAXK];
ll bernoulli_numbers[MAXK];
void generate_bernoulli(int k)
{
    bernoulli_numbers[0]=1;
    dp[0][1]=dp[0][2]=1;
    for(int i=1;i<=k;i++)
    {
        ll men=0;
        ll act=i&1;
        for(int j=0;j<i;j++)
        {
            dp[act][j+1]=dp[act^1][j]+dp[act^1][j+1];
            if(dp[act][j+1]>=mod)
                dp[act][j+1]-=mod;
            men+=dp[act][j+1]*bernoulli_numbers[j];
            if(men>=mod2)
                men-=mod2;
//            men=(men+c(i+1,j)*bernoulli_numbers[j])%mod;
        }
        dp[act][i+1]=dp[act^1][i]+dp[act^1][i+1];
        dp[act][i+1]%=mod;
        dp[act][i+2]=dp[act^1][i+1];

        men%=mod;
        men=(men*qp(i+1,mod-2))%mod;
        bernoulli_numbers[i]=(mod+1-men)%mod;
    }
}

vector<ll> fualhaber_polynomial(int k)
{
    ll inv=qp(k+1,mod-2);
    vector<ll> res(k+2);
    for(int i=0;i<=k;i++)
        res[k+1-i]=(inv*((c(k+1,i)*bernoulli_numbers[i])%mod))%mod;
    return res;
}
