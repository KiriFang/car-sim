#ifndef __MPC_COST_FUNC_H__
#define __MPC_COST_FUNC_H__

#include "param.h"
#include "state.h"
#include "../car/car.h"
#include "../test/car_test.h"
#include "../control/base/matrix.h"

typedef Car::carParam cParam;
typedef Car::motionParam mParam;

class costFunc {
	public:
		friend class testmpc;

		Param costparam;

	 	virtual void setHMatrix(float rho);
		virtual void setgMatrix(Matrix<float>& yref, Matrix<float>& cur_state);
		virtual void setsystemMatrix() {};
		virtual void setpreMatrix();
		virtual void getcostFunc() {};
		void setpreWtMatrix();

		bool is_increment;

		costFunc() {};
		costFunc(Param::mpcParam* mpcp, Param::weightParam* wp, cParam cp, mParam mp, float t, bool inc);
		virtual ~costFunc() {};

	protected:
		float T; // time step

		State state;

		cParam cparam;
		mParam mparam;

		Matrix<float> H;
		Matrix<float> g;

		Matrix<float> preQ, preR;
		Matrix<float> preA, A;
		Matrix<float> preB, B;
		Matrix<float> C;

};

#endif
