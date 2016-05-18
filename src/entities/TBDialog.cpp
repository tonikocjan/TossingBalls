
#include "TBDialog.h"

typedef std::vector<gEntity*>::iterator iter;
typedef std::vector<gEntity*>::const_iterator constIter;

TBDialog::TBDialog(int x, int y, int z, int w, int h, uint32 t) : gEntity(x, y, z, w, h, t) {
	clickedButton = 0;
}

void TBDialog::Render(double time, Camera* camera) const {
	if(!visible) return;
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);
		glColor3f(1,1,1);

		b2Vec2 a(x, y);
		b2Vec2 b(width, height);
		b *= 0.5;

		glBegin(GL_QUADS);
			glTexCoord2f(coords[0], coords[1]); glVertex3f(a.x - b.x, a.y - b.y, z);
			glTexCoord2f(coords[2], coords[3]); glVertex3f(a.x + b.x, a.y - b.y, z);
			glTexCoord2f(coords[4], coords[5]); glVertex3f(a.x + b.x, a.y + b.y, z);
			glTexCoord2f(coords[6], coords[7]); glVertex3f(a.x - b.x, a.y + b.y, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	constIter i = children.begin();
	constIter end = children.end();
	while(i != end) {
		(*i)->Render(time, camera);
		i++;
	}
}

void TBDialog::Update(double time) {
	if(!visible) return;
	constIter i = children.begin();
	constIter end = children.end();
	while(i != end) {
		(*i)->Update(time);
		i++;
	}
}

bool TBDialog::MouseOver(float x, float y) {
	if(!visible) return false;
	clickedButton = 0;

	constIter i = children.begin();
	constIter end = children.end();
	int c = 1;
	while(i != end) {
		if((*i)->MouseOver(x, y)) {
			clickedButton = c;
			return true;
		}
		c++;
		i++;
	}
	return false;
}

void TBDialog::addChild(gEntity* e) {
	b2Vec2 pos(e->getX(), e->getY());
	pos.x += x - width / 2;
	pos.y += y - height / 2;

	e->setPosition(pos.x, pos.y);
	children.push_back(e);
}
