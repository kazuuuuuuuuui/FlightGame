#include"Smoke.h"
#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^
//�����̂̔����ʒu�������Ƃ��Ďw�肷��

Smoke::Smoke(glm::vec3 _pos)
{
	m_transform.SetPosition(_pos);

}

//-------------------------------------
//���G�t�F�N�g�̐���
//�����Ƃ��ĉ����̂̍��W�Ɖ����`������
//�p�[�e�B�N���̖������w�肷��
//�߂�l�Ƃ��Đ�����������Ԃ�

Smoke* Smoke::Create(glm::vec3 _pos,const int _particleNum)
{
	Smoke *smoke = new Smoke(_pos);

	for (int i = 0; i < _particleNum; i++)
	{
		glm::vec3 color;
		color.x = 30.0f / 255.0f;
		color.y = 30.0f / 255.0f;
		color.z = 30.0f / 255.0f;

		Particle *particle = new Particle(_pos,color);

		glm::vec3 speed;
		speed.x = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		speed.y = (((float)rand() / RAND_MAX)) *0.05f;
		speed.z = ((float)rand() / RAND_MAX - 0.5f)*0.05f;
		particle->m_speed = speed;
		particle->m_alpha = 0.5f + ((float)rand() / RAND_MAX)*0.5f;//0.5f�`1.0f�̒l���擾
	
		smoke->m_particles.push_back(particle);
	}

	return smoke;
}

//-------------------------------------
//���̕`��

void Smoke::Draw()
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

//-------------------------------------
//���̍X�V

void Smoke::Update()
{
	//�p�[�e�B�N���̍X�V
	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->m_alpha -= 0.0001f;

		//������x�A���t�@�l������������񊈐��ɂ���
		if ((*itr)->m_alpha <= 0.75f)
		{
			(*itr)->m_isActive = false;
		}

		(*itr)->m_transform.SetScale(m_transform.GetScale() + (*itr)->m_alpha*10.0f);
		(*itr)->m_transform.SetPosition((*itr)->m_transform.GetPosition() + (*itr)->m_speed*(*itr)->m_alpha);
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
			delete (*itr);
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