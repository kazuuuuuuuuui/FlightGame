#include"Fire.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../glut.h"

Fire::Fire(EffectInfo _info)
{
	m_transform.m_position = _info.basePos;

	for (unsigned int i = 0; i < _info.particleNum; i++)
	{
		float alpha = ((float)rand() / RAND_MAX);
		glm::vec3 pos = _info.basePos;
		glm::vec3 color = _info.color;
		glm::vec3 speed;

		speed.x = 0;
		speed.y = (((float)rand() / RAND_MAX)) *0.05f;
		speed.z = 0;

		ParticleSP particle(new Particle(alpha, pos, color, speed));
		m_particles.push_back(particle);
	}
}

FireSP Fire::Create(EffectInfo _info)
{
	FireSP fire(new Fire(_info));

	return fire;
}

void Fire::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		static const unsigned int tex = oka::ImageManager::GetInstance()->GetHandle("Smoke");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);

		auto itr = m_particles.begin();
		auto end = m_particles.end();

		for (; itr != end; itr++)
		{
			(*itr)->Draw();
		}

	}
	glPopAttrib();
}

void Fire::Update()
{
	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.005f;
		//debug
		//printf("%f\n", (*itr)->m_alpha);

		if ((*itr)->m_alpha <= 0.0f)
		{
			(*itr)->m_isActive = false;
		}

		(*itr)->m_transform.m_scale += 0.2f;
		(*itr)->m_transform.m_position += (*itr)->m_speed;
	}



	//後で変更
	auto itr = m_particles.begin();
	while (itr != m_particles.end())
	{
		if ((*itr)->m_isActive)
		{

		}
		else
		{
			itr = m_particles.erase(itr);
			continue;
		}

		itr++;
	}

	//煙非活性
	if (0 == m_particles.size())
	{
		m_isActive = false;
	}
}