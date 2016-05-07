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