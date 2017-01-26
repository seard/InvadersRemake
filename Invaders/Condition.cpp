#include "Condition.h"
#include "DrawingControl.h"
#include "Player.h"
#include "Enemy.h"
#include "HUD.h"

extern Texture texture;
extern Player player;
extern Enemy enemy;

bool Condition::IsAlive()
{
	// HP BARS
	for (int i = 0; i < player.ReadLife(); i++)
		DrawFunc(18 + i * 5, 25, 2, 2, &texture.player, new float[]{0, 1, 0}, true);
	// Return true or false depending on life being 0 or more
	return !!((int)player.ReadLife());
}

bool Condition::WinControl() // Checks if won
{
	if (IsAlive() && enemy.AllDead())
		return true;
	return false;
}

bool Condition::LoseControl() // Checks if lost
{
	if (!IsAlive() || enemy.PassedPlayer())
		return true;
	return false;
}