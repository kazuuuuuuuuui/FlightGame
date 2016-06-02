#ifndef OKA_FEALDMANAGER_H_
#define OKA_FEALDMANAGER_H_

#include"../../Feald/Feald.h"

namespace oka
{
	class FealdManager
	{
	public:
		FealdSP m_feald;

		static FealdManager* GetInstance();
		void AddFeald(FealdSP _feald);
		static void Destroy();

		FealdManager():
			m_feald(nullptr)
		{}

		~FealdManager();

	private:
		static FealdManager* m_instance;

	};
}

#endif