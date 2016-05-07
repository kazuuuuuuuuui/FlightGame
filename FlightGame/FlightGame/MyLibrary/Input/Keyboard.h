#ifndef _OKA_KEYBOARD_H_
#define _OKA_KEYBOARD_H_

namespace oka
{
	class Keyboard
	{
	private:
		static bool m_nowKeys[256];
		static bool m_lastKeys[256];

	public:
		static void KeyPress(unsigned char _key);
		static void KeyUp(unsigned char _key);
		static void GetPrevStates();
		static bool GetStates(unsigned char _key);

	};
}

#endif