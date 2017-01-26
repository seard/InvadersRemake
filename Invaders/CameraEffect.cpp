#include "Global.h"
#include "CameraEffect.h"
#include <math.h>

float Camera::pX = 0;
float Camera::pY = 0;
float Camera::dX = 0;
float Camera::dY = 0;
float Camera::randA = 0;
float Camera::tmpTime = 0;

void Camera::Shake(float shakeLength)
{
	tmpTime = shakeLength;
}

void Camera::Update()
{
	if (tmpTime > 0)
	{
		tmpTime -= Time::deltaTimeLOCKED();
		randA = tmpTime * 100;

		dX = random(-randA, randA) / 100;
		dY = random(-randA, randA) / 100;
		pX = dX;
		pY = dY;
	}
	gluLookAt(pX, 0, 30 + pY, pX, 0, pY, 0, 1, 0);
}
