#ifndef TBBLINKANIMATOR_H_
#define TBBLINKANIMATOR_H_

#include <math.h>
#include "TBAnimator.h"
#include "../TextureLoader.h"
#include "../entities/TBEntity.h"

class TBBlinkAnimator : public TBAnimator {

	public:
		TBBlinkAnimator(const std::string& tex);

		void animateSprite(gEntity* e, float time);

	private:
		uint32 blinkTex;
		uint32 defTex;
		float  msTimeToNext;
		float  msPrevious;
		bool   blink;

		void   timeToNext();
};

#endif /* TBBLINKANIMATOR_H_ */
