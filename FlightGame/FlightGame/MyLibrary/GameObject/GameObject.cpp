#include"GameObject.h"

namespace oka
{
	//-------------------------------------
	//���g�̎��t���[���̍X�V
	//�OF�`�R�U�O�OF�̊ԂŎ�������

	void GameObject::Update()
	{
		m_flame++;

		m_flame %= (60 * 60);
	}

	//-------------------------------------
	//������Ԃ�Ԃ�

	bool GameObject::IsActive()const
	{
		return m_isActive;
	}
}