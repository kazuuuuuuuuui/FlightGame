#include"GameMainScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Sound/Sound.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"

#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../Feald/Feald.h"
#include"../Character/Player.h"
#include"../Character/Enemy.h"


#include"../glut.h"


//-------------------------------------
//コンストラクタ

GameMainScene::GameMainScene()
{
	printf("ゲームメインシーン生成\n");
	printf("\n");

	//debug
	oka::GameManager::GetInstance()->AddGameObject("Feald", new Feald());
	oka::ImageManager::GetInstance()->SetHandle("FealdTex", oka::LoadImage3f("tex.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("smoke.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("target.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("FlyTex", oka::LoadImage3f("flyTex.bmp"));
	

	//debug
	oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile("Shot.wav"));
	oka::SoundManager::GetInstance()->AddSound("Explode", oka::Sound::LoadWavFile("Explode.wav"));

	oka::ModelManager::GetInstance()->AddModel("Body", oka::Model::LoadXFile("body.x"));
	oka::ModelManager::GetInstance()->AddModel("Propeller", oka::Model::LoadXFile("propeller.x"));

	//キャラクターの登録
	oka::CharacterManager::GetInstance()->AddCharacter(new Player(glm::vec3(0.0f, 0.0f, 0.0f)));
	oka::CharacterManager::GetInstance()->AddCharacter(new Enemy(glm::vec3(0.0f, 0.0f, -20.0f)));

	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		oka::GameManager::GetInstance()->AddGameObject("Character", (*itr));

		itr++;
	}
};


//-------------------------------------
//デストラクタ

GameMainScene::~GameMainScene()
{
	printf("ゲームメインシーン削除\n");
	printf("\n");
};

//-------------------------------------
//

void GameMainScene::Update()
{
	//全オブジェクトの更新
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Update();
	}

	//後で変更
	//oka::BulletManager::GetInstance()->Updata();
	


}

void GameMainScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const float value = 8.0f;//補完係数

	glm::vec3 toVec;
	glm::vec3 upVec;

	const auto begin = oka::CharacterManager::GetInstance()->m_characters.begin();

	toVec = (*begin)->m_transform.m_myToVec;
	upVec = (*begin)->m_transform.m_myUpVec;

	//カメラの注視点
	glm::vec3 target = (*begin)->m_transform.GetPosition();

	//カメラの座標
	glm::vec3 pos = glm::vec3(0, 1, 5);
	pos = target - ( toVec * 5.0f ) ;
	pos = pos + ( upVec * 2.0f ) ;

	//カメラのupベクトル
	/*
	ティーポット -　カメラ
	その上
	
	*/

	glm::vec3 up = upVec;
	//glm::vec3 up = glm::vec3(0, 1, 0);
	
	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	//全オブジェクトの描画
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Draw();
	}
}
