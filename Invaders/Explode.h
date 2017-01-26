#ifndef EXPLODE_H
#define EXPLODE_H

#include "Global.h"
#include "DrawingControl.h"



class Explosion : public Delay
{
public:
	void CreateExplosion(float pX, float pY, int shrapnelAmount, float color[3], float reductionRate);
	void Update();
	class Shrapnel
	{
	public:
		float pX;
		float pY;
		float dirX;
		float dirY;
		float color[3];
		float size;
		float reductionRate;
	};
private:
	std::vector<Shrapnel> shrapnelVector;
};

#endif
