#include"Screen.h"
#include"../../glut.h"

namespace oka
{
	Screen* Screen::m_instance = nullptr;

	//-----------------
	//インスタンス生成

	Screen* Screen::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new Screen();
		}

		return m_instance;
	}

	//--------------
	//画面横幅の設定

	void Screen::SetWidth(const int _width) 
	{
		m_width = _width; 
	}

	//--------------
	//画面縦幅の設定

	void Screen::SetHeight(const int _height) 
	{
		m_height = _height; 
	}

	//--------------
	//画面横幅の取得

	int Screen::GetWidth()const
	{
		return m_width;
	};

	//--------------
	//画面縦幅の取得

	int Screen::GetHeight()const
	{ 
		return m_height; 
	}

	//-------------------
	//ビューポートの設定

	void Screen::SetViewport(const int _x, const int _y, const int _width, const int _height)const
	{
		glViewport(_x, _y, _width, _height);
	}

}