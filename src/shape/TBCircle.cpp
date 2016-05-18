/*
 * TBCircle.cpp
 *
 *  Created on: 14. sep. 2013
 *      Author: Toni
 */

#include "TBCircle.h"

TBCircle::TBCircle() : TBShape() { }
TBCircle::TBCircle(int w_, int h_, int x_, int y_) : TBShape(w_, h_, x_, y_) {}
TBCircle::TBCircle(const TBShape& other) : TBShape(other) {}

void TBCircle::Render() {
	glPushMatrix();
	glTranslatef(x, y, 0.0);

	glColor3f(color.r, color.g, color.b);

	int w = width / 2;
	int h = height / 2;

	glBegin(GL_TRIANGLE_FAN);

	for(float i = 0; i < 2 * M_PI; i += M_PI / 16) {
		glVertex2f(sin(i) * w, cos(i) * h);
	}

	glEnd();
	glPopMatrix();
}

