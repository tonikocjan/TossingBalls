#ifndef TBDIALOG_H_
#define TBDIALOG_H_

#include "TBEntity.h"

class TBDialog : public gEntity {
	public:
		TBDialog(int x, int y, int z, int w, int h, uint32 t);

		void Render(double time, Camera* camera) const;
		void Update(double time);
		bool MouseOver(float x, float y);

		void addChild(gEntity* e);
		int  getClickedChild() { return clickedButton; }

	private:
		std::vector<gEntity*> children;
		int clickedButton; // kateri izmed gumbov na tem dialogu je bil pritisnjen
};

#endif /* TBDIALOG_H_ */
