#include"Smoke.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ
//

Smoke::Smoke(glm::vec3 _basePos, unsigned int _particleNum, glm::vec3 _color)
{
	m_transform.m_position = _basePos;

	for (unsigned int i = 0; i < _particleNum;i++)
	{
		float alpha = 0.5f+((float)rand() / RAND_MAX)*0.5f;
		glm::vec3 pos = _basePos;
		glm::vec3 color = _color;
		glm::vec3 speed;
		speed.x = 0;
		speed.y = (((float)rand() / RAND_MAX)) *0.05f;
		speed.z = 0;
 
		ParticleSP particle(new Particle(alpha, pos, color, speed));
		m_particles.push_back(particle);
	}

}

//-------------------------------------
//デストラクタ

Smoke::~Smoke()
{
	
}

//-------------------------------------
//煙エフェクトの生成
//引数として煙自体の座標と煙を形成する
//戻り値として生成した煙を返す

SmokeSP Smoke::Create(glm::vec3 _basePos, unsigned int _particleNum, glm::vec3 _color)
{
	SmokeSP smoke(new Smoke(_basePos, _particleNum, _color));

	return smoke;
}

//-------------------------------------
//煙の描画

void Smoke::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		static const unsigned int tex = oka::ImageManager::GetInstance()->GetHandle("Smoke");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);

		auto itr = m_particles.begin();
		auto end = m_particles.end();

		while (itr != end)
		{
			(*itr)->Draw();

			itr++;
		}
	}
	glPopAttrib();
}

//-------------------------------------
//煙の更新

void Smoke::Update()
{
	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.005f;

		if ((*itr)->m_alpha <= 0.0f)
		{
			(*itr)->m_isActive = false;
		}

		(*itr)->m_transform.m_scale += (*itr)->m_alpha*0.1f;
		(*itr)->m_transform.m_position = ((*itr)->m_transform.m_position + (*itr)->m_speed*(*itr)->m_alpha);
	}

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