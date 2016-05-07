#include"Screen.h"
#include"../../glut.h"

namespace oka
{
	Screen* Screen::m_instance = nullptr;

	//-----------------
	//�C���X�^���X����

	Screen* Screen::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new Screen();
		}

		return m_instance;
	}

	//--------------
	//��ʉ����̐ݒ�

	void Screen::SetWidth(const int _width) 
	{
		m_width = _width; 
	}

	//--------------
	//��ʏc���̐ݒ�

	void Screen::SetHeight(const int _height) 
	{
		m_height = _height; 
	}

	//--------------
	//��ʉ����̎擾

	int Screen::GetWidth()const
	{
		return m_width;
	};

	//--------------
	//��ʏc���̎擾

	int Screen::GetHeight()const
	{ 
		return m_height; 
	}

	//-------------------
	//�r���[�|�[�g�̐ݒ�

	void Screen::SetViewport(const int _x, const int _y, const int _width, const int _height)const
	{
		glViewport(_x, _y, _width, _height);
	}

}