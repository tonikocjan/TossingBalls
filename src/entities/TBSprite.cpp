#include "TBSprite.h"
#include "../animator/TBAnimator.h"
using namespace std;

TBSprite::TBSprite(float x, float y, float z, float w, float h, unsigned int texture) : gEntity(x, y, z, w, h, texture) {
	bodyType = EBT_sprite;
	rotation = 0;
	this->z = z;
}

TBSprite::~TBSprite() {}

void TBSprite::Update(double time) {
	std::vector<TBAnimator*>::const_iterator it = animators.begin();
	std::vector<TBAnimator*>::const_iterator end = animators.end();

	for (; it != end; ++it) {
		(*it)->animateSprite(this, time);
	}
}

bool TBSprite::MouseOver(float x, float y) { return false; }

void TBSprite::Render(double time, Camera* camera) const {
	b2Vec2 a(x, y);
	b2Vec2 b(width, height);
	b *= 0.5;

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(0,0,0);
		glBindTexture(GL_TEXTURE_2D, tex);

		if(rotation != 0.0) {
			glTranslatef(x, y, 0);
			glRotatef(time * rotation, 0, 0, 1);
			glTranslatef(-x, -y, 0);
		}

		glBegin(GL_QUADS);
			glTexCoord2f(coords[0], coords[1]); glVertex3f(a.x - b.x, a.y - b.y, z);
			glTexCoord2f(coords[2], coords[3]); glVertex3f(a.x + b.x, a.y - b.y, z);
			glTexCoord2f(coords[4], coords[5]); glVertex3f(a.x + b.x, a.y + b.y, z);
			glTexCoord2f(coords[6], coords[7]); glVertex3f(a.x - b.x, a.y + b.y, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

