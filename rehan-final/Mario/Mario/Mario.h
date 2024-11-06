#pragma once
#include <gl/freeglut.h>

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




class Mario
{
public:

	RGBApixmap pix[5]; // make six empty pixmaps, one for each side of cube
	enum State { STANDING, RUNNING1, RUNNING2, RUNNING3, JUMPING, DIE }state;
	enum ModeType { STAY, RUN, R, JUMP, DEAD } mode;
	float pos_X, pos_Y;

	Mario(Point2 pos)

	{
		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();
		pix[0].readBMPFile("MarioStanding.bmp", 1);
		pix[1].readBMPFile("MarioRun1.bmp", 1);
		pix[2].readBMPFile("MarioRun2.bmp", 1);
		pix[3].readBMPFile("MarioRun3.bmp", 1);
		pix[4].readBMPFile("MarioJump.bmp", 1);

		for (int i = 0; i < 5; i++) {
			pix[i].setChromaKey(192, 192, 192);
			this->pos_X = pos.getX();
			this->pos_Y = pos.getY();
		}
	};

	void setPosition(float x, float y)
	{
		this->pos_X = x;
		this->pos_Y = y;
	}
	void render();
	void changeMode(ModeType m);
	void run();
	void die();


	void changePosition(float dx, float dy)
	{
		this->pos_X += dx;
		this->pos_Y += dy;

		if (this->pos_X > 640) this->pos_X = 0;
		if (this->pos_Y > 480) this->pos_Y = 0;
		if (this->pos_X < 0) this->pos_X = 640;
		if (this->pos_Y < 0) this->pos_Y = 480;



		//pix[state].mDraw();
	}

};

void Mario::render()
{
	switch (mode) {
		case STAY:
			glRasterPos2i(this->pos_X, this->pos_Y);
			std::cout << "stay" << std::endl;
			pix[0].mDraw();
			
			break;
		case RUN:
			run();
			glRasterPos2i(this->pos_X, this->pos_Y);
			pix[state].mDraw();
			std::cout << "run" << std::endl;
			break;
		case JUMP:
			glRasterPos2i(this->pos_X, this->pos_Y + 20);
			std::cout << "jump" << std::endl;
			pix[4].mDraw();
			break;
	}

}

void Mario::run()
{
	switch (state) {
		case RUNNING1:
			this->state = RUNNING2;
			break;
		case RUNNING2:
			this->state = RUNNING3;
			break;
		case RUNNING3:
			this->state = RUNNING1;
			break;
		default:
			this->state = RUNNING1;
			break;
	}
}




void Mario::changeMode(ModeType m)
{
	this->mode = m;
	std::cout << this->mode;
}