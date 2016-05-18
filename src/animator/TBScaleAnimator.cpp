#include "TBScaleAnimator.h"
#include "../entities/TBEntity.h"

TBScaleAnimator::TBScaleAnimator() {
	defWidth 		= -1;
	defHeight 		= -1;
	stepX 			= 0.1;
	stepY 			= 0.1;
	deltaWidth 		= 0;
	deltaHeight 	= 0;
}

void TBScaleAnimator::animateSprite(gEntity* e, float time) {
	if(FPS != 0 && !stop) {
		float currentTimeMs = time * 1000;

		// �e se je animacija sedaj za�ela, nastavimo za�etni �as kot trenutni �as
		if(msPrevious == -1.0)
			msPrevious = currentTimeMs;

		float delta = currentTimeMs - msPrevious;
		if(delta > msToWait) {
			float w, h;
			w = e->getWidth();
			h = e->getHeight();

			// ko se animacija za�ne prvi� nastavimo privzete vrednosti
			if(defWidth == -1) {
				defWidth = w;
				defHeight = h;
			}

			// �e je step pozitiven
			if(stepX > 0 && stepY > 0) {
				if(w <= deltaWidth)
					w += stepX;
				if(h <= deltaHeight)
					h += stepY;
			}
			else {
				if(w > defWidth)
					w += stepX;
				if(h > defHeight)
					h += stepY;
			}

			e->setSize(w, h);

			msPrevious = currentTimeMs;
		}
	}
}

void TBScaleAnimator::positive() {
	if(stepX < 0) stepX = -stepX;
	if(stepY < 0) stepY = -stepY;
}

void TBScaleAnimator::negative() {
	if(stepX > 0) stepX = -stepX;
	if(stepY > 0) stepY = -stepY;
}

