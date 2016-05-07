#ifndef _OKA_MANAGER_H_
#define _OKA_MANAGER_H_

#include<map>
#include<string>
#include"../GameObject/GameObject.h"

namespace oka
{
	//----------------------------------------------
	//ゲームのオブジェクトを管理するマネージャクラス

	class GameManager
	{
	public:
		std::map<std::string,GameObject*>m_gameObject;

		void Updata();
		void AddGameObject(std::string _str,GameObject *_object);
		void CheckGameObject();

		static GameManager* GetInstance();
		static void Destroy();

	private:
		static GameManager* m_instance;

		GameManager()
		{
			//debug
			printf("ゲームマネージャーが生成されました\n");
			printf("\n");

		}

		~GameManager()
		{
			//debug
			printf("ゲームマネージャーが削除されました\n");
			printf("\n");
		}

	};
}

#endif