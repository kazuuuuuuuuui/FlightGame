#ifndef OKA_MODEL_H_
#define OKA_MODEL_H_

#include"../GameObject/GameObject.h"

namespace oka
{
	class Model
	{
	public:
		//���_��
		unsigned int m_vertexNum;

		//�C���f�b�N�X��
		unsigned int m_indexNum;

		//�@����
		unsigned int m_normalNum;

		//uv��
		unsigned int m_texNum;

		//���_���
		std::vector<glm::vec3>m_vertex;

		//�C���f�b�N�X���
		std::vector<unsigned short>m_index;

		//�@�����
		std::vector<glm::vec3>m_normal;

		//uv���
		std::vector<glm::vec2>m_tex;

		static Model* LoadXFile(const char *_xFileName);

	};

}

#endif