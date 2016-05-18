
#ifndef TBRECTANGLE_H_
#define TBRECTANGLE_H_

#include "TBShape.h"

class TBRectangle : public TBShape {
	public:
		TBRectangle();
		TBRectangle(int w_, int h_, int x_, int y_);
		TBRectangle(const TBShape& other);

		void Render();
};

#endif /* TBRECTANGLE_H_ */
