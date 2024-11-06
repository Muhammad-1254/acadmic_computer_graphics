#pragma once
#include <gl/glew.h>
#include <gl/gl.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


class Bullet
{
public:

	float is_fired = false;
	float bX, bY;
	float rotationAngle;
	GLuint textureID;
	
	float get_x() {
		return this -> bX;
	}
	
	float get_y() {
		return this->bY;
	}

	void changePos(float dx, float dy) {
		bX += dx;
		bY += dy;
	}

	Bullet(float x, float y) {
		this->bX = x;
		this->bY= y;
	};
};

void Bullet::render() {

}