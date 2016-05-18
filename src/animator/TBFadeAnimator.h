
#ifndef TBFADEANIMATOR_H_
#define TBFADEANIMATOR_H_
#include "TBAnimator.h"

class TBFadeAnimator : public TBAnimator {
	public:
		TBFadeAnimator(int startOpacity, int s, int delay);

		void animateSprite(gEntity* e, float time);

	private:
		int opacity;
		int step;
		int msDelay;
};

#endif /* TBFADEANIMATOR_H_ */
