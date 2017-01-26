#ifndef ENEMY_H
#define ENEMY_H

#include "Global.h"
#include "DrawingControl.h"
#include "Bullet.h"
#include <vector>

class Enemy : public Object, public Delay
{
public:
	Enemy(int type = 1, float posX = 0, float posY = 0);
	virtual void Update();
	virtual void Init();
	int ReadValue(){ return mScoreValue; }
	bool PassedPlayer();
	bool AllDead();
	Enemy getVector(int index){ return enemyVector[index]; };
private:
	std::vector<Enemy> enemyVector;
	void Shoot(Bullet &b);
	int ReturnBottomInvader(int line);
	void ResetSetup();
	float mSpeedMultiplier;
	float mDirectionX;
	bool mMovingDown;
	int mRow;
	int mFireDelay1, mFireDelay2;
	float mScoreValue;
};

#endif
