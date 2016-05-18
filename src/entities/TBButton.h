#pragma once

#include <GLFW/glfw3.h>
#include "../SoundLoader.h"
#include "TBEntity.h"

class gButton : public gEntity {
	public:
		gButton();
		gButton(float x, float y, float z, float w, float h, unsigned int texture);

		void Render(double time, Camera* camera) const;
		void Update(double time);
		bool MouseOver(float x, float y);

		void setDelta(float x, float y);

	private:
		float aWidth; // width for animation
		float aHeight; // height for animation
		float speed;
		float deltaX, deltaY;
};

