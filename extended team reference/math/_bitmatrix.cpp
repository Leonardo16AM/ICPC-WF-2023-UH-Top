//
// Boolean coefficient matrix
//
// Description:
//   This admits very fast operations for boolean matrices.
//
// Algorithm:
//   Block matrix decomposition technique:
//   For a matrix A of size n x n, we split A as the block matrix
//   each block is of size n/W x n/W. Here, computation of each
//   W x W block is performed by bit operations;
//
// Complexity: (in practice)
//   O(n^3); however, for practical n, it is basically
//   20--100 times faster than the naive implementation.
//

#include <bits/stdc++.h>

using namespace std;

namespace bitmatrix
{
	typedef unsigned long long ull;

	struct mat
	{
		int n, m;
		vector<vector<ull>> x;
		
		mat(int n, int m) : n(n), m(m), x(1 + n / 8, vector<ull>(1 + m / 8)) {}

		bool get(int i, int j)
		{
			return x[i >> 3][j >> 3] & (1ull << (8 * (i & 7) + (j & 7)));
		}

		void set(int i, int j, int b = true)
		{
			if (b)
				x[i >> 3][j >> 3] |= (1ull << (8 * (i & 7) + (j & 7)));
			else
				x[i >> 3][j >> 3] &= ~(1ull << (8 * (i & 7) + (j & 7)));
		}
	};

	mat eye(int n)
	{
		mat I(n, n);
		for (int i = 0; i < I.x.size(); ++i)
			I.x[i][i] = 0x8040201008040201;
		return I;
	}

	mat add(mat A, const mat &B)
	{
		for (int i = 0; i < A.x.size(); ++i)
			for (int j = 0; j < A.x[0].size(); ++j)
				A.x[i][j] |= B.x[i][j];
		return A;
	}

	// 8 x 8 matrix product in 128 bit operations.
	// (cf: naive method requires 1024 ops)
	ull mul(ull a, ull b)
	{
		// C[i][j] |= A[i][k] & B[k][j]
		const ull u = 0x101010101010101, v = 0xff;
		ull x, y, c = 0;
		x = a & (u << 0); x |= (x << 1); x |= (x << 2); x |= (x << 4);
		y = b & (v << 0); y |= (y << 8); y |= (y << 16); y |= (y << 32);
		c |= (x & y);
		x = a & (u << 1); x |= (x >> 1); x |= (x << 2); x |= (x << 4);
		y = b & (v << 18); y |= (y >> 8); y |= (y << 16); y |= (y << 32);
		c |= (x & y);
		x = a & (u << 2); x |= (x << 1); x |= (x >> 2); x |= (x << 4);
		y = b & (v << 16); y |= (y << 8); y |= (y >> 16); y |= (y << 32);
		c |= (x & y);
		x = a & (u << 3); x |= (x >> 1); x |= (x >> 2); x |= (x << 4);
		y = b & (v << 24); y |= (y >> 8); y |= (y >> 16); y |= (y << 32);
		c |= (x & y);
		x = a & (u << 4); x |= (x << 1); x |= (x << 2); x |= (x >> 4);
		y = b & (v << 32); y |= (y << 8); y |= (y << 16); y |= (y >> 32);
		c |= (x & y);
		x = a & (u << 5); x |= (x >> 1); x |= (x << 2); x |= (x >> 4);
		y = b & (v << 40); y |= (y >> 8); y |= (y << 16); y |= (y >> 32);
		c |= (x & y);
		x = a & (u << 6); x |= (x << 1); x |= (x >> 2); x |= (x >> 4);
		y = b & (v << 48); y |= (y << 8); y |= (y >> 16); y |= (y >> 32);
		c |= (x & y);
		x = a & (u << 7); x |= (x >> 1); x |= (x >> 2); x |= (x >> 4);
		y = b & (v << 56); y |= (y >> 8); y |= (y >> 16); y |= (y >> 32);
		c |= (x & y);
		return c;
	}

	mat mul(mat A, mat B)
	{
		mat C(A.n, B.m);
		for (int i = 0; i < A.x.size(); ++i)
			for (int k = 0; k < B.x.size(); ++k)
				for (int j = 0; j < B.x[0].size(); ++j)
					C.x[i][j] |= mul(A.x[i][k], B.x[k][j]);
		return C;
	}

	mat pow(mat A, int k)
	{
		if (k == 0)
			return eye(A.n);
		if (k & 1)
			return mul(A, pow(mul(A, A), k / 2));
		return pow(mul(A, A), k / 2);
	}
}
