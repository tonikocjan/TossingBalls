//
//#include "TBText.h"
//#include "../animator/TBAnimator.h"
//
//TBText::TBText(float x, float y, float z, float width, uint32 tex, float angle, const TBColor3f& c, t_font font)
//	: gEntity(x, y, z, width, 0, tex), angle(angle), color(c), font(font) {
//	opacity = 100;
//}
//
//TBText::~TBText() {
//
//}
//
//void TBText::setText(const std::string& t) {
//	text = t;
//}
//
//void TBText::Render(double time, Camera* camera) const {
//	if(!visible) return;
//	glPushMatrix();
//
//		float o = (float)opacity / 100.0;
//
//		glTranslatef(x - (text.length() * width) / 2, y, z);
//		glColor3f(color.r, color.g, color.b);
//
//		dtx_use_font(font, width);
//		dtx_string(text.c_str());
//
//	glPopMatrix();
//}
//
//void TBText::Update(double time) {
//	if(!visible) return;
//	std::vector<TBAnimator*>::const_iterator it = animators.begin();
//	std::vector<TBAnimator*>::const_iterator end = animators.end();
//
//	for (; it != end; ++it) {
//		(*it)->animateSprite(this, time);
//	}
//
//}
//
//bool TBText::MouseOver(float x, float y){
//	return false;
//}
//
