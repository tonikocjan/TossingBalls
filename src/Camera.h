// source: http://www.deluge.co/?q=screen-to-world-coordinates-in-box2d

#ifndef CAMERA_H_
#define CAMERA_H_
#include <Box2D/Box2D.h>
#include <string>
#include <GLFW/glfw3.h>

class Camera {

	public:
		b2Vec2 rotationOrigin;
		float rotation;

		bool updated;

		b2Vec2 scaleWorldToScreen;
		b2Vec2 scaleScreenToWorld;

		// Coordinate of bottom left hand corner of screen
		b2Vec2 screenMin;
		// Coordinate of top right hand corner of screen
		b2Vec2 screenMax;

		// Coordinate of bottom left hand corner of world
		b2Vec2 worldMin;
		// Coordinate of bottom top right corner of world
		b2Vec2 worldMax;

		/*
		 *  Screen max/min in world - i.e. if the world extends from 0 - 100 but you only want to display
		 *  from 50 - 100 then screenMinInWorld = (50, 50) screenMaxInWorld(100, 100)
		 */
		b2Vec2 screenMinInWorld;
		b2Vec2 screenMaxInWorld;

		int zoom;
		float ZoomDelta() {
			if(zoom == 0) return 1.0;
			if(zoom > 0) return zoom * 0.65;
			return zoom * 1.33;
		}


		Camera(b2Vec2 worldMin, b2Vec2 worldMax, b2Vec2 screenMin, b2Vec2 screenMax, b2Vec2 screenMinInWorld, b2Vec2 screenMaxInWorld) {
			rotation = 0; rotationOrigin = scaleScreenToWorld = scaleWorldToScreen = b2Vec2(0,0); updated = false;
			setCamera(worldMin, worldMax, screenMin, screenMax, screenMinInWorld, screenMaxInWorld);
		}
		Camera( b2Vec2 worldMax, b2Vec2 screenMax, b2Vec2 screenMinInWorld, b2Vec2 screenMaxInWorld) {
			rotation = 0; rotationOrigin = scaleScreenToWorld = scaleWorldToScreen = b2Vec2(0,0); updated = false;
			setCamera(b2Vec2(0,0), worldMax, b2Vec2(0,0), screenMax, screenMinInWorld, screenMaxInWorld);
		}
		Camera( b2Vec2 worldMax, b2Vec2 screenMax) {
			rotation = 0; rotationOrigin = scaleScreenToWorld = scaleWorldToScreen = b2Vec2(0,0); updated = false;
			setCamera(b2Vec2(0,0), worldMax, b2Vec2(0,0), screenMax, b2Vec2(0,0), worldMax);
		}

		void setCamera(b2Vec2 worldMin, b2Vec2 worldMax, b2Vec2 screenMin, b2Vec2 screenMax, b2Vec2 screenMinInWorld, b2Vec2 screenMaxInWorld) {
			scaleWorldToScreen.x = (screenMax.x-screenMin.x)/(screenMaxInWorld.x-screenMinInWorld.x);
			scaleWorldToScreen.y = (screenMax.y-screenMin.y)/(screenMaxInWorld.y-screenMinInWorld.y);

			scaleScreenToWorld.x = 1/scaleWorldToScreen.x;
			scaleScreenToWorld.y = 1/scaleWorldToScreen.y;

			this->screenMin = screenMin;
			this->screenMax = screenMax;
			this->worldMin = worldMin;
			this->worldMax = worldMax;
//			this->screenMinInWorld = screenMinInWorld;
//			this->screenMaxInWorld = screenMaxInWorld;
			this->screenMinInWorld = screenMin;
			this->screenMaxInWorld = screenMax;

			zoom = 0;
			zoomOut();
			zoomOut();
		}

		b2Vec2 worldToScreen(float x, float y) {
			return worldToScreen(b2Vec2(x,y));
		}

		b2Vec2 worldToScreen(b2Vec2 world) {
			b2Vec2 screen = b2Vec2();
			screen.x = screenMin.x + scaleWorldToScreen.x * (world.x - worldMin.x - screenMinInWorld.x);
			screen.y = screenMin.y + scaleWorldToScreen.y * (world.y - worldMin.y - screenMinInWorld.y);

			return screen;
		  }

		b2Vec2 screenToWorld(float x, float y) {
			return screenToWorld(b2Vec2(x,y));
		}
		b2Vec2 screenToWorld(b2Vec2 screen) {
			b2Vec2 world = b2Vec2();
			world.x = (screen.x - screenMin.x)*scaleScreenToWorld.x + worldMin.x + screenMinInWorld.x;
			world.y = (screen.y - screenMin.y)*scaleScreenToWorld.y + worldMin.y + screenMinInWorld.y;
			return world;
		}

		float worldWidth() {
			return (worldMax.x - worldMin.x);
		}
		float worldHeight() {
			return (worldMax.y - worldMin.y);
		}
		float screenWidth() {
			return (screenMax.x - screenMin.x);
		}
		float screenHeight() {
			return (screenMax.y - screenMin.y);
		}

		std::string toString() {
			std::string s = "";
//			s += screenMin.toString()+" -> "+screenToWorld(screenMin).toString()+"\n";
//			s += screenMax.toString()+" -> "+screenToWorld(screenMax).toString();
			return s;
		}

		// Used if the screen dimensions change i.e. if a user adjusts the
		// dimensions of the window
		void reshape(float x1, float y1, float x2, float y2 ) {
			this->screenMin = b2Vec2(x1, y1);
			this->screenMax = b2Vec2(x2, y2);

			setCamera(worldMin, worldMax, screenMin, screenMax, screenMinInWorld, screenMaxInWorld);
		}

		// Pan by a vector
		void pan (b2Vec2 pan) {
			screenMinInWorld +=(pan);
			screenMaxInWorld +=(pan);
			updated = true;
		}

		// Zoom by a vector
		void zoomIn () {
			double x = 0.75;
			zoom ++;

			screenMaxInWorld.x *= x;
			screenMaxInWorld.y *= x;

			screenMinInWorld.x *= x;
			screenMinInWorld.y *= x;

			updated = true;
		}

		void zoomOut () {
			double x = 1.33;
			zoom --;

			screenMinInWorld.x *= x;
			screenMaxInWorld.x *= x;
			screenMinInWorld.y *= x;
			screenMaxInWorld.y *= x;

			updated = true;
		}


		// rotate by a certain angle
		void rotate(float amount) {
			rotation += amount;
			updated = true;
		}
};

#endif /* CAMERA_H_ */
