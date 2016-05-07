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

		//���_��
		unsigned int m_vertices;

		//�C���f�b�N�X��
		unsigned int m_indeces;

		//���_���
		std::vector<glm::vec3>m_vertex;

		//�C���f�b�N�X���
		std::vector<unsigned short>m_index;

		//�@�����
		std::vector<glm::vec3>m_normal;

		//uv���
		std::vector<glm::vec2>m_tex;

		//���g�̃t���[��
		unsigned int m_flame;

		//�������񊈐����̃t���O
		bool m_isActive;

		//���g�̈ʒu�E��]�E�g��k�����
		Transform m_transform;
		
		//���g�̍s��
		glm::mat4 m_matrix;
		glm::mat4 m_translate;
		glm::mat4 m_rotate;
		glm::mat4 m_scale;


		bool CheckIsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true),
			m_matrix(glm::mat4(1.0)),
			m_translate(glm::mat4(1.0)),
			m_rotate(glm::mat4(1.0)),
			m_scale(glm::mat4(1.0))
		{};

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}

#endif