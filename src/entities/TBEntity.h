#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include "../Camera.h"

#define TODEGREES 180 / M_PI
#define TORAD M_PI / 180

enum E_BODY_TYPE {
	EBT_undefined,   	 // 0
	EBT_tossingBall,	 // 1
	EBT_enemy,   	  	 // 2
	EBT_sprite,   		 // 3
	EBT_groundObject,    // 4
	EBT_obstacle    	 // 5
};

enum E_SHAPE_TYPE {
	EST_rect,
	EST_circle,
};


#include <GLFW/glfw3.h>
#include <math.h>
#include <OpenGL/gl.h>

class TBAnimator;
class gEntity {
	public:
		gEntity(float x, float y, float z, float w, float h, unsigned int texture);
		virtual ~gEntity();

		virtual void Render(double time, Camera* camera) const = 0;
		virtual void Update(double time) = 0;
		virtual bool MouseOver(float x, float y) = 0;

		void 	setPosition(float x_, float y_) { x = x_; y = y_; }
		void 	setSize(float w_, float h_) { height = h_; width = w_; }

		float 	getX() { return x; }
		float 	getY() { return y; }

		float 	getWidth() { return width; }
		float 	getHeight() { return height; }

		uint32 	getTexture() { return tex; }
		void	setTexture(uint32 t) { tex = t; }
		void 	setTexCoordinates(const std::vector<float>& coord);

		int 	getType() { return bodyType; }

		void 	setAnimator(TBAnimator* a);
		void 	setOpacity(int o) { opacity = o; }

		void 	setVisible(bool b) { visible = b; }
		bool	getVisible() { return visible; }

	protected:

		float 	x; 		// pozicija x
		float 	y; 		// pozicija y
		float	z;

		float 	width; 		// dol�ina
		float 	height; 	// vi�ina
		int 	opacity;	// prosojnost

		uint32 	tex; 		// tekstura
		float 	coords[8]; 	// koordinate teksture

		int 	bodyType; 	// tip telesa (E_BODY_TYPE)

		bool 	visible;

		std::vector<TBAnimator*> animators;
};

#endif /* ENTITY_H_ */
