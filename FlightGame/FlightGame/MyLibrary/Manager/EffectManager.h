#ifndef OKA_EFFECTMANAGER_H_
#define OKA_EFFECTMANAGER_H_

#include<list>
#include"../../Effect/Effect.h"

namespace oka
{
	class EffectManager
	{
	private:
		static EffectManager* m_instance;

	public:
		std::list<oka::Effect*> m_effects;

		void AddEffects(oka::Effect* _effect);
		void EraseEffect();

		EffectManager() {};
		static EffectManager* GetInstance();
	};

}

#endif
