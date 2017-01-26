#include "Global.h"
#include "Player.h"
#include "Bullet.h"

extern Texture texture;
extern Bullet b1, b2, b3;
extern Player player;

Player::Player()
{
	pX = 0;
	pY = -23;
	mLife = 3;
	mActive = true;
	mSize = 2;
	mTex = &texture.player;
	mColor[0] = 0; mColor[1] = 1; mColor[2] = 0;
	mScore = 0;
}

void Player::Update()
{
	if (Input::IsKeyDown('a') && pX >= -28)
		pX -= 20 * Time::deltaTime();
	if (Input::IsKeyDown('d') && pX <= 28)
		pX += 20 * Time::deltaTime();
	if (Input::IsKeyDown(32) && !b1.ActiveState())
	{
		b1.SetActive(true);
		b1.pX = pX;
		b1.pY = pY;
		b2.SetActive(true);
	}
	if (player.ReadLife() > 0)
	{
		if (HitCheck(b2, player))
			player.Damage(&b2);
		else if (HitCheck(b3, player))
			player.Damage(&b3);
	}
	Draw();
}

void Player::Damage(Bullet* b)
{
	Time::paused = true;
	if (player.Wait(0.15f, false))
		player.mActive = !player.mActive;
	if (player.Wait1(1, false)) // Pause time before entering
	{
		b->SetActive(false);
		player.mLife -= 1;
		Time::paused = false;
		player.mActive = true;
	}
}
