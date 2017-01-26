#include "Wall.h"
#include "DrawingControl.h"
#include "Global.h"
#include "Bullet.h"
#include "CameraEffect.h"
#include "Explode.h"

extern Texture texture;
extern Bullet b1, b2, b3;
extern Explosion explosion;

Wall::Wall()
{
	mSize = 1;
	mLives = 4;
	mActive = true;
	mTex = NULL;
	mColor[0] = 0;
	mColor[1] = 1;
	mColor[2] = 0;
}

Wall tmpWall;
void Wall::BuildWall(float pX, float pY)
{
	tmpWall.pX = -2 * tmpWall.mSize + pX;
	tmpWall.pY = 0 + pY;
	wallVector.push_back(tmpWall);

	tmpWall.pX = -2 * tmpWall.mSize + pX;
	tmpWall.pY = 2 * tmpWall.mSize + pY;
	wallVector.push_back(tmpWall);
	tmpWall.pX = 0 + pX;
	tmpWall.pY = 2 * tmpWall.mSize + pY;
	wallVector.push_back(tmpWall);
	tmpWall.pX = 2 * tmpWall.mSize + pX;
	tmpWall.pY = 2 * tmpWall.mSize + pY;
	wallVector.push_back(tmpWall);

	tmpWall.pX = 2 * tmpWall.mSize + pX;
	tmpWall.pY = 0 + pY;
	wallVector.push_back(tmpWall);
}

void Wall::Init()
{
	wallVector.clear();
	BuildWall(-21, -17);
	BuildWall(-7, -17);
	BuildWall(7, -17);
	BuildWall(21, -17);
}

void Wall::WallHitControl(Bullet &b, int index)
{
	if (HitCheck(b, wallVector[index]))
	{
		wallVector[index].mLives -= 1;
		b.SetActive(false);
	}
}

void Wall::Update()
{
	for (int i = 0; i < wallVector.size(); i++)
	{
		WallHitControl(b1, i);
		WallHitControl(b2, i);
		WallHitControl(b3, i);

		if (wallVector[i].mLives <= 0)
		{
			explosion.CreateExplosion(wallVector[i].pX, wallVector[i].pY, random(30, 70), wallVector[i].mColor, 0.3);
			wallVector.erase(wallVector.begin() + i);
			Camera::Shake(0.25);
		}

		wallVector[i].mColor[0] = 0.25 * (4 - wallVector[i].mLives);
		wallVector[i].mColor[1] = wallVector[i].mLives * 0.25;
		wallVector[i].mColor[2] = 0;
		DrawFunc(wallVector[i].pX, wallVector[i].pY, wallVector[i].mSize, wallVector[i].mSize / 2, wallVector[i].mTex, wallVector[i].mColor, wallVector[i].mActive);
	}
}
