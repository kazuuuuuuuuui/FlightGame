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

		virtual void Draw() {};
		virtual void Update() = 0;
		bool CheckIsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true)
		{};

		virtual ~GameObject() {};
	};

}

#endif