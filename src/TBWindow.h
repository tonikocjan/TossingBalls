#ifndef TBWINDOW_H_
#define TBWINDOW_H_
#include <GLFW/glfw3.h>
#include <string>

class WindowData {
	public:
		WindowData(std::string name, int width, int height) :
			name(name),
			width(width),
			height(height)
		{}

		std::string getName() { return name; }
		int 		getWidth() { return width; }
		int 		getHeight() { return height; }

		void		setSize(int width, int height) {
			this->width = width; this->height = height;
		}
	private:
		std::string name;
		int 		width;
		int 		height;
};

#endif /* TBWINDOW_H_ */
