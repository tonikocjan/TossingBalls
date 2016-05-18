
#ifndef TBSTOPANIMATOR_H_
#define TBSTOPANIMATOR_H_

#include "TBAnimator.h"

class TBStopAnimator : public TBAnimator {
	public:
		TBStopAnimator(float ms);

		void animateSprite(gEntity* e, float time);

	private:
		float msWhen;
};

#endif /* TBSTOPANIMATOR_H_ */
