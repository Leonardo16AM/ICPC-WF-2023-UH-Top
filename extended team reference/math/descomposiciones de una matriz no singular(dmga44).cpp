/**
    Sea A una matriz tal que |A|!=0 la descomposicin PLU
    obtiene tres matrices P,L y U tal que A=PLU y P es una matriz permutacion
    L es una matriz triangular inferior y U es una matriz triangular superior.
**/
///dmga44
#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<vector<ld>> matrix;
typedef pair<matrix,matrix> pmm;
typedef pair<pmm,matrix> pmmm;
#define prec(n) cout.precision(n); cout<<fixed
const ll mod=(ll)(1e9+7);
const ld eps=(1e-6);
const ll oo=(ll)(1e18+5);
#define pi acos(-1)
#define MAXN (ll)(2e5+5)

///solo lo hare para matrices cuadradas
matrix operator*(matrix a,matrix b)
{
    int n=a.size();
    matrix res(n,vector<ld>(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
                res[i][j]+=(a[i][k]*b[k][j]);
    return res;
}

///con picardia ;)
bool operator==(matrix a,matrix b)
{
    int n=a.size();
    bool eq=1;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            ///notar que no hay restas y no se comprueba con "=="
            eq&=(a[i][j]+eps>=b[i][j] && a[i][j]<=b[i][j]+eps);
    return eq;
}

void print(matrix a)
{
    int n=a.size();
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cout << a[i][j] << " \n"[j==n-1];
    cout << '\n';
}

pmm LU_dec(matrix A)
{
    ///copia de la matriz original
    ///matrix aa=A;
    ///A es cuadrada
    int n=A.size();
    matrix inv_L(n,vector<ld>(n));
    for(int i=0;i<n;i++)    ///la seteamos como la matriz identidad
        inv_L[i][i]=1;

    for(int i=0;i<n;i++)    ///pasemos por cada columna
    {
        ///el pivote se supone que sea este valor ya que
        ///"se le puede aplicar el m´etodo de Gauss sin realizar intercambios de filas"
        ///debe implicar esto(sino seria una complicacion, la verdad)
        ///int pivote=i;
        for(int j=i+1;j<n;j++)
        {
            if(abs(A[j][i])<eps)
                continue;
            ///el metodo de Gauss
            ld c=A[j][i]/A[i][i];     ///coeficiente del pivoteo
            for(int k=i;k<n;k++)
                A[j][k]-=(c*A[i][k]); ///aplicar el pivoteo sobre A'

            ///modificar la inversa de L
            for(int k=0;k<=i;k++)
                inv_L[j][k]-=(c*inv_L[i][k]); ///aplicar el pivoteo sobre M
        }
    }

    ///veamos

    /**
    print(aa);
    print(A);
    print(inv_L);
    print(inv_L*aa);
    assert(A==(inv_L*aa));
    **/

    /**
    notar aqui que ya A es la matriz U buscada.

    solo queda hallar la inversa de inv_L, es decir L
    analogamente se puede usar lo que ya hicimos:
    inv_L*aa=A y L*inv_L=I son analogos
    **/

    ///hago lo mismo que anteriormente, por eso quito los comentarios
    matrix L(n,vector<ld>(n));
    for(int i=0;i<n;i++)
        L[i][i]=1;

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(abs(inv_L[j][i])<eps)
                continue;
            ld c=inv_L[j][i]/inv_L[i][i];
            for(int k=i;k<n;k++)
                inv_L[j][k]-=(c*inv_L[i][k]);

            for(int k=0;k<=i;k++)
                L[j][k]-=(c*L[i][k]);
        }
    }

    return pmm(L,A); ///esto es en realidad L y U.
}

