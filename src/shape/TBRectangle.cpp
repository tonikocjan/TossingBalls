
#include "TBRectangle.h"

TBRectangle::TBRectangle() : TBShape() { }
TBRectangle::TBRectangle(int w_, int h_, int x_, int y_) : TBShape(w_, h_, x_, y_) {}
TBRectangle::TBRectangle(const TBShape& other) : TBShape(other) {}

void TBRectangle::Render() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glColor3f(color.r, color.g, color.b);

	glRotatef(angle, 0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(x - width / 2, y - height / 2);
	glTexCoord2f(0.0, 1.0); glVertex2f(x - width / 2, y + height / 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(x + width / 2, y + height / 2);
	glTexCoord2f(1.0, 0.0); glVertex2f(x + width / 2, y - height / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
