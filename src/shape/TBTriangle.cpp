#include "TBTriangle.h"

TBTriangle::TBTriangle() : TBShape() { }
TBTriangle::TBTriangle(int w_, int h_, int x_, int y_) : TBShape(w_, h_, x_, y_) {}
TBTriangle::TBTriangle(const TBShape& other) : TBShape(other) {}

void TBTriangle::Render() {
	glPushMatrix();

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex2f(x - width / 2, y - height / 2);
	glTexCoord2f(1.0, 0.0); glVertex2f(x + width / 2, y - height / 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(x, y + height / 2);
	glEnd();

	glPopMatrix();
}

