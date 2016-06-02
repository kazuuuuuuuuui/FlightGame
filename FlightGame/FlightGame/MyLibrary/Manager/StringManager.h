#ifndef OKA_STRINGMANAGER_H_
#define OKA_STRINGMANAGER_H_

#include<vector>
#include"../MyString/MyString.h"

namespace oka
{
	//-------------------------------------
	//�Q�[�����Ŏg�p���镶�����Ǘ�����N���X

	class StringManager
	{
	private:
		static StringManager *m_instance;

		StringManager() {}
		~StringManager() {}

	public:
		std::vector<MyString*>m_strings;
		static StringManager* GetInstance();
		void Add(MyString* _str);
	};

}

#endif