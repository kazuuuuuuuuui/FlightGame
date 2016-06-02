#ifndef OKA_MYSTRING_H_
#define OKA_MYSTRING_H_

#include"../../glm/glm.hpp"

namespace oka
{
	class MyString
	{
	public:
		unsigned int m_flame;
		bool m_isActive;
		glm::vec2 m_pos;
		float m_rot;
		glm::vec3 m_scale;
		const char *m_string;
		glm::vec3 m_color;
		float m_lineWidth;

		static MyString* Create(const char *_str, glm::vec2 _pos);
		void Draw();
		void Update() {};

		MyString(const char *_string,glm::vec2 _pos):
			m_flame(0),
			m_isActive(true),
			m_pos(_pos),
			m_rot(0.0f),
			m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
			m_string(_string),
			m_color(glm::vec3(0.0f, 0.0f, 0.0f)),
			m_lineWidth(2.0f)
		{}
	};

}

#endif