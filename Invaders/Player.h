#ifndef PLAYER_H
#define PLAYER_H

#include "DrawingControl.h"
#include "Global.h"
#include "Bullet.h"
#include <stdlib.h>

using namespace std;

class Player : public Object, public Delay
{
public:
	Player();
	virtual void Update();
	virtual void Init(int life){ pX = pY = 0; mLife = life; }
	void AddScore(int score){ mScore += score; }
	int ReadLife(){ return mLife; }
	int ReadScore(){ return mScore; }
	void ResetLife(){ mLife = 3; }
	void ResetScore(){ mScore = 0; }
private:
	void Damage(Bullet* b);
	int mScore;
	int mLife;
};

#endif