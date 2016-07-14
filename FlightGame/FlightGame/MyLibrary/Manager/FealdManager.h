#ifndef OKA_FEALDMANAGER_H_
#define OKA_FEALDMANAGER_H_

#include"../../Feald/Feald.h"
#include"../../Singleton/Singleton.h"

namespace oka
{
	class FealdManager :public Singleton<FealdManager>
	{
		friend class Singleton<FealdManager>;

	public:
		FealdSP m_feald;

		void AddFeald(FealdSP _feald);
		
		FealdManager();
		~FealdManager();

	private:
		static FealdManager* m_instance;

	};
}

#endif