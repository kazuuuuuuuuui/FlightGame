#include"Smoke.h"
#include"../glut.h"

const int Smoke::m_particleNum = 20;

Smoke::Smoke(glm::vec3 _pos)
{
	m_transform.SetPosition(_pos);

	for (int i = 0; i < m_particleNum; i++)
	{
		glm::vec3 color;
		color.x = 160.0f / 255.0f;
		color.y = 160.0f / 255.0f;
		color.z = 160.0f / 255.0f;

		Particle *particle = new Particle(color);

		particle->m_speed.x = ((float)rand() / RAND_MAX - 0.5f)*0.02f;
		particle->m_speed.y = (0.05f + ((float)rand() / RAND_MAX)*0.5f) *0.05f;
		particle->m_speed.z = ((float)rand() / RAND_MAX - 0.5f)*0.015f;
		particle->m_alpha = ((float)rand() / RAND_MAX);

		m_particles.push_back(particle);
	}
}

Smoke* Smoke::Create(glm::vec3 _pos)
{
	return new Smoke(_pos);
}

void Smoke::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_matrix);

			for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
			{
				(*itr)->Draw();
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Smoke::Update()
{
	//行列計算
	m_matrix = glm::mat4(1.0);

	glm::mat4 translate = glm::mat4(1.0);
	translate = glm::translate(translate, m_transform.GetPosition());

	glm::mat4 rotateX = glm::mat4(1.0);
	rotateX = glm::rotate(rotateX, m_transform.GetRotation().x, glm::vec3(1, 0, 0));

	glm::mat4 rotateY = glm::mat4(1.0);
	rotateX = glm::rotate(rotateY, m_transform.GetRotation().y, glm::vec3(0, 1, 0));

	glm::mat4 rotateZ = glm::mat4(1.0);
	rotateX = glm::rotate(rotateZ, m_transform.GetRotation().z, glm::vec3(0, 0, 1));

	glm::mat4 rotate = rotateX*rotateY*rotateZ;

	glm::mat4 scale = glm::mat4(1.0);
	scale = glm::scale(scale, m_transform.GetScale());

	m_matrix = translate *rotate *scale;

	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.0025f;
		(*itr)->m_transform.SetScale(m_transform.GetScale() + (*itr)->m_alpha*0.01f);
		(*itr)->m_transform.SetPosition((*itr)->m_transform.GetPosition() + (*itr)->m_speed*(*itr)->m_alpha);
	}
}