#ifndef BULLET_H
#define BULLET_H

#include "DrawingControl.h"
#include "Global.h"
#include <stdlib.h>

class Bullet : public Object, public Delay
{
public:
	Bullet(float speedY);
	virtual void Update();
	float fireDelay;
private:
	float mSpeedY;
	
};

bool HitCheck(Bullet b, Object o);

#endif