pmmm PLU_dec(matrix A)
{
    ///A es cuadrada
    int n=A.size();
    vector<int> p(n);
    matrix inv_L(n,vector<ld>(n));
    for(int i=0;i<n;i++)    ///la seteamos como la matriz identidad
    {                       ///y la permutacion identidad
        inv_L[i][i]=1;
        p[i]=i;
    }

    for(int i=0;i<n;i++)    ///pasemos por cada columna
    {
        ///busquemos el pivote
        int piv=-1;
        for(int j=i;j<n;j++)
            if(abs(A[j][i])>eps)
            {
                piv=j;
                break;
            }
        ///intercambiar las filas
        swap(p[i],p[piv]);          ///se modifica la matriz permutacion
        for(int j=i;j<n;j++)
            swap(A[piv][j],A[i][j]);///se modifica la matriz A'
        for(int j=0;j<i;j++)
            swap(inv_L[piv][j],inv_L[i][j]); ///se modifica M

        for(int j=i+1;j<n;j++)
        {
            if(abs(A[j][i])<eps)
                continue;
            ///el metodo de Gauss
            ld c=A[j][i]/A[i][i];     ///coeficiente del pivoteo
            for(int k=i;k<n;k++)
                A[j][k]-=(c*A[i][k]); ///aplicar el pivoteo sobre A'

            ///modificar la inversa de L
            for(int k=0;k<=i;k++)
                inv_L[j][k]-=(c*inv_L[i][k]); ///aplicar el pivoteo sobre M
        }
    }

    /**
    notar aqui que ya A es la matriz U buscada.

    solo queda hallar la inversa de inv_L, es decir L
    **/

    ///exactamente como en la descomposicion anterior
    matrix L(n,vector<ld>(n));
    for(int i=0;i<n;i++)
        L[i][i]=1;

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(abs(inv_L[j][i])<eps)
                continue;
            ld c=inv_L[j][i]/inv_L[i][i];
            for(int k=i;k<n;k++)
                inv_L[j][k]-=(c*inv_L[i][k]);

            for(int k=0;k<=i;k++)
                L[j][k]-=(c*L[i][k]);
        }
    }

    matrix P(n,vector<ld>(n));
    for(int i=0;i<n;i++)
        P[p[i]][i]=1;
    return pmmm(pmm(L,A),P); ///esto es en realidad L, U y P.
}

pair<matrix,vector<int>> PLU_dec_work_matrix(matrix A)
{
    ///A es cuadrada
    int n=A.size();
    vector<int> p(n);
    for(int i=0;i<n;i++)    ///la seteamos como la permutacion identidad
        p[i]=i;

    for(int i=0;i<n;i++)    ///pasemos por cada columna
    {
        ///busquemos el pivote
        int piv=-1;
        for(int j=i;j<n;j++)
            if(abs(A[j][i])>eps)
            {
                piv=j;
                break;
            }
        ///intercambiar las filas
        swap(p[i],p[piv]);          ///se modifica la permutacion
        for(int j=0;j<n;j++)
            swap(A[piv][j],A[i][j]);///aplicar el intercambio de filas sobre A

        for(int j=i+1;j<n;j++)
        {
            if(abs(A[j][i])<eps)
                continue;
            ///el metodo de Gauss
            ld c=A[j][i]/A[i][i];     ///coeficiente del pivoteo
            for(int k=0;k<n;k++)
                A[j][k]-=(c*A[i][k]); ///aplicar el pivoteo sobre A
            A[j][i]=-c;
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(abs(A[j][i])<eps)
                continue;
            ld c=A[j][i];
            for(int k=0;k<i;k++)
                A[j][k]-=(c*A[i][k]);
            A[j][i]=-c;
        }
    }

    return {A,p}; ///esto es en realidad L, U y P.
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<ld>> A(n,vector<ld>(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> A[i][j];
/** Descomentar aqui
    pmmm PLU=PLU_dec(A);
    matrix L=PLU.f.f;
    matrix U=PLU.f.s;
    matrix P=PLU.s;
**/

/**o aqui para probar
    auto PLU=PLU_dec_work_matrix(A);
    matrix LU=PLU.f;
    vector<int> p=PLU.s;
    matrix P(n,vector<ld>(n));
    matrix L(n,vector<ld>(n));
    matrix U(n,vector<ld>(n));
    for(int i=0;i<n;i++)
    {
        P[p[i]][i]=1;
        L[i][i]=1;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            if(i<=j)
                U[i][j]=LU[i][j];
            else
                L[i][j]=LU[i][j];
        }
**/

    prec(3);
    print(P);
    print(L);
    print(U);
    matrix aux=P*L*U;
    assert(A==aux); ///esto da error si no son "iguales"

    return 0;
}
/**
ejemplos:
3
1 1 2
1 2 2
1 2 3

4
1.2 1.4 6.0 4.2
0.5 -1 0 4
5 4 3 1
1 2 3 4

4
0 0 1 1
1 1 1 0
2 1 1 1
1 2 3 4
**/
