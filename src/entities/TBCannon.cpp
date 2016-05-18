#include "TBCannon.h"

TBCannon::TBCannon() : gEntity(0, 0, 0, 0, 0, -1), angle(0), tex2(-1) {}

TBCannon::TBCannon(float x, float y, float z, float w, float h, int x2, int y2, float w2, float h2, unsigned int t1, unsigned int t2) :
		gEntity(x, y, z, w, h, t1), angle(0.0), tex2(t2), w2(w2), h2(h2), x2(x2), y2(y2)
{
}

bool TBCannon::MouseOver(float px, float py) {
	if((px >= (x2 - w2 / 2) && px <= (x2 + h2 / 2) &&
		py >= (y2 - h2 / 2) && py <= (y2 + w2 / 2))) {
		return true;
	}
	return false;
}

void TBCannon::Update(double time) {}

void TBCannon::Render(double time, Camera* camera) const {
	b2Vec2 a(x, y);
	b2Vec2 b(width, height);
	b *= 0.5;

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(0,0,0);
		glBindTexture(GL_TEXTURE_2D, tex);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(a.x - b.x, a.y - b.y, z);
			glTexCoord2f(1.0, 0.0); glVertex3f(a.x + b.x, a.y - b.y, z);
			glTexCoord2f(1.0, 1.0); glVertex3f(a.x + b.x, a.y + b.y, z);
			glTexCoord2f(0.0, 1.0); glVertex3f(a.x - b.x, a.y + b.y, z);
		glEnd();

		glTranslatef(x2 - w2/2 + 12, y2 - h2/2, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-(x2 - w2/2 + 12), -(y2 - h2/2), 0);

		glBindTexture(GL_TEXTURE_2D, tex2);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x2 - w2/2, y2 - h2/2, z);
			glTexCoord2f(1.0, 0.0); glVertex3f(x2 + w2/2, y2 - h2/2, z);
			glTexCoord2f(1.0, 1.0); glVertex3f(x2 + w2/2, y2 + h2/2, z);
			glTexCoord2f(0.0, 1.0); glVertex3f(x2 - w2/2, y2 + h2/2, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
