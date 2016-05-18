
#include "TBButton.h"
#include "../animator/TBScaleAnimator.h"

gButton::gButton() : gEntity(0, 0, 0, 0, 0, -1) { aWidth = aHeight = deltaX = deltaY = 0; speed = 0.02; }
gButton::gButton(float x, float y, float z, float w, float h, unsigned int texture) : gEntity(x, y, z, w, h, texture) {
	aWidth 	= w;
	aHeight = h;
	speed 	= 0.008;
	deltaX 	= deltaY = 5;

	float aspect_ratio = w / h;

	TBScaleAnimator* anim = new TBScaleAnimator();
	anim->setDeltaSize(w + 10, h + 10);
	anim->setStep(-1, -1);
	setAnimator(anim);
}

bool gButton::MouseOver(float px, float py) {
	if((px >= (x - aWidth / 2) && px <= (x + aWidth / 2) &&
		py >= (y - aHeight / 2) && py <= (y + aHeight / 2))) {
		((TBScaleAnimator*)animators[0])->positive();
		return true;
	}
	((TBScaleAnimator*)animators[0])->negative();
	return false;
}

void gButton::Update(double time) {
	std::vector<TBAnimator*>::const_iterator it = animators.begin();
	std::vector<TBAnimator*>::const_iterator end = animators.end();

	for (; it != end; ++it) {
		(*it)->animateSprite(this, time);
	}
}

void gButton::Render(double time, Camera* camera) const {
	b2Vec2 a(x, y);
	b2Vec2 b(width, height);
	b *= 0.5;

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(0,0,0);
		glBindTexture(GL_TEXTURE_2D, tex);

		glBegin(GL_QUADS);
			glTexCoord2f(coords[0], coords[1]); glVertex3f(a.x - b.x, a.y - b.y, z);
			glTexCoord2f(coords[2], coords[3]); glVertex3f(a.x + b.x, a.y - b.y, z);
			glTexCoord2f(coords[4], coords[5]); glVertex3f(a.x + b.x, a.y + b.y, z);
			glTexCoord2f(coords[6], coords[7]); glVertex3f(a.x - b.x, a.y + b.y, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void gButton::setDelta(float x, float y) {
	deltaX = x;
	deltaY = y;
}

