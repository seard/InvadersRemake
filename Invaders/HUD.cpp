#include "Player.h"
#include "Global.h"
#include "Enemy.h"
#include "HUD.h"
#include "DrawingControl.h"
#include "Wall.h"
#include <glut.h>
#include <string>

using namespace std;

extern Player player;
extern Texture texture;
extern Enemy enemy;
extern Wall wall;

void Screen::Text() // Draws the standard text
{
	drawText("SCORE: ", -31, 24, 2);
	drawText(IntToString(player.ReadScore()), -21, 24, 2);
	drawText("LIVES: ", 7, 24, 2);
}

void Screen::Outline() // Draws the outline
{
	// OUTLINE
	glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(30, 22, 0);
	glVertex3f(30, -26, 0);
	glVertex3f(-30, -26, 0);
	glVertex3f(-30, 22, 0);
	glEnd();
}

void Screen::WinScreen() // Show the winscreen
{
	// Text
	drawText("SCORE: ", -31, 24, 2);
	drawText("LIVES: ", 7, 24, 2);
	drawText(IntToString(player.ReadScore()), 7, -2, 4);
	drawText("YOUR SCORE: ", -31, -2, 4);
	drawText("YOU WON", -31, 4, 4);
	drawText("R TO CONTINUE", -31, -8, 4);

	Time::paused = true;

	if (Input::IsKeyDown('r'))
	{
		wall.Init();
		enemy.Init();
		Time::paused = false;
	}
}

void Screen::LoseScreen() // Show the losescreen
{
	// Text
	drawText("SCORE: ", -31, 24, 2);
	drawText("LIVES: ", 7, 24, 2);
	drawText(IntToString(player.ReadScore()), 7, -2, 4);
	drawText("YOU LOST", -31, 4, 4);
	drawText("YOUR SCORE: ", -31, -2, 4);
	drawText("R TO RETRY", -31, -8, 4);

	Time::paused = true;

	if (Input::IsKeyDown('r'))
	{
		wall.Init();
		enemy.Init();
		player.ResetLife(); // Reset player lives
		player.ResetScore(); // Reset score
		Time::paused = false;
	}
}

void Screen::Update()
{
	Outline();
	Text();
}
