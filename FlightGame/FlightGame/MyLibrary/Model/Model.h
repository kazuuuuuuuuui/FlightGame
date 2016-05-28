#ifndef OKA_MODEL_H_
#define OKA_MODEL_H_

#include"../GameObject/GameObject.h"

namespace oka
{
	class Model
	{
	public:
		//頂点数
		unsigned int m_vertexNum;

		//インデックス数
		unsigned int m_indexNum;

		//法線数
		unsigned int m_normalNum;

		//uv数
		unsigned int m_texNum;

		//頂点情報
		std::vector<glm::vec3>m_vertex;

		//インデックス情報
		std::vector<unsigned short>m_index;

		//法線情報
		std::vector<glm::vec3>m_normal;

		//uv情報
		std::vector<glm::vec2>m_tex;

		static Model* LoadXFile(const char *_xFileName);

	};

}

#endif