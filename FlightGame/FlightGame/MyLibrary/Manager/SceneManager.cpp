#include<stdio.h>
#include"SceneManager.h"
#include"GameManager.h"
#include"ImageManager.h"
#include"../Sound/Sound.h"
#include"SoundManager.h"
#include"EffectManager.h"
#include"../../Scene/GameMainScene.h"

//debug

#include"CharacterManager.h"
#include"../Image/BmpImage.h"
#include"../../Feald/Feald.h"
#include"../../Character/Player.h"
#include"../../Character/Enemy.h"
#include"ModelManager.h"
#include"../Model/xFile.h"

#include"../../Effect/Smoke.h"
#include"../../Effect/Fire.h"

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

	////-------------------------------------
	////コース選択シーン

	//void SceneManager::CourseSelect(float _delta)
	//{
	//	if (0.0f == m_sequence.GetTime())
	//	{
	//		printf("/********************************/\n");
	//		
	//		m_nowScene = new CourseSelectScene();
	//
	//		printf("コース選択シーンが初期化されました\n");
	//		printf("\n");

	//	}

	//	m_nowScene->Update();
	//	m_nowScene->Render();

	//	//ゲームシーンに移行
	//	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
	//	{
	//		printf("\n");
	//		printf("ゲームシーンに移ります\n");
	//		printf("\n");

	//		m_prevScene = m_nowScene;
	//		delete m_nowScene;

	//		m_sequence.Change(&SceneManager::GameMain);
	//	}
	//	else if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_B)
	//	{
	//		printf("タイトルシーンに戻ります\n");
	//		printf("\n");

	//		m_prevScene = m_nowScene;
	//		delete m_nowScene;

	//		m_sequence.Change(&SceneManager::Title);
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

			//debug
			oka::GameManager::GetInstance()->AddGameObject("Feald", new Feald());
			oka::ImageManager::GetInstance()->SetHandle("FealdTex", oka::LoadImage3f("tex.bmp"));
			oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("smoke.bmp"));
			oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("target.bmp"));
			oka::CharacterManager::GetInstance()->AddCharacter(new Player(glm::vec3(0.0f, 5.0f, 0.0f)));
			oka::CharacterManager::GetInstance()->AddCharacter(new Enemy(glm::vec3(0.0f, 5.0f, -100.0f)));
			oka::GameManager::GetInstance()->AddGameObject("Character", oka::CharacterManager::GetInstance()->m_characters[0]);
			oka::GameManager::GetInstance()->AddGameObject("Enemy", oka::CharacterManager::GetInstance()->m_characters[1]);

			//debug
			glm::vec3 pos = glm::vec3(0.0f, 0.0f, -50.0f);
			int particleNum = 35;
			oka::EffectManager::GetInstance()->AddEffects(Smoke::Create(pos, particleNum));
			oka::EffectManager::GetInstance()->AddEffects(Fire::Create(glm::vec3(pos)));


			//oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile());

		}

		m_nowScene->Update();
		m_nowScene->Render();

		////ポーズシーンに移行
		//if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
		//{
		//	printf("ポーズシーンに移ります\n");
		//	printf("\n");

		//	m_prevScene = m_nowScene;

		//	m_sequence.Change(&SceneManager::Pause);
		//}
	}

	//-------------------------------------
	//ゲーム中のポーズシーン
	//void SceneManager::Pause(float _delta)
	//{
	//	if (0.0f == m_sequence.GetTime())
	//	{
	//		printf("/********************************/\n");
	//		
	//		m_nowScene = new PauseScene();

	//		printf("ポーズシーンが初期化されました\n");
	//		printf("\n");

	//	}

	//	m_prevScene->Render();

	//	m_nowScene->Update();
	//	m_nowScene->Render();

	//	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
	//	{
	//		if (PauseScene::Mode::backGame == PauseScene::m_mode)
	//		{
	//			printf("ゲームシーンに戻ります\n");
	//			printf("\n");

	//			m_prevScene = m_nowScene;
	//			delete m_nowScene;

	//			m_sequence.Change(&SceneManager::GameMain);
	//		}
	//		else if (PauseScene::Mode::backTitle == PauseScene::m_mode)
	//		{
	//			printf("タイトルシーンに戻ります\n");
	//			printf("\n");

	//			delete m_nowScene;//ポーズシーン
	//			delete m_prevScene;//ゲームメインシーン

	//			m_sequence.Change(&SceneManager::Title);
	//		}
	//		else if(PauseScene::Mode::backCourseSelect == PauseScene::m_mode)
	//		{
	//			printf("コース選択シーンに戻ります\n");
	//			printf("\n");

	//			delete m_nowScene;//ポーズシーン
	//			delete m_prevScene;//ゲームメインシーン

	//			m_sequence.Change(&SceneManager::CourseSelect);

	//		}
	//		else if(PauseScene::Mode::exit == PauseScene::m_mode)
	//		{
	//			exit(EXIT_SUCCESS);
	//		}
	//	}

	//}


}//namespace oka