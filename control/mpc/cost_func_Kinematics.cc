#include "cost_func_Kinematics.h"
#include <cmath>
#include <iostream>

using namespace std;


costFuncKinematics::costFuncKinematics(Param::mpcParam* mpcp, Param::weightParam* wp, cParam cp, mParam mp, float t, bool increment): 
	costFunc(mpcp, wp, cp, mp, t, increment) {

//		if(isincrement) {
//			costparam.mpcparam.Nx = costparam.mpcparam.Nx + costparam.mpcparam.Nu;
//		}

//		setsystemMatrix();
}

void 
costFuncKinematics::setsystemMatrix() {

	        /* define A matrix */
                for(int i = 0; i < A.size_r(); i++) {
                        for(int j = 0; j < A.size_c(); j++) {
                                if(i == j) {
                                        A[i][j] = 1;
                                }
                                else if(i == 0 && j == 2) {
                                        A[i][j] = - mparam.v * sin(mparam.phi) * T;
                                }
                                else if(i == 1 && j == 2) {
                                        A[i][j] = mparam.v * cos(mparam.phi) * T;
                                }
                                else {
                                        A[i][j] = 0;
                                }
                        }
                }

		/* define B matrix */

                for(int i = 0; i < B.size_r(); i++) {
                        for(int j = 0; j < B.size_c(); j++) {
                                if(i == 0 && j == 0) {
                                        B[i][j] = cos(mparam.phi) * T;
                                }
                                else if(i == 1 && j == 0) {
                                        B[i][j] = sin(mparam.phi) * T;
                                }
                                else if(i == 2 && j == 0) {
                                        B[i][j] = tan(mparam.theta) * T / cparam.length;
                                }
                                else if(i == 2 && j == 1) {
                                        B[i][j] = mparam.v / cparam.length / cos(mparam.theta) / cos(mparam.theta) * T;
                                }
                                else {
                                        B[i][j] = 0;
                                }
                        }
                }

		/* define C matrix */

		for(int i = 0; i < C.size_r(); i++) {
			for(int j = 0; j < C.size_c(); j++) {
				if(i == j) {
					C[i][j] = 1;
				}
				else {
					C[i][j] = 0;
				}
			}
		}

		/* if is increment, reconstruct system matrix */
		if(is_increment) {

			Matrix<float> A21(B.size_c(), B.size_r());
			Matrix<float> A22(B.size_c(), B.size_c(), 1);
			Matrix<float> Bb = A22;
			Matrix<float> Cb(costparam.mpcparam.Ny, costparam.mpcparam.Nu);

			/*join to realize the increment A B  */
			A.concatenate_c(B);
			A21.concatenate_c(A22);
			C.concatenate_c(Cb);

			A.concatenate_r(A21);
			B.concatenate_r(Bb);

		}

}

