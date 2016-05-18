
#ifndef TBSCALEANIMATOR_H_
#define TBSCALEANIMATOR_H_

#include "TBAnimator.h"

/**
 * Animator za pove�evanje/zmanj�evanje objektov
 *
 */
class TBScaleAnimator: public TBAnimator {

	public:
		TBScaleAnimator();

		void animateSprite(gEntity* e, float time);

		void setDeltaSize(float w, float h) { deltaWidth = w; deltaHeight = h; }
		void setStep(float x, float y) { stepX = x; stepY = y; }
		void positive();
		void negative();

	private:
		// na koliko naj scala
		float deltaWidth;
		float deltaHeight;
		// korak
		float stepX;
		float stepY;
		// privzeta velikost
		float defWidth;
		float defHeight;
};

#endif /* TBSCALEANIMATOR_H_ */
