
#include "TBImageAnimator.h"
#include "../entities/TBEntity.h"
using namespace std;

TBImageAnimator::TBImageAnimator() {
	n = 0;
	currentFrame = 0;
	loop = true;
}

void TBImageAnimator::animateSprite(gEntity* e, float time) {
	if(!stop) {
		float currentTimeMs = time * 1000;

		// �e se je animacija sedaj za�ela, nastavimo za�etni �as kot trenutni �as
		if(msPrevious == -1.0) {
			msPrevious = currentTimeMs;
			e->setTexture(texture);
			e->setTexCoordinates(coord[currentFrame++]);
		}

		float delta = currentTimeMs - msPrevious;
		if(delta > msToWait) {
			if(currentFrame >= n ) {
				if(loop)
					currentFrame = 0;
			}

			e->setTexCoordinates(coord[currentFrame++]);

			msPrevious = currentTimeMs;
		}
	}
}

void TBImageAnimator::createAnimation(const std::string& path, int n) {
	this->image	 	= path;
	this->n			= n;

	texture = TextureLoader::LoadTex(path);

	for(int i = 0; i < n; i++) {
		float c[8];

		float a = (float)i / (float)n;
		float b = (float)(i + 1.0) / (float)n;

		c[0] = a;
		c[1] = 0;
		c[2] = b;
		c[3] = 0;

		c[4] = b;
		c[5] = 1;
		c[6] = a;
		c[7] = 1;

		vector<float> x(c, c + sizeof(c)/sizeof(c[0]));
		coord.push_back(x);
	}

	currentFrame = 0;
}
