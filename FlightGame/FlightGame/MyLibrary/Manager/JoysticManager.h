#ifndef _OKA_JOYSTICK_MANAGER_
#define _OKA_JOYSTICK_MANAGER_

#include<vector>
#include"../Input/Controller.h"

namespace oka
{
	class JoysticManager
	{
	private:
		static JoysticManager* m_instance;

		JoysticManager() {};

	public:
		std::vector<Contoroller*>m_contoroller;
		Contoroller GetContoroller(const int _num)const;
		void AddController(Contoroller *_Contoroller);
		unsigned int GetContorollerNumber()const;
		void Update();
		static JoysticManager* GetInstance();
	};

}

#endif