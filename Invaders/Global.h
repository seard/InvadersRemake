#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <glut.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Delay
{
public:
	bool Wait(float waitTime, bool pausable);
	bool Wait1(float waitTime, bool pausable);
private:
	float mTime;
	float mTime1;
};

struct Time
{
public:
	static float deltaTime(){ if (paused)return 0; else return mDT; };
	static float deltaTimeLOCKED(){ return mDT; };
	static bool paused;
	static void Tick();
private:
	static float mDT;
	static double startT;
	static double endT;
};

struct Texture
{
public:
	void Init();
	GLuint inv1;
	GLuint inv2;
	GLuint inv3;
	GLuint player;
};

#define BUTTON_UP   0
#define BUTTON_DOWN 1
class Input
{
public:
	static void keyboard(unsigned char key, int x, int y);
	static void keyboard_up(unsigned char key, int x, int y);
	static bool IsKeyDown(char c);
private:
	static unsigned char keyState[255]; // 32 = spacebar;
};

float random(int min, int max);
string IntToString(int a);
void drawText(string text, int pX, int pY, int size);
void loadTexture(const char *file, GLuint *image);

#endif
