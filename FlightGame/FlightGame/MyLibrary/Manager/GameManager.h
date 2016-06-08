#ifndef _OKA_MANAGER_H_
#define _OKA_MANAGER_H_

#include<map>
#include<string>
#include"../GameObject/GameObject.h"

namespace oka
{
	//----------------------------------------------
	//�Q�[���̃I�u�W�F�N�g���Ǘ�����}�l�[�W���N���X

	class GameManager
	{
	public:
		//std::multimap<std::string,GameObject*>m_gameObjects;
		std::multimap<std::string, GameObjectSP>m_gameObjects;

		void Updata();
		void Add(std::string _str, GameObjectSP _object);
		//GameObjectSP GetObject(std::string _str);
		void CheckGameObject();

		static GameManager* GetInstance();
		static void Destroy();

	private:
		static GameManager* m_instance;

		GameManager()
		{
			//debug
			printf("�Q�[���}�l�[�W���[����������܂���\n");
			printf("\n");

		}

		~GameManager()
		{
			//debug
			printf("�Q�[���}�l�[�W���[���폜����܂���\n");
			printf("\n");
		}

	};
}

#endif