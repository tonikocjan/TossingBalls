#include "TBBody.h"
#include "../animator/TBAnimator.h"

TBBody::TBBody(
		b2World* context,
		float x, float y, float z,
		float w, float h,
		int bodyType,
		int shapeType,
		unsigned int t1,
		bool dynamic)
	: gEntity(x, y, z, w, h, t1)
{
	this->angle	   	= 0;
	this->bodyType 	= bodyType;
	this->dynamic  	= dynamic;
	this->world    	= context;
	this->hp	   	= 100;
	this->collision = false;
	this->force 	= 0;

	if(bodyType == 0) bodyType = 5; // prepre�imo nedefiniran objekt
}

TBBody::~TBBody() {
	if(world != NULL)
		world->DestroyBody(body);
}

bool TBBody::MouseOver(float x, float y) { return false; }

void TBBody::Render(double time, Camera* camera) const {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);
		glColor3f(0,0,0);

		b2Vec2 a(x, y);
		b2Vec2 b(width, height);

		a = camera->worldToScreen(a);
		b = camera->worldToScreen(b);
		b *= 0.5;

		// rotiramo objekt
		glTranslatef(a.x, a.y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-a.x, -a.y, 0);

		glBegin(GL_QUADS);
			glTexCoord2f(coords[0], coords[1]); glVertex3f(a.x - b.x, a.y - b.y, z);
			glTexCoord2f(coords[2], coords[3]); glVertex3f(a.x + b.x, a.y - b.y, z);
			glTexCoord2f(coords[4], coords[5]); glVertex3f(a.x + b.x, a.y + b.y, z);
			glTexCoord2f(coords[6], coords[7]); glVertex3f(a.x - b.x, a.y + b.y, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void TBBody::Update(double time) {
	// rotiramo in posodobimo pozicijo
	setPosition(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * TODEGREES;

	std::vector<TBAnimator*>::const_iterator it = animators.begin();
	std::vector<TBAnimator*>::const_iterator end = animators.end();

	for (; it != end; ++it) {
		(*it)->animateSprite(this, time);
	}
}

void TBBody::handleCollision(float force) {
	// �e je to telo 'tla' ne naredi ni�esar
	if(bodyType == EBT_groundObject) return;
	this->force = force;
}
