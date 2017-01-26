#ifndef CAMERAEFFECT_H
#define CAMERAEFFECT_H

#include "Global.h"
#include <glut.h>

struct Camera
{
public:
	static float pX;
	static float pY;
	static void Shake(float shakeLength);
	static void Update();
private:
	static float dX;
	static float dY;
	static float randA;
	static float tmpTime;
};

#endif