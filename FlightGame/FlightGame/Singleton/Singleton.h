#ifndef SINGLETON_H_
#define SINGLETON_H_

#include<vector>
#include"BaseSingleton.h"

namespace oka
{
	template< typename T > 
	class Singleton :public BaseSingleton
	{
	public:

		//-------------------------------------
		//インスタンスの生成

		static T* GetInstance()
		{
			if (nullptr == T::m_instance)
			{
				T::m_instance = new T();
			}
			return T::m_instance;
		}

		//-------------------------------------
		//インスタンスの削除

		void Destroy()
		{
			delete T::m_instance;
			T::m_instance = nullptr;
		}

		virtual void Update() {};			
	};
}



#endif