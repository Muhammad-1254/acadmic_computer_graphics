#pragma once
#include <gl/freeglut.h>

class Triangle 
{
	public:
		float tX;
		float tY;
		float height;
		float width;
        
		Triangle(float x, float y, float height, float width) {
			this->tX = x;
			this->tY = y;
			this->height = height;
			this->width = width;
		}

		void setPosition(float x, float y)
		{
			this->tX = x;
			this->tY = y;
		}

		void changePosition(float dx, float dy) {
			this->tX += dx;
			this->tY += dy;

			if (this->tX > 640) this->tX = 0;
			if (this->tY > 480) this->tY = 0;
			if (this->tX < 0) this->tX = 640;
			if (this->tY < 0) this->tY = 480;
		}

		void render();
};

void Triangle::render() {
	glBegin(GL_TRIANGLES);
	glVertex2f(this->tX, this->tY);
	glVertex2f(this->tX + this->width / 2, this->tY + this->height);
	glVertex2f(this->tX - this->width / 2, this->tY + this->height);
	glEnd();
};

class RectanglE
{
public:
    float rX;
    float rY;
    float height;
    float width;

    RectanglE(float x, float y, float height, float width) {
        this->rX = x;
        this->rY = y;
        this->height = height;
        this->width = width;
    }

    void setPosition(float x, float y) {
        this->rX = x;
        this->rY = y;
    }

    void changePosition(float dx, float dy) {
        this->rX += dx;
        this->rY += dy;

        if (this->rX > 640) this->rX = 0;
        if (this->rY > 480) this->rY = 0;
        if (this->rX < 0) this->rX = 640;
        if (this->rY < 0) this->rY = 480;
    }

    void render() {
        // Sky Blue
        glBegin(GL_QUADS);
        glVertex2f(this->rX - this->width / 2, this->rY - this->height / 2);
        glVertex2f(this->rX + this->width / 2, this->rY - this->height / 2);
        glVertex2f(this->rX + this->width / 2, this->rY + this->height / 2);
        glVertex2f(this->rX - this->width / 2, this->rY + this->height / 2);
        glEnd();
    }
};


class Circle
{
public:
    float cX;
    float cY;
    float radius;

    Circle(float x, float y, float r) {
        this->cX = x;
        this->cY = y;
        this->radius = r;
    }

    void setPosition(float x, float y) {
        this->cX = x;
        this->cY = y;
    }

    void changePosition(float dx, float dy) {
        this->cX += dx;
        this->cY += dy;

        if (this->cX > 640) this->cX = 0;
        if (this->cY > 480) this->cY = 0;
        if (this->cX < 0) this->cX = 640;
        if (this->cY < 0) this->cY = 480;
    }

    void render() {
        glColor3f(1.0f, 1.0f, 0.0f); // Bright yellow
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(this->cX, this->cY); // Center of the circle
        const int numSegments = 100; // Number of segments to approximate the circle
        for (int i = 0; i <= numSegments; ++i) {
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // Angle
            float x = this->radius * cosf(theta); // X coordinate
            float y = this->radius * sinf(theta); // Y coordinate
            glVertex2f(this->cX + x, this->cY + y); // Vertex
        }
        glEnd();
    }
};
