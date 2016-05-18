#pragma once

#include <GLFW/glfw3.h>
#include <math.h>
#include "TBEntity.h"

class TBCannon : public gEntity {
	public:
		TBCannon();
		// t1 - top, t2 - podno�je
		TBCannon(float x, float y, float w, float z, float h, int x2, int y2, float w2, float h2, unsigned int t1, unsigned int t2);

		void Render(double time, Camera* camera) const;
		void Update(double time);
		bool MouseOver(float x, float y);

		void 	setAngle(float a) { angle = a; }
		float 	getAngle() { return angle; }

		float 	getX2() { return x2; }
		float 	getY2() { return y2; }

		float 	getW2() { return w2; }
		float 	getH2() { return h2; }

	private:
		// !NOTE cannon uporablja screen koordinate
		float 			angle;
		unsigned int 	tex2;
		float 			w2, h2;
		float 			x2, y2;

};
