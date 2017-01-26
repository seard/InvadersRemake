#include "Input.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

#define BUTTON_UP   0
#define BUTTON_DOWN 1
void keyboard(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_DOWN;
}
void keyboard_up(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_UP;
}

int main1()
{
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	return 0;
}