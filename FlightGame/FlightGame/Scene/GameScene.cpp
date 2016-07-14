#include<random>
#include"GameScene.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/Manager/ScoreManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../Feald/Feald.h"
#include"../Character/Player.h"
#include"../Character/Enemy.h"
#include"../MyLibrary/Sky/Sky.h"
#include"../MyLibrary/Sea/Sea.h"
#include"../MyLibrary/Manager/TimeManager.h"
#include"../MyLibrary/MyString/MyString.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../MyLibrary/FPS/Fps.h"
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

void DrawGameTime()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		char buf[256];
		const int milliSecond = oka::TimeManager::GetInstance()->GetMilliSecond();
		const int second = oka::TimeManager::GetInstance()->GetSecond();
		const int minute = oka::TimeManager::GetInstance()->GetMinutes();

		const int width = oka::Screen::GetInstance()->GetWidth() / 2 - 50;//
		const int height = oka::Screen::GetInstance()->GetHeight() - oka::Screen::GetInstance()->GetHeight() / 8;

		sprintf_s(buf, "Time:%02d''%02d''%03d", minute, second, milliSecond);

		if (second <=10)
		{
			glColor3f(1, 0, 0);
		}
		else
		{
			glColor3f(0, 0, 0);
		}

		glLineWidth(2);

		glPushMatrix();
		{
			glTranslatef(width, height, 0.0f);
			glScalef(0.5f, 0.5f, 0.5f);

			for (unsigned int i = 0; i < strlen(buf); i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, buf[i]);
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
}

//-------------------------------------
//コンストラクタ

GameMainScene::GameMainScene()
{
	oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("Image/target.bmp",false));
	oka::ImageManager::GetInstance()->SetHandle("RockOn", oka::LoadImage4f("Image/rockOn.bmp", false));
	oka::ImageManager::GetInstance()->SetHandle("Radar", oka::LoadImage4f("Image/radar.bmp", false));

	//キャラクターの登録
	PlayerSP player = Player::Create();
	oka::CharacterManager::GetInstance()->SetPlayer(player);
	oka::CharacterManager::GetInstance()->AddCharacter(player);
	oka::GameManager::GetInstance()->Add("Player", player);

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
	
	oka::CharacterManager::GetInstance()->Update();
	oka::BulletManager::GetInstance()->Update();
	oka::TimeManager::GetInstance()->Update();
	
}

void GameMainScene::Render()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		//ビューポートの設定
		const int width = oka::Screen::GetInstance()->GetWidth();
		const int height = oka::Screen::GetInstance()->GetHeight();
		glViewport(0, 0, width, height);

	if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
	{
		//カメラの注視点
		glm::vec3 target = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_position;

		//攻撃を受けている際は注視点を揺らす
		const bool isHit = oka::CharacterManager::GetInstance()->GetPlayer()->GetIsHitAttack();
		if (isHit)
		{
			glm::vec3 shake;

			std::random_device rnd;
			std::mt19937 mt(rnd());
			std::uniform_int_distribution<> x(-1, 1);
			std::uniform_int_distribution<> y(-1, 1);
			std::uniform_int_distribution<> z(-1, 1);

			shake.x = x(mt);
			shake.y = y(mt);
			shake.z = z(mt);

			shake *= 0.02f;

			target += shake;
		}

		g_camera->SetTarget(target);

		const glm::vec3 toVec = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_myToVec;
		const glm::vec3 upVec = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_myUpVec;
	
		//カメラの座標
		glm::vec3 pos;
		pos += upVec*3.0f;
		pos += target - (toVec * 8.0f);
		
		g_camera->SetPos(pos);

		//カメラの上
		glm::vec3 up = g_camera->GetUp();
		up = up + (upVec - up)*0.05f;
		up = glm::normalize(up);
		g_camera->SetUp(up);
	}

		g_camera->Perspective();
		g_camera->SetViewMatrix();
		g_camera->MultViewMatrix();

		/* 光の位置 */
		float light[] = { 0.0f, 1.0f, 0.0f, 0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light);

		//全オブジェクトの描画
		auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
		auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

		while (itr != end)
		{
			itr->second->Draw();

			itr++;
		}

		if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
		{
			oka::CharacterManager::GetInstance()->GetPlayer()->DrawTarget();
		}

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		const float left = 0.0f;
		const float right = (float)oka::Screen::GetInstance()->GetWidth();
		const float bottom = 0.0f;
		const float top = (float)oka::Screen::GetInstance()->GetHeight();

		g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);

		if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
		{			
			bool isHit = oka::CharacterManager::GetInstance()->GetPlayer()->GetIsHitAttack();

			//マスク
			if (isHit)
			{
				oka::Screen::GetInstance()->SetMask(glm::vec4(1.0f, 0.0f, 0.0f, 0.3f));
			}

			oka::ScoreManager::GetInstance()->DrawScore();
			oka::CharacterManager::GetInstance()->GetPlayer()->DrawRadarPos();

			DrawGameTime();
			DrawRadar();

			auto itr = oka::CharacterManager::GetInstance()->GetCharacters()->begin();
			auto end = oka::CharacterManager::GetInstance()->GetCharacters()->end();

			while (itr != end)
			{
				(*itr)->DrawRadarPos();

				itr++;
			}

			//操作方法
			glColor3f(0.0f, 0.0f, 0.0f);
			oka::MyString::Draw("[Lstick]Control", glm::vec2(300.0f, 100.0f), glm::vec2(0.2f, 0.2f));
			oka::MyString::Draw("[LB/RB]Roll", glm::vec2(500.0f, 100.0f), glm::vec2(0.2f, 0.2f));
			oka::MyString::Draw("[A]Accel", glm::vec2(300.0f, 50.0f), glm::vec2(0.2f, 0.2f));
			oka::MyString::Draw("[X]Shot", glm::vec2(400.0f, 50.0f), glm::vec2(0.2f, 0.2f));
			oka::MyString::Draw("[Y]HomingShot", glm::vec2(500.0f, 50.0f), glm::vec2(0.2f, 0.2f));
		}

		fps();

	}
	glPopAttrib();
}
