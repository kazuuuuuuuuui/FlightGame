#include"Bullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^

Bullet::Bullet(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	//debug
	//printf("�e����������܂���\n");

	m_originPos = _pos;
	m_transform.m_position = _pos;
	m_transform.m_rotate = _rotate;
	m_speed = _speed;

}

//-------------------------------------
//�f�X�g���N�^

Bullet::~Bullet()
{
	//debug
	//printf("�e���폜����܂���\n");
}

//-------------------------------------
//�e�̐���

BulletSP Bullet::Create(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	BulletSP bullet(new Bullet(_pos, _rotate, _speed));

	return bullet;
}

//-------------------------------------
//�`��

void Bullet::Draw()
{
	glPushMatrix();
	{
		//�s��K��
		glMultMatrixf((GLfloat*)&m_transform.m_matrix);

		glutSolidCube(0.2);
	}
	glPopMatrix();
}

//-------------------------------------
//�X�V

void Bullet::Update()
{
	m_transform.m_position += m_speed;

	//������x�̋������ꂽ��񊈐��ɂ���
	const float distance = 500;
//printf("%f\n", glm::length(m_transform.m_position - m_originPos));

	if (glm::length(m_transform.m_position - m_originPos) >= distance )
	{
		m_isActive = false;
	}

	//�t�B�[���h���ɂ��邩
	if (!IsGroundOut())
	{
		if (IsIntersectGround())
		{
			//oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position));
			//m_isActive = false;
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
