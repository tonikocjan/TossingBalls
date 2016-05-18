
#include "TBFadeAnimator.h"
#include "../entities/TBEntity.h"

TBFadeAnimator::TBFadeAnimator(int startOpacity, int s, int delay) {
	opacity = startOpacity;
	step 	= s;
	msDelay = delay;
}


void TBFadeAnimator::animateSprite(gEntity* e, float time) {
	if(!stop) {
		float currentTimeMs = time * 1000;

		// �e se je animacija sedaj za�ela, nastavimo za�etni �as kot trenutni �as
		if(msPrevious == -1.0) {
			msPrevious = currentTimeMs;
		}

		// z animacijo za�nemo po �elenem zamiku
		float delta = currentTimeMs - msPrevious;
		if(delta > msToWait && delta > msDelay) {
			opacity -= step;
			e->setOpacity(opacity);

			if(opacity >= 100)
				stop = true;
			if(opacity <= 0)
				stop = true;

			msPrevious = currentTimeMs;
		}
	}
}

