#ifndef _OKA_MANAGER_H_
#define _OKA_MANAGER_H_

#include<map>
#include<string>
#include"../GameObject/GameObject.h"
#include"../../Singleton/Singleton.h"

namespace oka
{
	//----------------------------------------------
	//ゲームのオブジェクトを管理するマネージャクラス

	class GameManager : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>;

	public:
		std::multimap<std::string, GameObjectSP>m_gameObjects;

		virtual void Update()override;
		void Add(std::string _str, GameObjectSP _object);
		void CheckGameObject();

	private:
		static GameManager* m_instance;

		GameManager();
		~GameManager();

	};
}

#endif