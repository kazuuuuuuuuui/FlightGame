#include"HomingBullet.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../Effect/EffectInfo.h"
#include"../Effect/Smoke.h"
#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^

HomingBullet::HomingBullet(glm::vec3 *_target,glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	//debug
	//printf("�z�[�~���O�e����������܂���\n");
	m_isHoming = true;
	m_target = _target;
	m_originPos = _pos;
	m_transform.m_position = _pos;
	m_transform.m_rotate = _rotate;
	m_speed = _speed;

}

//-------------------------------------
//�f�X�g���N�^

HomingBullet::~HomingBullet()
{
	//debug
	//printf("�e���폜����܂���\n");
}

//-------------------------------------
//�e�̐���

HomingBulletSP HomingBullet::Create(glm::vec3 *_target,glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	HomingBulletSP bullet(new HomingBullet(_target, _pos, _rotate, _speed));

	return bullet;
}

//-------------------------------------
//�`��

void HomingBullet::Draw()
{
	glPushMatrix();
	{
		//�s��K��
		glMultMatrixf((GLfloat*)&m_transform.m_matrix);

		glutWireSphere(0.5, 10, 10);
	}
	glPopMatrix();
}

//-------------------------------------
//�X�V

void HomingBullet::Update()
{	
	if (0 == m_flame % 30)
	{
		m_isHoming = false;
	}

	if (m_isHoming)
	{
		SetHomingSpeed();
	}

	m_transform.m_position += m_speed;

	//�֐����������������H
	if (0 == m_flame % 2)
	{
		EffectInfo info;
		info.basePos = m_transform.m_position;
		info.particleNum = 1;
		info.color = glm::vec3(230.0f / 255.0f, 230.0f / 255.0f, 230.0f / 255.0f);
		SmokeSP smoke = Smoke::Create(info);
		oka::GameManager::GetInstance()->Add("Smoke", smoke);
	}

	//������x�̋������ꂽ��񊈐��ɂ���
	const float distance = 500;
	if (glm::length(m_transform.m_position - m_originPos) >= distance)
	{
		m_isActive = false;
	}

	if (IsGroundOut())
	{
		if (IsIntersectSea())
		{
			m_isActive = false;
		}
	}
	else
	{
		if (IsIntersectGround())
		{
			EffectInfo info;
			info.basePos = m_transform.m_position;
			info.particleNum = 1;
			info.color = glm::vec3(211.0f / 255.0f, 183.0f / 255.0f, 138.0f / 255.0f);

			SmokeSP smoke = Smoke::Create(info);
			oka::GameManager::GetInstance()->Add("Smoke", smoke);

			m_isActive = false;
		}
	}

	//�L�����N�^�[�Ƃ̓����蔻��
	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		const glm::vec3 pos = (*itr)->m_transform.m_position;

		if (IsHit(pos))
		{
			(*itr)->m_isHitAttack = true;
			m_isActive = false;
		}

		itr++;
	}
}

//-------------------------------------
//�e�ƃL�����N�^�[�Ƃ̓����蔻��
//�����Ƃ��ăL�����N�^�[���W��������Ă���

bool HomingBullet::IsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.m_position - _pos;

	//�e�ƃL�����N�^�[�Ƃ̋���
	const float value = 5.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}

//-------------------------------------
//�z�[�~���O���x�̐ݒ�

void HomingBullet::SetHomingSpeed()
{
	glm::vec3 v1 = m_transform.m_myToVec;
	glm::vec3 v2 = *(m_target) - m_transform.m_position;

	glm::vec3 dir = (v2 - v1);
	dir = glm::normalize(dir);
	dir *= 0.5f;

	m_speed += dir;
}
