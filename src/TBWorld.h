#pragma once

#include <vector>
#include <algorithm>
#include <Box2D/Box2D.h>

#include "Camera.h"
#include "animator/TBScaleAnimator.h"
#include "animator/TBImageAnimator.h"
#include "animator/TBBlinkAnimator.h"
#include "animator/TBFadeAnimator.h"
#include "animator/TBStopAnimator.h"
#include "entities/TBBody.h"
#include "entities/TBSprite.h"
#include "entities/TBCannon.h"
#include "shape/TBShape.h"

typedef std::vector<gEntity*>::iterator iter;
typedef std::vector<gEntity*>::const_iterator constIter;

struct WorldContext {

    WorldContext(float ts, int vi, int pi, float gr, int width, int height);

	void addObject(gEntity* object);
	void popObject(gEntity* object);
	iter popObject(iter i);
	void resetWorld();

	b2World* 					world;
	Camera* 					camera;

	float32 					timeStep;
    int 						velocityIterations;
    int 						positionIterations;
    b2Vec2* 					gravity;

	std::vector<gEntity*> 		container;		 // vsa telesa
	std::vector<gEntity*> 		disposeBodies;	 // telesa, ki jih �elimo izbrisati

	TBBody* 					groundBody;
	TBCannon* 					cannon;

	int							countBalls;   // �tevilo �og
	int 						countEnemies; // �tevilo nasprotnikov
};

class TBWorld {
	public:
		TBWorld();

		TBBody* createBox(
				float x, float y, float z,
				float w, float h,
				int bodyType,
				unsigned int t1,
				unsigned int t2,
				bool dynamic,
				float density = 0.8f,
				float restitution = 0.5f,
				float friction = 0.3f
		);

		TBBody* createSphere(
				float x, float y, float z,
				float w, float h,
				int bodyType,
				unsigned int t1,
				bool dynamic,
				float density = 1.0f,
				float restitution = 0.5f,
				float friction = 1.f
		);

		TBSprite* createSprite (
				float x, float y, float z,
				float w, float h,
				float rotation,
				unsigned int image
		);

		TBBody* createGroundObject(
				const TBColor3f& c,
				float x, float y,
				float w, float h);

		WorldContext* world;

};

