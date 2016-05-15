#ifndef XFILE_H_
#define XFILE_H_

#include"../GameObject/GameObject.h"

namespace oka
{

	class xFile
	{
	public:
		//頂点数
		unsigned int m_vertices;

		//インデックス数
		unsigned int m_indeces;

		//法線数
		unsigned int m_normals;

		//頂点情報
		std::vector<glm::vec3>m_vertex;

		//インデックス情報
		std::vector<unsigned short>m_index;

		//法線情報
		std::vector<glm::vec3>m_normal;

		//uv情報
		std::vector<glm::vec2>m_tex;

		static xFile* LoadXFile(const char *_xFileName);

	};

}

#endif