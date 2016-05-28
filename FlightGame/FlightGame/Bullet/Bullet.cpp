#include"Bullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../glut.h"

Bullet::Bullet()
{
	//debug
	printf("�e����������܂���\n");
}

Bullet::~Bullet()
{
	//debug
	printf("�e���폜����܂���\n");
}

//-------------------------------------
//�e�̐���

Bullet* Bullet::Create(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	Bullet *bullet = new Bullet();
	bullet->m_transform.m_position = _pos;
	bullet->m_transform.m_rotate = _rotate;
	bullet->m_speed = _speed;

	return bullet;
}

//-------------------------------------
//�`��

void Bullet::Draw()
{
	//glPushAttrib(GL_ALL_ATTRIB_BITS);
	//{
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			//�s��K��
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			glutSolidCube(0.5);
			//glutSolidCube(1);

			/*auto v = m_model.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_model.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_model.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));*/

		}
		glPopMatrix();

	//}
	//glPopAttrib();

}

//-------------------------------------
//�X�V

void Bullet::Update()
{
	m_transform.m_position += m_speed;

//debug
glm::vec3 pos = m_transform.m_position;
printf("x:%f,y:%f,z:%f\n", pos.x, pos.y, pos.z);

	//�t�B�[���h���ɂ��邩
	if (IsGroundOut())
	{
//debug
printf("�o�Ă邤����������������������\n");
m_isActive = false;
	}
	else
	{
		if (IsIntersectGround())
		{
			m_isActive = false;
		}
	}

	//�L�����N�^�[�Ƃ̓����蔻��
	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while(itr != end)
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

bool Bullet::IsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.m_position - _pos;

	//�e�ƃL�����N�^�[�Ƃ̋���
	const float value = 2.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}

//-------------------------------------
//�n�`�������ɂ��邩�O�ɂ��邩�̔���

bool Bullet::IsGroundOut()const
{
	//x
	const float width = oka::FealdManager::GetInstance()->m_feald->m_width;
	const float x = m_transform.m_position.x;

	if (x < 0 || width < x)
	{
		return  true;
	}

	//z
	const float height = oka::FealdManager::GetInstance()->m_feald->m_height;
	const float z = m_transform.m_position.z;

	if (z < -height || 0 < z)
	{
		return  true;
	}

	return false;
}

//-------------------------------------
//�e�ƒn�`�Ƃ̐ڐG����

bool Bullet::IsIntersectGround()const
{
	const int x = m_transform.m_position.x;
	const float y = m_transform.m_position.y;
	const int z = -m_transform.m_position.z;

	const int width = oka::FealdManager::GetInstance()->m_feald->m_width;

	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

	//debug
	//printf("h:%f\n", height);

	if (y <= height)
	{
		return true;
	}

	return false;
}