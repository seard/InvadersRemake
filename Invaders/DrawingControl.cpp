#include "Global.h"
#include "DrawingControl.h"

Object::Object() :
pX(0),
pY(0),
mActive(false),
mSize(2){}

void DrawFunc(float pX, float pY, float sX, float sY, GLuint* tex, float color[3], bool active)
{
	if (active)
	{
		if (tex)
		{
			// Set alpha mode for unit
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Set unit texture
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, *tex);
		}
		else
			glDisable(GL_TEXTURE_2D); // Need to deny texture, or it will use the last texture


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Set color
		glColor3f(color[0], color[1], color[2]);

		// Draw unit
		glBegin(GL_QUADS);
		glTexCoord2f(0.99f, 0.01f);
		glVertex3f(sX + pX, sY + pY, 0);
		glTexCoord2f(0.99f, 0.99f);
		glVertex3f(sX + pX, -sY + pY, 0);
		glTexCoord2f(0.01f, 0.99f);
		glVertex3f(-sX + pX, -sY + pY, 0);
		glTexCoord2f(0.01f, 0.01f);
		glVertex3f(-sX + pX, sY + pY, 0);
		glEnd();
	}
}

void Object::Draw()
{
	DrawFunc(pX, pY, mSize, mSize, mTex, mColor, mActive);
}