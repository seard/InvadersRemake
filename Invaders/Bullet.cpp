#include "Bullet.h"
#include "DrawingControl.h"
#include "Global.h"
#include "Enemy.h"
#include "CameraEffect.h"
#include "Explode.h"

extern Enemy enemy;
extern Explosion explosion;

Bullet::Bullet(float speedY)
{
	pX = 0;
	pY = 0;
	mSize = 0.3;
	mSpeedY = speedY;
	mActive = false;
	mTex = NULL;
	mColor[0] = 0; mColor[1] = 1; mColor[2] = 0;
	fireDelay = random(0, 5);
}

void Bullet::Update()
{
	pY += mSpeedY * Time::deltaTime();
	if (pY > 21 || pY < -25 || pX > 29 || pX < -29) // If bullet is outside of bounds
	{
		if (mActive)
			explosion.CreateExplosion(pX, pY, random(20, 40), mColor, 1);
		mActive = false;
	}
	Draw();
}

bool HitCheck(Bullet b, Object o)
{
	if (b.ActiveState())
	{
		if (b.pX - b.GetSize() < o.pX + o.GetSize() && b.pX + b.GetSize() > o.pX - o.GetSize() &&
			b.pY - b.GetSize() < o.pY + o.GetSize() && b.pY + b.GetSize() > o.pY - o.GetSize())
			return true;
	}
	return false;
}
