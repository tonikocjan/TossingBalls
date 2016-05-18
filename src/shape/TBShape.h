
#ifndef TBSHAPE_H_
#define TBSHAPE_H_

#include <GLFW/glfw3.h>
#include <math.h>
#include <OpenGL/gl.h>

class TBColor3f {
	public:
		TBColor3f() : r(0), g(0), b(0) {}
		TBColor3f(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
		TBColor3f(const TBColor3f& c) : r(c.r), g(c.g), b(c.b) {}
		TBColor3f operator=(const TBColor3f& c) { return TBColor3f(c.r, c.g, c.b); }

		float r, g, b;

	public:
		static TBColor3f Red;
		static TBColor3f Green;
		static TBColor3f Blue;
		static TBColor3f White;
		static TBColor3f Black;
};

class TBShape {

	public:

		virtual ~TBShape() {}

		TBShape() : width(0), height(0), x(0), y(0), angle(0) {}
		TBShape(int w_, int h_, int x_, int y_) : width(w_), height(h_), x(x_), y(y_), angle(0) {}
		TBShape(const TBShape& other) :
			width(other.getWidth()), height(other.getHeight()), x(other.getX()), y(other.getY()), angle(0) {}

		// every shape must implement this method
		virtual void Render() = 0;

		int getWidth()  const 		{ return width; }
		int getHeight() const  		{ return height; }
		TBColor3f getColor() const 	{ return color; }

		void setWidth(int w) 		{ width = w; }
		void setHeight(int h) 		{ height = h; }

		int getX() const  			{ return x; }
		int getY() const 			{ return y; }

		void setAngle(int a) 		{ angle = a; }
		int getAngle() const 		{ return angle; }

		void setX(int x_) 			{ x = x_; }
		void setY(int y_) 			{ y = y_; }

		void setColor(float r,
				float g, float b) 	{ color.r = r; color.g = g; color.b = b; }
		void setColor(const TBColor3f& c) 	{ color.r = c.r; color.g = c.g; color.b = c.b; }

	protected:
		int width, height; // size
		int x, y; // location
		int angle; // rotation
		TBColor3f color;
};

#endif /* TBSHAPE_H_ */
