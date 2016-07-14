#ifndef _OKA_TIMEMANAGER_H_
#define _OKA_TIMEMANAGER_H_

#include"../../Singleton/Singleton.h"

namespace oka
{
	class TimeManager : public Singleton<TimeManager>
	{
		friend class Singleton<TimeManager>;

	public:
		void Update()override;
		unsigned int GetFlame()const;
		unsigned int GetMilliSecond()const;
		unsigned int GetSecond()const;
		unsigned int GetMinutes()const;
		void MinusTime();

		TimeManager();

	private:
		static TimeManager* m_instance;
		unsigned int m_gameTime;
		unsigned int m_flame;
		unsigned int m_milliSecond;
		unsigned int m_second;
		unsigned int m_minute;
	};
}

#endif