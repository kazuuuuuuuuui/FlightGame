#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include<memory>
#include"Transform.h"
#include"../../glm/vec2.hpp"

//-------------------------------

namespace oka
{
	//GameObject�ւ̃X�}�[�g�|�C���^���`��
	class GameObject;
	typedef std::shared_ptr<GameObject> GameObjectSP;

	class GameObject 
	{
	public:
		//���g�̃t���[��
		unsigned int m_flame;

		//�������񊈐����̃t���O
		bool m_isActive;

		//���g�̈ʒu�E��]�E�g��k�����
		Transform m_transform;

		virtual void Draw() {};
		virtual void Update();
		bool IsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true)
		{};

		virtual ~GameObject() {};
	};

}

#endif