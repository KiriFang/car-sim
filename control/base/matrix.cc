#include "matrix.h"
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;



template <typename T>
void
Matrix<T>::concatenate_r(Matrix<T>& ap) {

	assert(c == ap.size_c());
        
//	cout << "mtx_r = " << mtx.size() << endl;
	for(int i = 0; i < ap.r; i++) {

		mtx.push_back(ap[i]);
	//	cout << mtx.size() << endl;
	}

	r = mtx.size();

}

template <typename T>
void
Matrix<T>::concatenate_c(Matrix<T>& ap) {

        assert(this -> r == ap.size_r());
	vector<T> a =  {1,1,1,1,1};
	typename vector<T>::iterator it = ap[0].end();
        for(int i = 0; i < ap.size_r(); i++) {

		/* err record: if use ap[i].begin() to insert into mtx, there will be err
		 * 'terminate called after ...', because the operator[] return a temporary variable,
		 * we need to redefine it */
		vector<T> a = ap[i];
	       	mtx[i].insert(mtx[i].end(), a.begin(), a.end());

        }

	c = mtx[0].size();
}

template <typename T>
Matrix<T>&
Matrix<T>::concatenate_eye(Matrix<T>& ap) {

	int ar = ap.r, ac = ap.c;
	vector<T> cp(ac, 0);
	vector<T> rp(this -> c, 0);

        for(int i = 0; i < r; i++) {
                        this -> mtx[i].insert(this -> mtx[i].end(), cp.begin(), cp.end());
        }

	for(int i = 0; i < ar; i++) {
		this -> mtx.push_back(rp);
	}

	for(int i = r; i < r + ar; i++) {
		vector<T> a = ap[i - r];
		this -> mtx[i].insert(this -> mtx[i].end(), a.begin(), a.end());
	}

	c = mtx[0].size();
	r = mtx.size();

        return *this;
}

template <typename T>
Matrix<T>
Matrix<T>::transpose() {

	Matrix<T> Tm(c,r);

	for(int i = 0; i < c; i++) {
		for(int j = 0; j < r; j++) {
			Tm[i][j] = mtx[j][i];
		}
	}

	return Tm;
}

template <typename T>
Matrix<T> 
Matrix<T>::inverse() {

	Matrix<T> mat(r,c,1);
	Matrix<T> a = *this;

	if (a.r != a.c)
	{
		cout << "uninversable" << endl;
	}

	int m = a.r; 
	int n = a.c;

	for (int i = 0; i < m; i++) 
	{                         
		
		int k;
		for (k = i; k < m; k++)
		{
			if (fabs(a[k][i]) > 1e-10) 
				break;
		}
		if (k < m)
		{
			if (k != i)
			{
				
				for (int j = 0; j < n; j++)
				{
				        a[0][j] = a[i][j]; a[i][j] = a[k][j]; a[k][j] = a[0][j];
					mat[0][j] = mat[i][j]; mat[i][j] = mat[k][j]; mat[k][j] = mat[0][j];
				}
			}
			double b = a[i][i];//倍数
			
			for (int j = 0; j < n; j++)//从第一个元素开始
			{
				a[i][j] =  a[i][j] / b;
				mat[i][j] = mat[i][j] / b;
			}

//			cout << "changing.." << endl;
			for (int j = i + 1; j < m; j++)
			{
				//注意本来为 -a.mat[j][i]/a.mat[i][i],因为a.mat[i][i]等于 1，则不需要除它
				b = -a[j][i];
				for (k = 0; k < n; k++)
				{
					a[j][k] = a[j][k] + b * a[i][k];//第 i 行 b 倍加到第 j 行
					mat[j][k] = mat[j][k] + b * mat[i][k];
				}
			}
//			cout << "finishing " << endl;
		}
		else
		{
			cout << " uninversable!" << endl;
		}
	}

//	cout << " down to up..." << endl;

	for (int i = m - 1; i >= 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double b = -a[j][i];
			a[j][i] = 0; 
			for (int k = 0; k < n; k++)
			{
				mat[j][k] = mat[j][k] + b * mat[i][k];
			}
		}
	}

	return mat;
}

template class Matrix<int>;
template class Matrix<float>;

