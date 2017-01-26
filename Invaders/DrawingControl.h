#ifndef DRAWINGCONTROL_H
#define DRAWINGCONTROL_H

#include <stdlib.h>
#include <glut.h>

class Object
{
public:
	Object();
	float pX;
	float pY;
	void Draw();
	void SetActive(bool active){ mActive = active; }
	bool ActiveState(){ return mActive; }
	float GetSize(){ return mSize; }
	float* GetColor(){ return mColor; }
	virtual void Init(){}
	virtual void Update(){}
protected:
	bool mActive;
	GLuint* mTex = NULL;
	float mSize;
	float mColor[3];
};

void SimpleDraw(float pX, float pY, float sX, float sY, GLuint tex, float R, float G, float B);
void DrawFunc(float pX, float pY, float sX, float sY, GLuint* tex, float color[3], bool active);

#endif