#include<stdio.h>
#include"SceneManager.h"
#include"JoysticManager.h"
#include"../../Scene/GameMainScene.h"
#include"../../Scene/PauseScene.h"

namespace oka
{
	SceneManager* SceneManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ

	SceneManager::SceneManager()
	{
		m_nowScene = nullptr;
		m_prevScene = nullptr;
		m_sequence.Change(&SceneManager::GameMain);
	}


	//------------------------------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

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
	//タイトルシーン

	//void SceneManager::Title(float _delta)
	//{
	//	if (0.0f == m_sequence.GetTime())
	//	{	
	//		printf("/********************************/\n");
	//
	//		m_nowScene = new TitleScene();
	//		
	//		printf("タイトルシーンが初期化されました\n");
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
	//			printf("コース選択シーンに移ります\n");
	//			printf("\n");

	//			m_prevScene = m_nowScene;
	//			delete m_nowScene;

	//			m_sequence.Change(&SceneManager::CourseSelect);
	//			oka::SoundManager::GetInstance()->Play("modeDecision");
	//		}
	//	}

	//}

	//-------------------------------------
	//ゲームシーン

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{			
			m_nowScene = new GameMainScene();

			printf("ゲームシーンが初期化されました\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//ポーズシーンに移行
		const unsigned int downkey = JoysticManager::GetInstance()->m_contoroller[0]->m_downkey;
		if (downkey & XINPUT_GAMEPAD_START)
		{
			printf("ポーズシーンに移ります\n");
			printf("\n");

			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::Pause);
		}
	}

	//-------------------------------------
	//ゲーム中のポーズシーン
	void SceneManager::Pause(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("/********************************/\n");
			
			m_nowScene = new PauseScene();

			printf("ポーズシーンが初期化されました\n");
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
				printf("ゲームシーンに戻ります\n");
				printf("\n");

				m_prevScene = m_nowScene;
				//delete m_nowScene;

				m_sequence.Change(&SceneManager::GameMain);
			}
			//else if (PauseScene::Mode::backTitle == PauseScene::m_mode)
			//{
			//	printf("タイトルシーンに戻ります\n");
			//	printf("\n");
			//	delete m_nowScene;//ポーズシーン
			//	delete m_prevScene;//ゲームメインシーン
			//	m_sequence.Change(&SceneManager::Title);
			//}
			else if(PauseScene::Selection::Exit == PauseScene::m_nowSelect)
			{
				exit(EXIT_SUCCESS);
			}
		}

	}


}//namespace oka