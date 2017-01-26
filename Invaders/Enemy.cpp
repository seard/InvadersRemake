#include "Global.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "DrawingControl.h"
#include "Explode.h"
#include "CameraEffect.h"

extern Texture texture;
extern vector<Object*> objects;
extern Enemy enemy;
extern Player player;
extern Bullet b1, b2, b3;
extern Explosion explosion;

Enemy::Enemy(int enemyType, float posX, float posY) // Enemy constructor, set initial values
{
	ResetSetup();
	pX = posX;
	pY = posY;

	if (enemyType == 1){
		mColor[0] = 1; mColor[1] = 1; mColor[2] = 0;
		mScoreValue = 10;
		mTex = &texture.inv1;
	}
	else if (enemyType == 2){
		mColor[0] = 1; mColor[1] = 0.67; mColor[2] = 0;
		mScoreValue = 20;
		mTex = &texture.inv2;
	}
	else if (enemyType == 3){
		mColor[0] = 1; mColor[1] = 0.33; mColor[2] = 0;
		mScoreValue = 40;
		mTex = &texture.inv3;
	}
	else cout << "Enemytype has to be 1, 2 or 3." << endl;
}

bool Enemy::PassedPlayer()
{
	for (int i = 0; i < enemyVector.size(); i++)
	{
		if (enemyVector[i].pY <= player.pY + 1)
			return true;
	}
	return false;
}

bool Enemy::AllDead()
{
	for (int i = 0; i < enemyVector.size(); i++)
	{
		if (enemyVector[i].mActive)
			return false;
	}
	return true;
}

void Enemy::ResetSetup() // Reset variables
{
	mRow = 0;
	mDirectionX = 1;
	mMovingDown = false;
	mSpeedMultiplier = 1;
	mActive = true;
	mSize = 1.25;
	enemyVector.clear(); // Empty the vector
}

int Enemy::ReturnBottomInvader(int line) // Used to find the invader furthest down in a line
{
	for (int i = 0; i < 5; i++)
	{
		if (enemyVector[line + (i * 11)].mActive)
			return (line + (i * 11));
	}
	return ReturnBottomInvader(random(0, 10)); // If there is no enemy in the line, do a new check
}

void Enemy::Shoot(Bullet &b)
{
	if (!b.ActiveState())
	{
		if (b.Wait(b.fireDelay, true)) // If bullet is not active, wait for random delay until firing next time
		{
			int tmpRand = random(0, 10);
			b.pX = enemyVector[ReturnBottomInvader(tmpRand)].pX;
			b.pY = enemyVector[ReturnBottomInvader(tmpRand)].pY;
			b.SetActive(true);
			b.fireDelay = random(0, 8);
		}
	}
}

void Enemy::Update()
{
	if (Wait(0.15 * mSpeedMultiplier, true))	// Enter once every X seconds
	{
		if (mMovingDown) // Moving down
		for (int i = 0; i < 11; i++) // Loops through all row vector objects
			enemyVector[i + (mRow * 11)].pY += -2;
		else // Moving sideways
		for (int i = 0; i < 11; i++) // Loops through all row vector objects
			enemyVector[i + (mRow * 11)].pX += mDirectionX;

		mRow += 1; // Ticks through the invader rows
		if (mRow >= 5) // If at last row, move back to first row
		{
			if (mMovingDown) // If invaders already moved downwards
			{
				mDirectionX = -mDirectionX; // Change X-direction
				mMovingDown = false; // Stop moving downwards
				if (mSpeedMultiplier > 0.1) // Increase speed when invaders move downwards
					mSpeedMultiplier -= 0.075;
			}
			else
			{
				for (int i = 44; i < enemyVector.size(); i++)
				{
					if (enemyVector[i].mActive && enemyVector[i].pX <= -(29 - enemyVector[i].mSize)) // If hit left edge, move down
						mMovingDown = true;
					else if (enemyVector[98 - i].mActive && enemyVector[98 - i].pX >= (29 - enemyVector[98 - i].mSize)) // If hit right edge, move down
						mMovingDown = true;
				}
			}
			mRow = 0; // Reset back to first row
		}
	}

	for (int i = 0; i < enemyVector.size(); i++) // Drawing the enemies
	{
		if (HitCheck(b1, enemyVector[i]) && enemyVector[i].ActiveState())
		{
			Camera::Shake(0.5);
			explosion.CreateExplosion(enemyVector[i].pX, enemyVector[i].pY, random(40, 80), enemyVector[i].mColor, 0.3);
			player.AddScore(enemyVector[i].mScoreValue);
			enemyVector[i].SetActive(false);
			b1.SetActive(false);
		}
		enemyVector[i].Draw();
	}

	Shoot(b2);
	Shoot(b3);
}

void Enemy::Init()
{
	ResetSetup();

	// Spawns enemycluster
	int spaceX = 4;
	int spaceY = 3;

	float tmpX;
	float tmpY;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			tmpX = spaceX * (j - 5);
			tmpY = spaceY * (i - 3) + 15;
			if (i == 0 || i == 1)
				enemyVector.push_back(Enemy(1, tmpX, tmpY));
			if (i == 2 || i == 3)
				enemyVector.push_back(Enemy(2, tmpX, tmpY));
			if (i == 4)
				enemyVector.push_back(Enemy(3, tmpX, tmpY));
		}
	}
}
