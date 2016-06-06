#include"Smoke.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ
//

Smoke::Smoke(EffectInfo _info)
{
	m_transform.m_position = _info.basePos;

	for (unsigned int i = 0; i < _info.particleNum;i++)
	{
		float alpha = 0.5f + ((float)rand() / RAND_MAX)*0.5f;
		glm::vec3 pos = _info.basePos;
		glm::vec3 color = _info.color;
		glm::vec3 speed;
		speed.x = ((float)rand() / RAND_MAX - 0.5f)*0.02f;
		speed.y = (((float)rand() / RAND_MAX)) *0.02f;
		speed.z = ((float)rand() / RAND_MAX - 0.5f)*0.02f;
 
		ParticleSP particle(new Particle(alpha, pos, color, speed));
		m_particles.push_back(particle);
	}

}

//-------------------------------------
//煙エフェクトの生成
//引数として煙自体の座標と煙を形成する
//戻り値として生成した煙を返す

SmokeSP Smoke::Create(EffectInfo _info)
{
	SmokeSP smoke(new Smoke(_info));

	return smoke;
}

//-------------------------------------
//煙の描画

void Smoke::Draw()
{
	auto itr = m_particles.begin();
	auto end = m_particles.end();

	for (; itr != end; itr++)
	{
		(*itr)->Draw();
	}
}

//-------------------------------------
//煙の更新

void Smoke::Update()
{
	//パーティクルの更新
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.0005f;

		(*itr)->m_transform.m_scale = (m_transform.m_scale + (*itr)->m_alpha*10.0f);
		(*itr)->m_transform.m_position = ((*itr)->m_transform.m_position + (*itr)->m_speed*(*itr)->m_alpha);
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