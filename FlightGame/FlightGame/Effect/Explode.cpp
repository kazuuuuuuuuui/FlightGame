#include"Explode.h"
#include"../glut.h"

Explode::Explode(glm::vec3 _pos)
{
	m_transform.SetPosition(_pos);
	m_fire = new Fire(_pos);
	m_smoke = new Smoke(_pos);
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
			glMultMatrixf((GLfloat*)&m_matrix);
			m_fire->Draw();
			m_smoke->Draw();
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Explode::Update()
{
	//çsóÒåvéZ
	//m_matrix = glm::mat4(1.0);

	//glm::mat4 translate = glm::translate(m_transform.GetPosition());

	////glm::mat4 rotate = glm::rotate();

	//glm::mat4 scale = glm::scale(m_transform.GetScale());

	//m_matrix = translate *rotate *scale;
}