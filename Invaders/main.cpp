#include "Global.h"
#include "Player.h"
#include "Condition.h"
#include "HUD.h"
#include "Enemy.h"
#include "CameraEffect.h"
#include "DrawingControl.h"
#include "Bullet.h"
#include "Wall.h"
#include "Explode.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

using namespace std;

//extern Time time;
extern Texture texture;
extern Explosion explosion;

// Holds all objects to be drawn
vector<Object*> objects;
Player player;
Enemy enemy;
Bullet b1(50);
Bullet b2(-40);
Bullet b3(-40);
Wall wall;

// Updates once during startup
void Start()
{
	// Initialize values and push the objects into the object vector
	texture.Init();
	objects.push_back(&player);
	objects.push_back(&enemy);
	objects.push_back(&b1);
	objects.push_back(&b2);
	objects.push_back(&b3);
	objects.push_back(&wall);
	wall.Init();
	enemy.Init();
}

// Updates once every frame
void Update()
{
	if (Condition::WinControl()) // If won
		Screen::WinScreen();
	else if (Condition::LoseControl()) // If lost
		Screen::LoseScreen();
	else
	{
		for (int i = 0; i < objects.size(); i++) // Updates all objects
			objects[i]->Update();
		explosion.Update(); // Update explosion
	}
	Screen::Update(); // Update screen scripts
}

#pragma region INIT
void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Time::Tick(); // Update timer
	Camera::Update(); // Update camera

	Update();

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, float(width) / float(height), 0.1f, 10000.0f);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Invaders");

	Start();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(Input::keyboard);
	glutKeyboardUpFunc(Input::keyboard_up);

	glutMainLoop();

	return 0;
}
#pragma endregion INIT
