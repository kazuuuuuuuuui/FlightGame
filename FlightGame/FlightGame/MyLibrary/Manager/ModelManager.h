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
		std::map<std::string, ModelSP>m_models;
		void Add(std::string _str, ModelSP _model);

	private:
		static ModelManager* m_instance;

	};
}

#endif