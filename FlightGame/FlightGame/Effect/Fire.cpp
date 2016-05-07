#include"Fire.h"
#include"../glut.h"

const int Fire::m_particleNum = 30;

Fire::Fire(glm::vec3 _pos)
{
	m_transform.SetPosition(_pos);

	for (int i = 0; i < m_particleNum; i++)
	{
		Particle *particle = new Particle(glm::vec3(1.0f,0.5f,0.25f));

		particle->m_speed.x = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		particle->m_speed.y = (((float)rand() / RAND_MAX)) *0.1f;
		particle->m_speed.z = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		particle->m_alpha = ((float)rand() / RAND_MAX);

		m_particles.push_back(particle);
	}
}

Fire* Fire::Create(glm::vec3 _pos)
{
	return new Fire(_pos);
}

void Fire::Draw()
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

void Fire::Update()
{
	//行列計算
	m_matrix = glm::mat4(1.0);

	glm::mat4 translate = glm::mat4(1.0);
	translate = glm::translate(translate,m_transform.GetPosition());

	glm::mat4 rotateX = glm::mat4(1.0);
	rotateX = glm::rotate(rotateX,m_transform.GetRotation().x,glm::vec3(1,0,0));

	glm::mat4 rotateY = glm::mat4(1.0);
	rotateX = glm::rotate(rotateY, m_transform.GetRotation().y, glm::vec3(0, 1, 0));

	glm::mat4 rotateZ = glm::mat4(1.0);
	rotateX = glm::rotate(rotateZ, m_transform.GetRotation().z, glm::vec3(0, 0, 1));

	glm::mat4 rotate = rotateX*rotateY*rotateZ;

	glm::mat4 scale = glm::mat4(1.0);
	scale = glm::scale(scale, m_transform.GetScale())*glm::scale(scale, glm::vec3(0.8f, 1, 0.8f));

	m_matrix = translate *rotate *scale;

	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.01f;
		(*itr)->m_transform.SetScale(m_transform.GetScale() + 3.0f);
		(*itr)->m_transform.SetPosition((*itr)->m_transform.GetPosition() + (*itr)->m_speed*(*itr)->m_alpha);
	}
}