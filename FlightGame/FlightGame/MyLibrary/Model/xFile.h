#ifndef XFILE_H_
#define XFILE_H_

#include"../GameObject/GameObject.h"

namespace oka
{

	class xFile
	{
	public:
		//���_��
		unsigned int m_vertices;

		//�C���f�b�N�X��
		unsigned int m_indeces;

		//�@����
		unsigned int m_normals;

		//���_���
		std::vector<glm::vec3>m_vertex;

		//�C���f�b�N�X���
		std::vector<unsigned short>m_index;

		//�@�����
		std::vector<glm::vec3>m_normal;

		//uv���
		std::vector<glm::vec2>m_tex;

		static xFile* LoadXFile(const char *_xFileName);

	};

}

#endif