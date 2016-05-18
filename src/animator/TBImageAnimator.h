#ifndef TBIMAGEANIMATOR_H_
#define TBIMAGEANIMATOR_H_

#include "TBAnimator.h"
#include "../TextureLoader.h"

/**
 * Ta animator menja teksturo objekta in s tem kreira animacijo.
 *
 */

class TBImageAnimator : public TBAnimator {
	public:
		TBImageAnimator();

		void animateSprite(gEntity* e, float ms);

		// pot do datoteke in �tevilo framov
		void createAnimation(const std::string& path, int n);

	private:
		std::string image; 			// pot do lokacije slik
		std::vector<std::vector<float> > coord;  // koordinate tekstur
		int n; 							// �tevilo framov
		int currentFrame; 			// trenuten frame
		uint32 texture;
};

#endif /* TBIMAGEANIMATOR_H_ */
