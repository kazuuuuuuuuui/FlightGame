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

		//頂点数
		unsigned int m_vertices;

		//インデックス数
		unsigned int m_indeces;

		//頂点情報
		std::vector<glm::vec3>m_vertex;

		//インデックス情報
		std::vector<unsigned short>m_index;

		//法線情報
		std::vector<glm::vec3>m_normal;

		//uv情報
		std::vector<glm::vec2>m_tex;

		//自身のフレーム
		unsigned int m_flame;

		//活性か非活性かのフラグ
		bool m_isActive;

		//自身の位置・回転・拡大縮小情報
		Transform m_transform;
		
		//自身の行列
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