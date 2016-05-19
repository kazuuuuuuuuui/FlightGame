#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include<vector>
#include"Transform.h"
#include"../../glm/vec2.hpp"

//-------------------------------

namespace oka
{
	class GameObject 
	{
	public:
		//���g�̃t���[��
		unsigned int m_flame;

		//�������񊈐����̃t���O
		bool m_isActive;

		//���g�̈ʒu�E��]�E�g��k�����
		Transform m_transform;

		bool CheckIsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true)
		{};

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}

#endif