#ifndef TBCIRCLE_H_
#define TBCIRCLE_H_

#include "TBShape.h"

class TBCircle : public TBShape {
	public:
		TBCircle();
		TBCircle(int w_, int h_, int x_, int y_);
		TBCircle(const TBShape& other);

		void Render();
};

#endif /* TBCIRCLE_H_ */
