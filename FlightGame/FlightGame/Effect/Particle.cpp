#include"Particle.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

Particle::Particle(float _alpha, glm::vec3 _pos,glm::vec3 _color, glm::vec3 _speed)
{
	m_alpha = _alpha;
	m_transform.m_position = _pos;
	m_transform.m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
	m_color = _color;
	m_speed = _speed;
}


ParticleSP Particle::Create(float _alpha, glm::vec3 _pos,glm::vec3 _color, glm::vec3 _speed)
{
	ParticleSP particle(new Particle(_alpha, _pos,_color, _speed));

	return particle;
}

void Particle::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			glTranslatef(m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

			//ビルボード回転行列適用
			glMultMatrixf((GLfloat*)&BillboardMatrix);

			glScalef(m_transform.m_scale.x, m_transform.m_scale.y, m_transform.m_scale.z);

			glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 1.f);
				glVertex2f(-0.5f, -0.5f);

				glTexCoord2f(0.f, 0.f);
				glVertex2f(-0.5f, 0.5f);

				glTexCoord2f(1.f, 0.f);
				glVertex2f(0.5f, 0.5f);

				glTexCoord2f(1.f, 1.f);
				glVertex2f(0.5f, -0.5f);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();
}