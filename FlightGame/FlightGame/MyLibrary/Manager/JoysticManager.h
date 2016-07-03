#ifndef JOYSTICK_MANAGER_H_
#define JOYSTICK_MANAGER_H_

#include<vector>
#include"../../Singleton/Singleton.h"
#include"../Input/Controller.h"

namespace oka
{
	class JoysticManager : public Singleton<JoysticManager>
	{
	friend class Singleton<JoysticManager>;

	public:
		virtual void Update()override;
		void SetController(Contoroller *_Contoroller);
		Contoroller* GetController(unsigned int _num)const;

		JoysticManager();
		~JoysticManager();

	private:
		static JoysticManager* m_instance;
		std::vector<Contoroller*>m_contoroller;

	};
}

#endif