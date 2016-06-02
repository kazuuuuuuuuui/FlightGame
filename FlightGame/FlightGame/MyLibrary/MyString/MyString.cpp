#include<string>
#include"MyString.h"
#include"../../glut.h"

namespace oka
{
	//-------------------------------------
	//

	MyString* MyString::Create(const char *_str,glm::vec2 _pos)
	{
		MyString* str = new MyString(_str, _pos);

		return str;
	}

	//-------------------------------------
	//•`‰æ

	void MyString::Draw()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glDisable(GL_LIGHTING);
			glColor3f(m_color.x, m_color.y, m_color.z);
			glLineWidth(m_lineWidth);

			glPushMatrix();
			{
				glTranslatef(m_pos.x, m_pos.y, 0);
				glRotatef(0, 0.0f, 0.0f, 1.0f);
				glScalef(m_scale.x, m_scale.y, m_scale.z);

				for (unsigned int i = 0; i < strlen(m_string); i++)
				{
					glutStrokeCharacter(GLUT_STROKE_ROMAN, m_string[i]);
				}
			}
			glPopMatrix();
		}
		glPopAttrib();
	}
}