#ifndef WALL_H
#define WALL_H

#include "DrawingControl.h"
#include "Bullet.h"
#include <vector>

class Wall : public Object
{
public:
	Wall();
	virtual void Update();
	virtual void Init();
private:
	std::vector<Wall> wallVector;
	void WallHitControl(Bullet &b, int index);
	void BuildWall(float pX, float pY);
	int mLives;
};

#endif