#pragma once
#include <gl/freeglut.h>

class Spider
{
public:

	RGBApixmap sPix;
	float spos_X, spos_y;
	void render();

	Spider(float x, float y) {
		this->spos_X = x;
		this->spos_y = y;
		sPix.readBMPFile("Spider1.bmp", 1);
		sPix.setChromaKey(0, 0, 0);
	};
};

void Spider::render() {
	glRasterPos2i(this->spos_X,this->spos_y);
	sPix.mDraw();
}