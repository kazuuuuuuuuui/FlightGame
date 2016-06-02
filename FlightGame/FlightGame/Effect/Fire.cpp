#include"Fire.h"
#include"../glut.h"

const int Fire::m_particleNum = 20;

Fire::Fire(glm::vec3 _pos)
{
	m_transform.m_position = _pos;

	for (int i = 0; i < m_particleNum; i++)
	{
		ParticleSP particle(new Particle(glm::vec3(1.0f,0.25f,0.125f)));

		particle->m_speed.x = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		particle->m_speed.y = (((float)rand() / RAND_MAX)) *0.2f;
		particle->m_speed.z = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		particle->m_alpha = ((float)rand() / RAND_MAX);

		m_particles.push_back(particle);
	}
}

FireSP Fire::Create(glm::vec3 _pos)
{
	FireSP fire(new Fire(_pos));

	return fire;
}

void Fire::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

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
	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.01f;
		(*itr)->m_transform.m_scale = (m_transform.m_scale + 3.0f);
		(*itr)->m_transform.m_position = ((*itr)->m_transform.m_position + (*itr)->m_speed*(*itr)->m_alpha);
	}
}