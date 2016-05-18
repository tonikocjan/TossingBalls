#include "TBEntity.h"

gEntity::gEntity(float x, float y, float z, float w, float h, unsigned int texture) : x(x), y(y), z(z), width(w), height(h), tex(texture) {
	bodyType  = 0;
	coords[0] = 0;
	coords[1] = 0;

	coords[2] = 1;
	coords[3] = 0;

	coords[4] = 1;
	coords[5] = 1;

	coords[6] = 0;
	coords[7] = 1;
	opacity   = 100;

	visible   = true;
}

gEntity::~gEntity() {
	std::vector<TBAnimator*>::iterator it = animators.begin();
	std::vector<TBAnimator*>::iterator end = animators.end();

	for (; it != end; ++it) {
		delete (*it);
	}
}

void gEntity::setAnimator(TBAnimator* a) {
	if(a)
		animators.push_back(a);
}
void gEntity::setTexCoordinates(const std::vector<float>& coord) {
	for(int i = 0; i < 8; i++)
		coords[i] = coord[i];
}

