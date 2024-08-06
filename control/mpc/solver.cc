#include "solver.h"
#include <iostream>

Solver::Solver(Matrix<float>& H, Matrix<float>& g, Matrix<float>& A_eq, Matrix<float>& b_eq, Matrix<float>& A_ueq, Matrix<float>& b_ueq):
	H(H), g(g),
	Aeq(A_eq),
	beq(b_eq),
	Aueq(A_ueq),
	bueq(b_ueq),
        X(g.c,g.r) {
	}

void 
Solver::InteriorPointsolver() {

	Matrix<float> H1 = H.inverse();
        
cout << "reverse" << H1.size_r() << " " << H1.size_c() << endl;
cout << "reverse" <<X.size_r() << " " << X.size_c() << endl;

	X = H1 * g;

}

