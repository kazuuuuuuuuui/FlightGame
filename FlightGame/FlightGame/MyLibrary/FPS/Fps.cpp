#include<stdio.h>
#include<string>
#include"Fps.h"
#include"../Screen/Screen.h"
#include"../../glut.h"

//-------------------------------------
//fps�v���p�ϐ��Ɗ֐�(debug�p)

int g_GLframe = 0; //�t���[����
int g_GLtimenow = 0;//�o�ߎ���
int g_GLtimebase = 0;//�v���J�n����
float g_fps = 0.0f;

void fps()
{
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

	if (g_GLtimenow - g_GLtimebase > 1000)      //�P�b�ȏソ������fps���o��
	{
		g_fps = g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase);

		g_GLtimebase = g_GLtimenow;//����Ԃ�ݒ�                
		g_GLframe = 0;//�t���[���������Z�b�g
	}

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		char buf[256];

		const int width = oka::Screen::GetInstance()->GetWidth() - oka::Screen::GetInstance()->GetWidth() / 5;

		sprintf_s(buf, "FPS:%.3f", g_fps);

		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(1);

		glPushMatrix();
		{
			glTranslatef(width, 1.0f, 0.0f);
			glScalef(0.2f, 0.2f, 0.2f);

			for (unsigned int i = 0; i < strlen(buf); i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, buf[i]);
			}
		}
		glPopMatrix();
	}
	glPopAttrib();

}