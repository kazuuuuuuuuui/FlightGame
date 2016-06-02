#include"StringManager.h"

namespace oka
{
	StringManager* StringManager::m_instance = nullptr;

	StringManager* StringManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new StringManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//’Ç‰Á

	void StringManager::Add(MyString* _str)
	{
		m_strings.push_back(_str);
	}

}