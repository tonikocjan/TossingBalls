#include "TBBlinkAnimator.h"

TBBlinkAnimator::TBBlinkAnimator(const std::string& tex) {
	srand(time(NULL));

	blinkTex = TextureLoader::LoadTex(tex);
	msPrevious = 0;
	defTex = 0;
	timeToNext();

	blink = false;
}

void TBBlinkAnimator::animateSprite(gEntity* e, float time) {
	float currentTimeMs = time * 1000;

	if(defTex == 0) {
		defTex = e->getTexture();
		msPrevious = currentTimeMs;
	}

	float delta = currentTimeMs - msPrevious;
	if(!blink) {
		if(delta > msTimeToNext) {
			blink = true;
			e->setTexture(blinkTex);
			msPrevious = currentTimeMs;
		}
	}
	else {
		if(delta > 100) {
			e->setTexture(defTex);
			timeToNext();
			blink = false;
		}
	}
}

void TBBlinkAnimator::timeToNext() {
	msTimeToNext = rand() % 8000; // najve� 10 sekund med vsako ponovitvijo
	if(msTimeToNext < 100)
		msTimeToNext = 100;
}

