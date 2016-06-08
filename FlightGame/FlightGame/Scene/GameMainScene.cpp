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

#include"../Effect/Smoke.h"


#include"../glut.h"


void DrawRadar()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		const float width = (float)oka::Screen::GetInstance()->GetWidth() / 3.0f;
		const float height = (float)oka::Screen::GetInstance()->GetHeight() / 3.0f;

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		const unsigned int texture = oka::ImageManager::GetInstance()->GetHandle("Radar");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		

		glBegin(GL_QUADS);
		{
			glColor4f(1, 1, 1, 0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);
		}
		glEnd();
	}
	glPopAttrib();
}

void DrawDadarPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glColor3f(1, 0, 0);
		glPointSize(10);

		auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
		auto end = oka::CharacterManager::GetInstance()->m_characters.end();

		while (itr != end)
		{	
			if (!(*itr)->IsGroundOut())
			{
				const glm::vec2 pos = (*itr)->m_onRadarPos;

				glBegin(GL_POINTS);
				{
					glVertex2f(pos.x, pos.y);
				}
				glEnd();
			}

			itr++;
		}
	}
	glPopAttrib();
}

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
	oka::ImageManager::GetInstance()->SetHandle("RockOn", oka::LoadImage4f("rockOn.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("FlyTex", oka::LoadImage3f("flyTex.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sky", oka::LoadImage3f("sky.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sea", oka::LoadImage4f("sea.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Radar", oka::LoadImage4f("radar.bmp"));

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
	oka::CharacterManager::GetInstance()->SetPlayer(player);
	oka::CharacterManager::GetInstance()->AddCharacter(player);
	oka::GameManager::GetInstance()->Add("Player", player);
	

	//test
	EnemySP enemy = Enemy::Create(glm::vec3(30.0f, 30.0f, -50.0f));
	oka::CharacterManager::GetInstance()->AddCharacter(enemy);
	oka::GameManager::GetInstance()->Add("Enemy", enemy);
	
	EnemySP enemy2 = Enemy::Create(glm::vec3(80.0f, 30.0f, -80.0f));
	oka::CharacterManager::GetInstance()->AddCharacter(enemy2);
	oka::GameManager::GetInstance()->Add("Enemy", enemy2);

	//
	/*EffectInfo info;
	info.basePos = glm::vec3(0, 30.0f, -50.0f);
	info.particleNum = 10;
	info.color = glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f);
	info.scale = glm::vec3(1, 1, 1);		

	SmokeSP smoke = Smoke::Create(info);
	oka::GameManager::GetInstance()->Add("Smoke", smoke);*/

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glm::vec3 toVec = oka::CharacterManager::GetInstance()->m_player->m_transform.m_myToVec;
	glm::vec3 upVec = oka::CharacterManager::GetInstance()->m_player->m_transform.m_myUpVec;

	//カメラの注視点
	glm::vec3 target = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;

	//カメラの座標
	glm::vec3 pos;
	pos += target - (toVec * 6.0f);
	pos = pos + (upVec * 2.0f);

	//カメラのアップ
	/*static glm::vec3 up = g_camera->m_transform.m_myUpVec;
	up = up + (toVec - up)*0.1f;
	up = glm::normalize(up);*/

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

	//変えたい
	oka::CharacterManager::GetInstance()->m_player->DrawTarget();

	//文字
	const float left = 0.0f;
	const float right = (float)oka::Screen::GetInstance()->GetWidth();
	const float bottom = 0.0f;
	const float top = (float)oka::Screen::GetInstance()->GetHeight();
	
	g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);

	DrawRadar();
	DrawDadarPos();
}
