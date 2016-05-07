#include"Keyboard.h"

namespace oka
{
	bool Keyboard::m_nowKeys[256];
	bool Keyboard::m_lastKeys[256];

	void Keyboard::KeyPress(unsigned char _key)
	{
		m_nowKeys[_key] = true;
	}

	void Keyboard::KeyUp(unsigned char _key)
	{
		m_nowKeys[_key] = false;
	}

	//-------------------------------------
	//1フレーム前のキー状態を取得する

	void Keyboard::GetPrevStates()
	{
		for (int i = 0; i < 256; i++)
		{
			m_lastKeys[i] = m_nowKeys[i];
		}
	}

	bool Keyboard::GetStates(unsigned char _key)
	{
		return (m_nowKeys[_key]);
	}

}