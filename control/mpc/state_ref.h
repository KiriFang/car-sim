#ifndef __MPC_STATE_REF_H__
#define __MPC_STATE_REF_H__

#include <memory>
#include "../control/base/matrix.h"

using namespace std;

class stateRef {

	public: 

		shared_ptr<vector<float>> yref;

		Matrix pre_yref;
		void setpreyRefMatrix();

		stateRef() {};

		~stateRef() {};
};


#endif
