#include "Explode.h"
#include "Global.h"
#include <vector>

Explosion explosion;

void Explosion::CreateExplosion(float pX, float pY, int shrapnelAmount, float c[3], float rR)
{
	Shrapnel tmpShrapnel;

	for (int i = 0; i < shrapnelAmount; i++) // Spawn shrapnel inside of every explosion
	{
		tmpShrapnel.color[0] = c[0];
		tmpShrapnel.color[1] = c[1];
		tmpShrapnel.color[2] = c[2];
		tmpShrapnel.dirX = random(-30, 30);
		tmpShrapnel.dirY = random(-30, 30);
		tmpShrapnel.pX = pX;
		tmpShrapnel.pY = pY;
		tmpShrapnel.size = random(1, 2) / 10;
		tmpShrapnel.reductionRate = rR;
		shrapnelVector.push_back(tmpShrapnel);
	}
}

void Explosion::Update()
{
	for (int i = 0; i < shrapnelVector.size(); i++)
	{
		if (shrapnelVector[i].pX <= -30 || shrapnelVector[i].pX >= 30)
			shrapnelVector[i].dirX = -shrapnelVector[i].dirX;
		if (shrapnelVector[i].pY <= -26 || shrapnelVector[i].pY >= 22)
			shrapnelVector[i].dirY = -shrapnelVector[i].dirY;

		shrapnelVector[i].pX += shrapnelVector[i].dirX * Time::deltaTime();
		shrapnelVector[i].pY += shrapnelVector[i].dirY * Time::deltaTime();

		shrapnelVector[i].size -= shrapnelVector[i].reductionRate * Time::deltaTime();

		DrawFunc(shrapnelVector[i].pX, shrapnelVector[i].pY, shrapnelVector[i].size, shrapnelVector[i].size, NULL, shrapnelVector[i].color, true);

		if (shrapnelVector[i].size <= 0)
			shrapnelVector.erase(shrapnelVector.begin() + i);
	}
}
