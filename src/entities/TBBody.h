#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include "TBEntity.h"
#include "../SOIL.h"

class TBBody : public gEntity {
	public:

		TBBody(
				b2World* context,
				float x, float y, float z,
				float w, float h,
				int bodyType,
				int shapeType,
				unsigned int t1,
				bool dynamic
			);

		virtual void 		Render(double time, Camera* camera) const;
		virtual void 		Update(double time);
		virtual bool 		MouseOver(float x, float y);

		b2Body*& 	getBody() 			{ return body; }
		int			getHitPoints() 		{ return hp; }
		float	 	getAngle()			{ return angle; }
		std::string getOnImpactSound() 	{ return onImpact; }

		void		setAngle(float a) { angle = a; }
		void 	 	setBody(b2Body* b) { body = b; }
		void 	 	setBodyPosition(float x, float y, float a) { setPosition(x, y); body->SetTransform(b2Vec2(x, y), a); }
		void		setOnImpactSound(const std::string& sound) { onImpact = sound; }

		void 		handleCollision(float force);

		virtual 	~TBBody();

	protected:
		// zadeve za box2d
		b2Body*			     body;  //
		b2World*			 world; // kazalec na svet fizike

		// atributi telesa
		std::string 	     onImpact;    // zvok ob trku
		std::string 		 onDestroy;   // zvok ob uni�enju
		std::vector<int>	 textures;	  // telo ima lahko ve� tekstur (za �kodo)
		int					 countTextures; // �tevilo tekstur

		bool				 dynamic;     // ali je to telo dinami�no ali stati�no
		float				 angle; 	  // kot v stopinjah

	public:
		float force;
		int					 hp;		  // '�ivljenje', ko pride na 0 se telo uni�i
		bool	collision;
};

