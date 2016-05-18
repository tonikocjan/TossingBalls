/*
 * TBTriangle.h
 *
 *  Created on: 14. sep. 2013
 *      Author: Toni
 */

#ifndef TBTRIANGLE_H_
#define TBTRIANGLE_H_
#include "TBShape.h"

class TBTriangle : public TBShape {
	public:
		TBTriangle();
		TBTriangle(int w_, int h_, int x_, int y_);
		TBTriangle(const TBShape& other);

		void Render();
};

#endif /* TBTRIANGLE_H_ */
