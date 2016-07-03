#include<stdio.h>
#include"SceneManager.h"
#include"CharacterManager.h"
#include"JoysticManager.h"
#include"../MyTime/MyTime.h"
#include"../../Scene/TitleScece.h"
#include"../../Scene/GameScene.h"
#include"../../Scene/TimeUpScene.h"
#include"../../Scene/GameOverScene.h"
#include"../../Scene/ResultScene.h"
#include"../../Scene/EndScene.h"

namespace oka
{
	SceneManager* SceneManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	SceneManager::SceneManager()
	{
		m_nowScene = nullptr;
		m_prevScene = nullptr;
		m_sequence.Change(&SceneManager::Title);
	}


	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	SceneManager* SceneManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new SceneManager();
		}
		return m_instance;
	}

	//-------------------------------------

	void SceneManager::Update()
	{
		m_sequence.Run(this, 1.0f / 60.0f);
	}


	//--------------
	//�^�C�g���V�[��

	void SceneManager::Title(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{		
			m_nowScene = new TitleScene();
			
			printf("�^�C�g���V�[��������������܂���\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetController(0)->m_downkey & XINPUT_GAMEPAD_A)
		{
			switch (TitleScene::m_titleMeny)
			{
			case(TitleMenu::GameStart) :
				
				m_prevScene = m_nowScene;
				//delete m_nowScene;
				m_sequence.Change(&SceneManager::Game);

				break;

			case(TitleMenu::Exit) :

				exit(0);

				break;
			};
		}

	}

	//-------------------------------------
	//�Q�[���V�[��

	void SceneManager::Game(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{			
			m_nowScene = new GameMainScene();

			printf("�Q�[���V�[��������������܂���\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//�Q�[���I�[�o�[�V�[���Ɉڍs
		if (nullptr == oka::CharacterManager::GetInstance()->m_player)
		{
			printf("�Q�[���I�[�o�[�V�[���Ɉڂ�܂�\n");
			printf("\n");

			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::GameOver);
		}

		//�^�C���A�b�v�V�[���Ɉڍs
		if (0 == oka::MyTime::GetInstance()->GetFlame())
		{
			printf("�^�C���A�b�v�V�[���Ɉڂ�܂�\n");
			printf("\n");

			//m_prevScene = m_nowScene;

			//m_sequence.Change(&SceneManager::TimeUp);
		}
	}

	//-------------------------------------
	//�^�C���A�b�v�V�[��

	void SceneManager::TimeUp(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new TimeUpScene();

			printf("�^�C���A�b�v�V�[��������������܂���\n");
			printf("\n");
		}

		m_prevScene->Render();

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetController(0)->m_downkey & XINPUT_GAMEPAD_START)
		{
			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::Result);
		}
	}


	//-------------------------------------
	//�Q�[���I�[�o�[�V�[��

	void SceneManager::GameOver(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new GameOverScene();

			printf("�Q�[���I�[�o�[�V�[��������������܂���\n");
			printf("\n");
		}

		m_prevScene->Render();
		m_prevScene->Update();

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetController(0)->m_downkey & XINPUT_GAMEPAD_START)
		{
			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::End);
		}
	}


	//-------------------------------------
	//���U���g�V�[��

	void SceneManager::Result(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new ResultScene();
		}

		if (oka::JoysticManager::GetInstance()->GetController(0)->m_downkey & XINPUT_GAMEPAD_START)
		{
			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::End);
		}

		m_nowScene->Update();
		m_nowScene->Render();

	}

	//-------------------------------------
	//�G���h�V�[��

	void SceneManager::End(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new EndScene();

			delete m_prevScene;
			delete m_nowScene;

			m_sequence.Change(&SceneManager::Title);
		}
	}


}//namespace oka