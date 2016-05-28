#include<stdio.h>
#include"SceneManager.h"
#include"JoysticManager.h"
#include"../../Scene/GameMainScene.h"
#include"../../Scene/PauseScene.h"

namespace oka
{
	SceneManager* SceneManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	SceneManager::SceneManager()
	{
		m_nowScene = nullptr;
		m_prevScene = nullptr;
		m_sequence.Change(&SceneManager::GameMain);
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

	//void SceneManager::Title(float _delta)
	//{
	//	if (0.0f == m_sequence.GetTime())
	//	{	
	//		printf("/********************************/\n");
	//
	//		m_nowScene = new TitleScene();
	//		
	//		printf("�^�C�g���V�[��������������܂���\n");
	//		printf("\n");

	//		oka::SoundManager::GetInstance()->Play("TitleBGM");

	//	}

	//	m_nowScene->Update();
	//	m_nowScene->Render();

	//	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
	//	{
	//		if (TitleScene::GameMode::exit == TitleScene::m_gameMode)
	//		{
	//			exit(EXIT_SUCCESS);
	//		}
	//		else
	//		{
	//			printf("�R�[�X�I���V�[���Ɉڂ�܂�\n");
	//			printf("\n");

	//			m_prevScene = m_nowScene;
	//			delete m_nowScene;

	//			m_sequence.Change(&SceneManager::CourseSelect);
	//			oka::SoundManager::GetInstance()->Play("modeDecision");
	//		}
	//	}

	//}

	//-------------------------------------
	//�Q�[���V�[��

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{			
			m_nowScene = new GameMainScene();

			printf("�Q�[���V�[��������������܂���\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//�|�[�Y�V�[���Ɉڍs
		const unsigned int downkey = JoysticManager::GetInstance()->m_contoroller[0]->m_downkey;
		if (downkey & XINPUT_GAMEPAD_START)
		{
			printf("�|�[�Y�V�[���Ɉڂ�܂�\n");
			printf("\n");

			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::Pause);
		}
	}

	//-------------------------------------
	//�Q�[�����̃|�[�Y�V�[��
	void SceneManager::Pause(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("/********************************/\n");
			
			m_nowScene = new PauseScene();

			printf("�|�[�Y�V�[��������������܂���\n");
			printf("\n");

		}

		m_prevScene->Render();

		m_nowScene->Update();
		m_nowScene->Render();

		const unsigned int downkey = JoysticManager::GetInstance()->m_contoroller[0]->m_downkey;
		if (downkey & XINPUT_GAMEPAD_A)
		{
			if (PauseScene::Selection::BackGameMain == PauseScene::m_nowSelect)
			{
				printf("�Q�[���V�[���ɖ߂�܂�\n");
				printf("\n");

				m_prevScene = m_nowScene;
				//delete m_nowScene;

				m_sequence.Change(&SceneManager::GameMain);
			}
			//else if (PauseScene::Mode::backTitle == PauseScene::m_mode)
			//{
			//	printf("�^�C�g���V�[���ɖ߂�܂�\n");
			//	printf("\n");
			//	delete m_nowScene;//�|�[�Y�V�[��
			//	delete m_prevScene;//�Q�[�����C���V�[��
			//	m_sequence.Change(&SceneManager::Title);
			//}
			else if(PauseScene::Selection::Exit == PauseScene::m_nowSelect)
			{
				exit(EXIT_SUCCESS);
			}
		}

	}


}//namespace oka