
#ifndef TBANIMATOR_H_
#define TBANIMATOR_H_

#include <string>
#include <vector>
#include "../utility.h"

class gEntity;
class TBAnimator {
	public:
		TBAnimator();
		virtual ~TBAnimator();

		virtual void animateSprite(gEntity* e, float ms) = 0;

		void setLoop(bool l) { loop = l; }
		void setFPS(float framesPerSecond) { FPS = framesPerSecond; msToWait = (1/FPS) * 1000;}
		void stopAnimation() { stop = true; }
		void playAnimation() { stop = false; }

	protected:
		bool  loop;
		bool  stop;
		float FPS;
		float msToWait;
		float msPrevious;
};
#endif /* TBANIMATOR_H_ */
