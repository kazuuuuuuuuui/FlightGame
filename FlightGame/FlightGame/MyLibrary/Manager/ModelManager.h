#ifndef MODELMANAGER_H_
#define MODELMANAGER_H_

#include<stdio.h>
#include<map>
#include<string>
#include"../Model/Model.h"
#include"../../Singleton/Singleton.h"

namespace oka
{
	class ModelManager : public Singleton<ModelManager>
	{
		friend class Singleton<ModelManager>;

	public:
		void SetModel(std::string _str, ModelSP _model);
		ModelSP GetModel(std::string _str)const;

	private:
		static ModelManager* m_instance;
		std::map<std::string, ModelSP>m_models;
	};
}

#endif