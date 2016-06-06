#include"Smoke.h"
#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^
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
//���G�t�F�N�g�̐���
//�����Ƃ��ĉ����̂̍��W�Ɖ����`������
//�߂�l�Ƃ��Đ�����������Ԃ�

SmokeSP Smoke::Create(EffectInfo _info)
{
	SmokeSP smoke(new Smoke(_info));

	return smoke;
}

//-------------------------------------
//���̕`��

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
//���̍X�V

void Smoke::Update()
{
	//�p�[�e�B�N���̍X�V
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.0005f;

		(*itr)->m_transform.m_scale = (m_transform.m_scale + (*itr)->m_alpha*10.0f);
		(*itr)->m_transform.m_position = ((*itr)->m_transform.m_position + (*itr)->m_speed*(*itr)->m_alpha);
	}

	//��ŕύX
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

	//���񊈐�
	if (0 == m_particles.size())
	{
		m_isActive = false;
	}
}