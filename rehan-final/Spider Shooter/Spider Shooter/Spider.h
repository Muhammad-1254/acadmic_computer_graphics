#include "pixelMap.h"
#pragma once
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw(void)
	{
		glPointSize(2.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable(GL_POINT_SMOOTH);

	}// end draw
private:
	float x, y;
}; // end class Point2

class Spider
{
private:
	enum State { RUNNING1, RUNNING2, DEAD } state;
	RGBApixmap pix[3];
	float pos_X, pos_Y;
	bool invertX = false;
	bool invertY = false;

public:
	enum modeType { RUN, DIE } mode;
	bool is_moving;	// indicate the spider is still alive
	float sspeed;
	float theta;
	float rate_tChange;
	Spider();
	Spider(Point2 pos);
	void setPosition(float x, float y);
	float spider_getX();
	float spider_getY();
	void changePosition(float dx, float dy);
	void render();
	void changeMode(modeType m);
	void run();

};


///////////////////////////SPider///////////////////////////////////////
Spider::Spider()
{

}

Spider::Spider(Point2 pos)
{


	this->pos_X = 0.0;
	this->pos_Y = 0.0;
	this->is_moving = true;
	pix[RUNNING1].readBMPFile("spider.bmp",1);
	pix[RUNNING2].readBMPFile("spider_1.bmp",1);
	pix[DEAD].readBMPFile("mak3.bmp", 1);

	//pix[i].readBMPFile(fname[i],0);
	for (int i = 0; i < 3; i++) {
		pix[i].setChromaKey(192, 192, 192);
	}

}
void Spider::setPosition(float x, float y)
{
	pos_X = x;
	pos_Y = y;
	//sets pos_X to x and pos_Y to y
}
float Spider::spider_getX()
{
	return pos_X;
}
float Spider::spider_getY()
{
	return pos_Y;
}
void Spider::changePosition(float dx, float dy)
{
	if (dx > 0)
	{
		if (invertX) pos_X -= dx;
		else pos_X += dx;
	}
	else {
		if (invertX) pos_X += dx;
		else pos_X -= dx;
		
	}
	if (dy > 0) {
		if (invertY) pos_Y -= dy;
		else pos_Y += dy;
	}
	else {
		if (invertY) pos_Y += dy;
		else pos_Y -= dy;
	}

	/*if (invertX) pos_X -= dx;
	else pos_X += dx;
	
	if (invertY) pos_Y -= dy;
	else pos_Y += dy;*/
	
	/*pos_X += dx;
	pos_Y += dy;*/

	if (pos_Y >= 460) {
		pos_Y -= 15;
		invertY = true;
	}
	if (pos_Y <= 0) {
		pos_Y += 15;
		invertY = false;
	}
	if (pos_X >= 600) {
		invertX = true;
		pos_X -= 15;
	}
	if (pos_X <= 0) {
		invertX = false;
		pos_X += 15;
	}
}
void Spider::render()
{

	switch (mode)
	{
	case DIE:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[2].mDraw();
		break;
	case RUN:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[state].mDraw();
		break;

	}
}

void Spider::changeMode(modeType m) {
	this->mode= m;
}

void Spider::run() {
	switch (state) 
	{
		case RUNNING1:
			this->state = RUNNING2;
			break;
		case RUNNING2:
			this->state = RUNNING1;
			break;
	}
}