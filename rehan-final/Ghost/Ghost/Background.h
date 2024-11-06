#pragma once
#include <gl/freeglut.h>
#include "RGBAPixMap.h"

class Background
{
public:

	RGBApixmap bgPix;
	float bg_x, bg_y;
	void render();

	Background(float x, float y) {
		this->bg_x = x;
		this->bg_y = y;
		bgPix.readBMPFile("background.bmp", 1);
		bgPix.setChromaKey(0, 0, 0);
	};
};

void Background::render() {
	glRasterPos2i(this->bg_x, this->bg_y);
	bgPix.mDraw();
}