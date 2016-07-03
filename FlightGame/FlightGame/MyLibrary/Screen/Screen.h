#ifndef _OKA_SCREEN_H_
#define _OKA_SCREEN_H_

#include"../../glm/glm.hpp"

namespace oka
{
	class Screen
	{
	private:
		static Screen* m_instance;
		int m_width;
		int m_height;

		Screen() :
			m_width(900), m_height(900)
		{};

	public:
		static Screen* GetInstance();
		void SetWidth(const int _width);
		void SetHeight(const int _height);
		int GetWidth()const;
		int GetHeight()const;
		void SetViewport(const int _x, const int _y, const int _width, const int _height)const;
		void SetMask(glm::vec4 _mask);
	};
}

#endif