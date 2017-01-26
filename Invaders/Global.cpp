#include "Global.h"
#include <stdlib.h>
#include <glut.h>
#include <IL/il.h>
#include <windows.h>
#include <iostream>
#include <sstream>

Texture texture;

double Time::startT = 0;
double Time::endT = 0;
float Time::mDT = 0;
bool Time::paused = false;

void Time::Tick() // Update deltaTime
{
	startT = glutGet(GLUT_ELAPSED_TIME);
	mDT = (startT - endT) / 1000;
	endT = startT;
}

bool Delay::Wait(float waitTime, bool pausable) // simple wait function
{
	if (pausable)
		mTime += Time::deltaTime();
	else
		mTime += Time::deltaTimeLOCKED();
	if (mTime >= waitTime)
	{
		mTime = 0;
		return true;
	}
	return false;
}

bool Delay::Wait1(float waitTime, bool pausable)
{
	if (pausable)
		mTime1 += Time::deltaTime();
	else
		mTime1 += Time::deltaTimeLOCKED();
	if (mTime1 >= waitTime)
	{
		mTime1 = 0;
		return true;
	}
	return false;
}

#pragma region HELPFUNCTIONS
void loadTexture(const char *file, GLuint *image)
{
	ilInit();

	ILuint ilImage;
	ilGenImages(1, &ilImage);
	ilBindImage(ilImage);

	wchar_t fileW[256];
	mbstowcs_s(NULL, fileW, sizeof(fileW) / 2, file, _TRUNCATE);

	if (!ilLoadImage(fileW))
	{
		MessageBox(NULL, fileW, L"Load error", MB_OK);
		exit(0);
	}

	if (!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
	{
		MessageBox(NULL, fileW, L"Convert error", MB_OK);
		exit(0);
	}

	glGenTextures(1, image);
	glBindTexture(GL_TEXTURE_2D, *image);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ilDeleteImages(1, &ilImage);
}

void Texture::Init()
{
	loadTexture("invader1.png", &inv1);
	loadTexture("invader2.png", &inv2);
	loadTexture("invader3.png", &inv3);
	loadTexture("player.png", &player);
}

float random(int min, int max)
{
	return(rand() % (max - min + 1) + min);
}

string IntToString(int a)
{
	ostringstream temp;
	temp << a;
	return temp.str();
}

void drawText(string text, int pX, int pY, int size)
{
	glPushMatrix();
	glDisable(GL_BLEND);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 10000.0);
	gluLookAt(0, 0, 30, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(pX, pY, 0);
	glScalef(0.01 * size, 0.01 * size, 0.01 * size);

	glColor3f(0, 1, 0);
	for (int i = 0; i < text.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	glPopMatrix();
}

unsigned char Input::keyState[255];
void Input::keyboard(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_DOWN;
}
void Input::keyboard_up(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_UP;
}
bool Input::IsKeyDown(char c)
{ 
	if (keyState[(unsigned char)c]) 
		return true; 
	else 
		return false;
}
#pragma endregion HELPFUNCTIONS
