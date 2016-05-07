#ifndef _OKA_MODELMANAGER_H_
#define _OKA_MODELMANAGER_H_

#include<stdio.h>
#include<map>
#include<string>
#include"../Model/xFile.h"

namespace oka
{
	class ModelManager 
	{
	public:
		std::map<std::string, xFile*>m_models;

		void Updata() {};
		void AddModel(std::string _str, xFile *_object);

		static ModelManager* GetInstance();
		static void Destroy();

	private:
		static ModelManager* m_instance;

		ModelManager()
		{
			//debug
			printf("モデルマネージャーが生成されました\n");
			printf("\n");

		}

		~ModelManager()
		{
			//debug
			printf("モデルマネージャーが削除されました\n");
			printf("\n");
		}



	};
}

#endif