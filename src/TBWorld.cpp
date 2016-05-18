#include "TBWorld.h"

WorldContext::WorldContext(float ts, int vi, int pi, float gr, int width, int height) {
	camera = new Camera(b2Vec2(width / 10, height / 10), b2Vec2(width, height));
	camera->updated = true;

	gravity = new b2Vec2(0.0f, gr);
	world = new b2World(*gravity);

	timeStep = ts;
	velocityIterations = vi;
	positionIterations = pi;

	countBalls = 0;
	countEnemies = 0;

	groundBody = NULL;
	cannon = NULL;
}

void WorldContext::addObject(gEntity* object) {
	if(object->getType() == EBT_enemy)
		countEnemies++;
	container.push_back(object);
}

void WorldContext::popObject(gEntity* object) {
	container.erase(std::remove(container.begin(), container.end(), object), container.end());
	disposeBodies.erase(std::remove(container.begin(), container.end(), object), container.end());
	delete object;
}
iter WorldContext::popObject(iter i) {
	delete (*i);
	disposeBodies.erase(i);
	return container.erase(i);
}

void WorldContext::resetWorld() {
	container.clear();
	disposeBodies.clear();
	countBalls 		= 0;
	countEnemies 	= 0;
	cannon 			= NULL;
	groundBody 		= NULL;
	world 			= new b2World(*gravity);
}

TBWorld::TBWorld() {}

TBBody* TBWorld::createBox(
		float x, float y, float z,
		float w, float h,
		int bodyType,
		unsigned int t1,
		unsigned int t2,
		bool dynamic,
		float density,
		float restitution,
		float friction
)
{
	TBBody* e = new TBBody(world->world, x, y, z, w, h, bodyType, EST_rect, t1, dynamic);

	// referenci na world in body
	b2World* wr = world->world;
	b2Body* body;

	// nastavitve telesa
	b2BodyDef bodyDef;
	b2Vec2 pos(x, y);

	bodyDef.position.Set(pos.x, pos.y);
	if(dynamic) bodyDef.type = b2_dynamicBody;
	else 		bodyDef.type = b2_staticBody;

	body = wr->CreateBody(&bodyDef);

	// pravokotnik
	b2PolygonShape box;
	b2Vec2 size(w / 2, h / 2);
	box.SetAsBox(size.x, size.y);

	// fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	body->CreateFixture(&fixtureDef);

	e->setBody(body);

	world->addObject(e);
	body->SetUserData(e);
	return e;
}

TBBody* TBWorld::createSphere(
		float x, float y, float z,
		float w, float h,
		int bodyType,
		unsigned int t1,
		bool dynamic,
		float density,
		float restitution,
		float friction
)
{
	TBBody* e = new TBBody(world->world, x, y, z, w, h, bodyType, EST_circle, t1, dynamic);

	// referenci na world in body
	b2World* wr = world->world;
	b2Body* body;

	b2BodyDef bodyDef;
	b2Vec2 pos(x, y);

	// nastavitve telesa
	bodyDef.position.Set(pos.x, pos.y);
	if(dynamic) bodyDef.type = b2_dynamicBody;
	else 		bodyDef.type = b2_staticBody;

	body = wr->CreateBody(&bodyDef);

	// krog
    b2CircleShape circle;
    circle.m_radius = w / 2;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	body->CreateFixture(&fixtureDef);

	e->setBody(body);

	world->addObject(e);
	body->SetUserData(e);

	return e;
}

TBSprite* TBWorld::createSprite(
		float x, float y, float z,
		float w, float h,
		float rotation,
		unsigned int image)
{

	TBSprite* e = new TBSprite(x, y, z, w, h, image);
	e->setRotation(rotation);

	world->addObject(e);
	return e;
}

TBBody* TBWorld::createGroundObject(
		const TBColor3f& c,
		float x,
		float y,
		float w,
		float h)
{
	TBBody* e = new TBBody(world->world, x, y, 0, w, h, EBT_groundObject, EST_rect, -1, false);

	// referenci na world in body
	b2World* wr = world->world;
	b2Body* body;

	b2BodyDef bodyDef;
	b2Vec2 pos(x, y);

	// nastavitve telesa
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.type = b2_staticBody;

	body = wr->CreateBody(&bodyDef);

	// pravokotnik
	b2PolygonShape box;
	b2Vec2 size(w / 2, h / 2); /*= camera->worldToScreen(wd, hg);*/
	box.SetAsBox(size.x, size.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.friction = 1.0;

	body->CreateFixture(&fixtureDef);

	e->setBody(body);

	world->addObject(e);
	body->SetUserData(e);
	return e;
}
