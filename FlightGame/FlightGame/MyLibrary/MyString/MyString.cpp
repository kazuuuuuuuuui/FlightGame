#include<string>
#include"MyString.h"
#include"../../glut.h"

namespace oka
{
	
	//-------------------------------------
	//•`‰æ

	void MyString::Draw(const char *_str, glm::vec2 _pos, glm::vec2 _scale)
	{
		glPushMatrix();
		{
			glTranslatef(_pos.x, _pos.y, 0);
			glRotatef(0, 0.0f, 0.0f, 1.0f);
			glScalef(_scale.x, _scale.y, 0.0f);

			for (unsigned int i = 0; i < strlen(_str); i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, _str[i]);
			}
		}
		glPopMatrix();

	}
}