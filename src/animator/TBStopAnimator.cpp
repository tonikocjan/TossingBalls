#include "TBStopAnimator.h"
#include "../entities/TBEntity.h"

TBStopAnimator::TBStopAnimator(float ms) {
	msWhen = ms;
}

void TBStopAnimator::animateSprite(gEntity* e, float time) {
	if(!stop) {
		float currentTimeMs = time * 1000;

		// �e se je animacija sedaj za�ela, nastavimo za�etni �as kot trenutni �as
		if(msPrevious == -1.0) {
			msPrevious = currentTimeMs;
		}

		float delta = currentTimeMs - msPrevious;
		if(delta > msWhen) {
			stop = true;
			e->setVisible(false);
		}
	}
}

