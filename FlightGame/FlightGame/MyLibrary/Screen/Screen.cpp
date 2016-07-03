#include"Screen.h"
#include"../../glut.h"

namespace oka
{
	Screen* Screen::m_instance = nullptr;

	//-------------------------------------
	//インスタンス生成

	Screen* Screen::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new Screen();
		}

		return m_instance;
	}

	//-------------------------------------
	//画面横幅の設定

	void Screen::SetWidth(const int _width) 
	{
		m_width = _width; 
	}

	//-------------------------------------
	//画面縦幅の設定

	void Screen::SetHeight(const int _height) 
	{
		m_height = _height; 
	}

	//-------------------------------------
	//画面横幅の取得

	int Screen::GetWidth()const
	{
		return m_width;
	};

	//-------------------------------------
	//画面縦幅の取得

	int Screen::GetHeight()const
	{ 
		return m_height; 
	}

	//-------------------------------------
	//ビューポートの設定

	void Screen::SetViewport(const int _x, const int _y, const int _width, const int _height)const
	{
		glViewport(_x, _y, _width, _height);
	}

	//-------------------------------------
	//画面にかけるマスク処理
	//引数としてマスクの色と透明度を持つvec4を受け取る

	void Screen::SetMask(glm::vec4 _color)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			glColor4f(_color.r, _color.g, _color.b, _color.a);

			const int width = oka::Screen::GetInstance()->GetWidth();
			const int height = oka::Screen::GetInstance()->GetHeight();

			glBegin(GL_QUADS);
			{
				glVertex2f(0.0f, 0.0f);
				glVertex2f(width, 0.0f);
				glVertex2f(width, height);
				glVertex2f(0.0f, height);
			}
			glEnd();
		}
		glPopAttrib();
	}
}