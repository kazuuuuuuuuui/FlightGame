#include"GameMainScene.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Sound/Sound.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../Feald/Feald.h"
#include"../Character/Player.h"
#include"../Character/Enemy.h"
#include"../MyLibrary/SkyDome/Sky.h"
#include"../MyLibrary/Sea/Sea.h"


#include"../MyLibrary/MyString/MyString.h"

#include"../glut.h"

//-------------------------------------
//コンストラクタ

GameMainScene::GameMainScene()
{
	printf("ゲームメインシーン生成\n");
	printf("\n");

	//debug
	oka::ImageManager::GetInstance()->SetHandle("FealdTex", oka::LoadImage3f("grand.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("smoke.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("target.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("FlyTex", oka::LoadImage3f("flyTex.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sky", oka::LoadImage3f("sky.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sea", oka::LoadImage4f("sea.bmp"));

	//音データ
	oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile("Shot.wav"));
	oka::SoundManager::GetInstance()->AddSound("Explode", oka::Sound::LoadWavFile("Explode.wav"));

	//モデルデータ
	oka::ModelManager::GetInstance()->Add("Body", oka::Model::LoadXFile("body.x"));
	oka::ModelManager::GetInstance()->Add("Propeller", oka::Model::LoadXFile("propeller.x"));
	oka::ModelManager::GetInstance()->Add("Sky", oka::Model::LoadXFile("sky.x"));
	oka::ModelManager::GetInstance()->Add("Sea", oka::Model::LoadXFile("sea.x"));

	//フィールド
	FealdSP feald = Feald::Create();
	oka::GameManager::GetInstance()->Add("Feald", feald);
	oka::FealdManager::GetInstance()->AddFeald(feald);

	//空
	oka::SkySP sky = oka::Sky::Create();
	oka::GameManager::GetInstance()->Add("Sky", sky);

	//海
	oka::GameManager::GetInstance()->Add("Sea", oka::Sea::Create());

	//キャラクターの登録
	PlayerSP player = Player::Create(glm::vec3(0.0f, 30.0f, 0.0f));
	oka::CharacterManager::GetInstance()->AddCharacter(player);
	oka::GameManager::GetInstance()->Add("Player", player);
	
	EnemySP enemy = Enemy::Create(glm::vec3(50.0f, 30.0f, 0.0f));
	oka::CharacterManager::GetInstance()->AddCharacter(enemy);
	oka::GameManager::GetInstance()->Add("Enemy", enemy);
	

	//文字

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

	while(itr != end)
	{
		itr->second->GameObject::Update();
		itr->second->Update();

		itr++;
	}

	/*変えたい*/
	oka::CharacterManager::GetInstance()->Update();
	oka::BulletManager::GetInstance()->Updata();
}

void GameMainScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	const float value = 8.0f;//補完係数

	glm::vec3 toVec;
	glm::vec3 upVec;

	const auto characterTop = oka::CharacterManager::GetInstance()->m_characters.begin();

	toVec = (*characterTop)->m_transform.m_myToVec;
	upVec = (*characterTop)->m_transform.m_myUpVec;

	//カメラの注視点
	glm::vec3 target = (*characterTop)->m_transform.m_position;

	//カメラの座標
	glm::vec3 pos;
	pos = target - ( toVec * 6.0f ) ;
	pos = pos + ( upVec * 2.0f ) ;

	glm::vec3 up = upVec;

	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	float v[] = { 0,100,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	//全オブジェクトの描画
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	while (itr != end)
	{
		itr->second->Draw();

		itr++;
	}


	//文字
	/*const float left = 0.0f;
	const float right = (float)oka::Screen::GetInstance()->GetWidth() * 2.0f;
	const float bottom = 0.0f;
	const float top = (float)oka::Screen::GetInstance()->GetHeight() * 2.0f;

	g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);*/

	
}


/*

1点決めて
ニュートンの万有引力を加速度にする


*/
