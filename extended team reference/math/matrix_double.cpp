/*
	Matrix Computation Algorithms (double)
*/

typedef vector<double> vec;
typedef vector<vec> mat;

int sign(double x)
{
	return x < 0 ? -1 : 1;
}

mat eye(int n)
{
	mat I(n, vec(n));
	for (int i = 0; i < n; ++i)
		I[i][i] = 1;
	return I;
}

mat add(mat A, const mat &B)
{
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < A[0].size(); ++j)
			A[i][j] += B[i][j];
	return A;
}

mat mul(mat A, const mat &B)
{
	for (int i = 0; i < A.size(); ++i)
	{
		vec x(A[0].size());
		for (int k = 0; k < B.size(); ++k)
			for (int j = 0; j < B[0].size(); ++j)
				x[j] += A[i][k] * B[k][j];
		A[i].swap(x);
	}
	return A;
}

mat pow(mat A, int k)
{
	mat X = eye(A.size());
	for (; k > 0; k /= 2)
	{
		if (k & 1)
			X = mul(X, A);
		A = mul(A, A);
	}
	return X;
}

double diff(vec a, vec b)
{
	double S = 0;
	for (int i = 0; i < a.size(); ++i)
		S += (a[i] - b[i]) * (a[i] - b[i]);
	return sqrt(S);
}

double diff(mat A, mat B)
{
	double S = 0;
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < A[0].size(); ++j)
			S += (A[i][j] - B[i][j]) * (A[i][j] - B[i][j]);
	return sqrt(S);
}

vec mul(mat A, vec b)
{
	vec x(A.size());
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < A[0].size(); ++j)
			x[i] += A[i][j] * b[j];
	return x;
}

mat transpose(mat A)
{
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < i; ++j)
			swap(A[i][j], A[j][i]);
	return A;
}

double det(mat A)
{
	double D = 1;
	for (int i = 0; i < A.size(); ++i)
	{
		int p = i;
		for (int j = i + 1; j < A.size(); ++j)
			if (fabs(A[p][i]) < fabs(A[j][i]))
				p = j;
		swap(A[p], A[i]);
		for (int j = i + 1; j < A.size(); ++j)
			for (int k = i + 1; k < A.size(); ++k)
				A[j][k] -= A[i][k] * A[j][i] / A[i][i];
		D *= A[i][i];
		if (p != i)
			D = -D;
	}
	return D;
}

// assume: A is non-singular
vec solve(mat A, vec b)
{
	for (int i = 0; i < A.size(); ++i)
	{
		int p = i;
		for (int j = i + 1; j < A.size(); ++j)
			if (fabs(A[p][i]) < fabs(A[j][i]))
				p = j;
		swap(A[p], A[i]);
		swap(b[p], b[i]);
		for (int j = i + 1; j < A.size(); ++j)
		{
			for (int k = i + 1; k < A.size(); ++k)
				A[j][k] -= A[i][k] * A[j][i] / A[i][i];
			b[j] -= b[i] * A[j][i] / A[i][i];
		}
	}
	for (int i = A.size() - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < A.size(); ++j)
			b[i] -= A[i][j] * b[j];
		b[i] /= A[i][i];
	}
	return b;
}

// TODO: verify
mat solve(mat A, mat B)
{
	// A^{-1} B
	for (int i = 0; i < A.size(); ++i)
	{
		// forward elimination
		int p = i;
		for (int j = i + 1; j < A.size(); ++j)
			if (fabs(A[p][i]) < fabs(A[j][i]))
				p = j;
		swap(A[p], A[i]);
		swap(B[p], B[i]);
		for (int j = i + 1; j < A.size(); ++j)
		{
			double coef = A[j][i] / A[i][i];
			for (int k = i; k < A.size(); ++k)
				A[j][k] -= A[i][k] * coef;
			for (int k = 0; k < B[0].size(); ++k)
				B[j][k] -= B[i][k] * coef;
		}
	}
	for (int i = A.size() - 1; i >= 0; --i)
	{
		// backward substitution
		for (int j = i + 1; j < A.size(); ++j)
			for (int k = 0; k < 0; ++k)
				B[i][k] -= A[i][j] * B[j][k];
		for (int k = 0; k < B[0].size(); ++k)
			B[i][k] /= A[i][i];
	}
	return B;
}

// LU factorization
struct lu_data
{
	mat A;
	vector<int> pi;
};

lu_data lu(mat A)
{
	vector<int> pi;
	for (int i = 0; i < A.size(); ++i)
	{
		int p = i;
		for (int j = i + 1; j < A.size(); ++j)
			if (fabs(A[p][i]) < fabs(A[j][i]))
				p = j;
		pi.push_back(p);
		swap(A[p], A[i]);
		for (int j = i + 1; j < A.size(); ++j)
		{
			for (int k = i + 1; k < A.size(); ++k)
				A[j][k] -= A[i][k] * A[j][i] / A[i][i];
			A[j][i] /= A[i][i];
		}
	}
	return {A, pi};
}

vec solve(lu_data LU, vec b)
{
	mat &A = LU.A;
	vector<int> &pi = LU.pi;
	for (int i = 0; i < pi.size(); ++i)
		swap(b[i], b[pi[i]]);
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < i; ++j)
			b[i] -= A[i][j] * b[j];
	for (int i = A.size() - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < A.size(); ++j)
			b[i] -= A[i][j] * b[j];
		b[i] /= A[i][i];
	}
	return b;
}
