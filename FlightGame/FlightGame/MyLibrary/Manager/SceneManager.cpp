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
	//コンストラクタ

	SceneManager::SceneManager()
	{
		m_nowScene = nullptr;
		m_prevScene = nullptr;
		m_sequence.Change(&SceneManager::Title);
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

	void SceneManager::Title(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{		
			m_nowScene = new TitleScene();
			
			printf("タイトルシーンが初期化されました\n");
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
	//ゲームシーン

	void SceneManager::Game(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{			
			m_nowScene = new GameMainScene();

			printf("ゲームシーンが初期化されました\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//ゲームオーバーシーンに移行
		if (nullptr == oka::CharacterManager::GetInstance()->m_player)
		{
			printf("ゲームオーバーシーンに移ります\n");
			printf("\n");

			m_prevScene = m_nowScene;

			m_sequence.Change(&SceneManager::GameOver);
		}

		//タイムアップシーンに移行
		if (0 == oka::MyTime::GetInstance()->GetFlame())
		{
			printf("タイムアップシーンに移ります\n");
			printf("\n");

			//m_prevScene = m_nowScene;

			//m_sequence.Change(&SceneManager::TimeUp);
		}
	}

	//-------------------------------------
	//タイムアップシーン

	void SceneManager::TimeUp(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new TimeUpScene();

			printf("タイムアップシーンが初期化されました\n");
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
	//ゲームオーバーシーン

	void SceneManager::GameOver(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_nowScene = new GameOverScene();

			printf("ゲームオーバーシーンが初期化されました\n");
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
	//リザルトシーン

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
	//エンドシーン

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