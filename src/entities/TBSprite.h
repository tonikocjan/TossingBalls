#pragma once

#include <string>
#include "TBEntity.h"

class TBSprite : public gEntity {

	public:
		TBSprite(float x, float y, float z, float w, float h, unsigned int image);
		virtual ~TBSprite();

		void Render(double time, Camera* camera) const;
		void Update(double time);
		bool MouseOver(float x, float y);

		float 	getRotation() 	{ return rotation; }
		void 	setRotation(float r)	{ rotation = r; }

	private:
		float rotation;
};

