#include "TBAnimator.h"

TBAnimator::TBAnimator() {
	loop = false;
	setFPS(60);
	msPrevious = -1.0;
	stop = false;
}

TBAnimator::~TBAnimator() {}

