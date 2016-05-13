#include"Explode.h"
#include"../glut.h"

Explode::Explode(glm::vec3 _pos)
{
	m_transform.SetPosition(_pos);

	const unsigned int num = 20;
	m_fire = Fire::Create(_pos);
	m_smoke = Smoke::Create(_pos,num);
}

Explode* Explode::Create(glm::vec3 _pos)
{
	return new Explode(_pos);
}

void Explode::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			m_fire->Draw();
			m_smoke->Draw();
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Explode::Update()
{
	
}