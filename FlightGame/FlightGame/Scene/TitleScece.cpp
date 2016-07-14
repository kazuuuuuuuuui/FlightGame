#include"TitleScece.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/StringManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/ScoreManager.h"
#include"../MyLibrary/Sound/Sound.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../Feald/Feald.h"
#include"../MyLibrary/Sky/Sky.h"
#include"../MyLibrary/Sea/Sea.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../Character/Player.h"
#include"../Character/Enemy.h"
#include"../MyLibrary/MyString/MyString.h"
#include"../MyLibrary/FPS/Fps.h"
#include"../glut.h"

//-------------------------------------
//現在選択されているタイトルメニュー初期化

int TitleScene::m_titleMeny = TitleMenu::GameStart;

//-------------------------------------
//タイトルメニューの配列初期化

const char* TitleScene::m_titleMenyName[TitleMenuMax] =
{
	"Game Start",
	"Ranking",
	"Exit"
};

//-------------------------------------
//コンストラクタ

TitleScene::TitleScene()
{
	g_camera = new oka::Camera();

	oka::Contoroller *controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->SetController(controller);

	//画像データ
	oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("Image/smoke.bmp", true));
	oka::ImageManager::GetInstance()->SetHandle("Grand", oka::LoadImage3f("Image/grand.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("FlyTex", oka::LoadImage3f("Image/ship.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sky", oka::LoadImage3f("Image/sky.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Sea", oka::LoadImage4f("Image/sea.bmp", false));

	//音データ
	oka::SoundManager::GetInstance()->AddSound("BGM", oka::Sound::LoadWavFile("Sound/BGM.wav"));
	oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile("Sound/Shot.wav"));
	oka::SoundManager::GetInstance()->AddSound("Explode", oka::Sound::LoadWavFile("Sound/Explode.wav"));
	oka::SoundManager::GetInstance()->AddSound("RockOn", oka::Sound::LoadWavFile("Sound/RockOn.wav"));
	oka::SoundManager::GetInstance()->AddSound("HomingBullet", oka::Sound::LoadWavFile("Sound/HomingBullet.wav"));
	oka::SoundManager::GetInstance()->AddSound("CursorMove", oka::Sound::LoadWavFile("Sound/CursorMove.wav"));
	oka::SoundManager::GetInstance()->AddSound("GameStart", oka::Sound::LoadWavFile("Sound/GameStart.wav"));

	//モデルデータ
	oka::ModelManager::GetInstance()->SetModel("Body", oka::Model::LoadXFile("xFile/Flighter.x"));
	oka::ModelManager::GetInstance()->SetModel("Sky", oka::Model::LoadXFile("xFile/Sky.x"));
	oka::ModelManager::GetInstance()->SetModel("Sea", oka::Model::LoadXFile("xFile/Sea.x"));

	//フィールド
	FealdSP feald = Feald::Create();
	oka::GameManager::GetInstance()->Add("Feald", feald);
	oka::FealdManager::GetInstance()->AddFeald(feald);

	//空
	oka::SkySP sky = oka::Sky::Create();
	oka::GameManager::GetInstance()->Add("Sky", sky);

	//海
	oka::GameManager::GetInstance()->Add("Sea", oka::Sea::Create());

	//敵
	const int num = oka::CharacterManager::GetInstance()->m_maxEnemyNum;
	for (int i = 0; i < num; i++)
	{
		EnemySP enemy = Enemy::Create();
		oka::CharacterManager::GetInstance()->AddCharacter(enemy);
		oka::GameManager::GetInstance()->Add("Enemy", enemy);
	}
};

//-------------------------------------
//デストラクタ

TitleScene::~TitleScene()
{
	
};

//-------------------------------------
//更新

void TitleScene::Update()
{
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	while (itr != end)
	{
		itr->second->GameObject::Update();
		itr->second->Update();

		itr++;
	}

	if (oka::JoysticManager::GetInstance()->GetController(0)->m_yBottomDown)
	{
		oka::SoundManager::GetInstance()->Play("CursorMove");
		m_titleMeny++;
		m_titleMeny = (m_titleMeny + TitleMenu::TitleMenuMax) % TitleMenu::TitleMenuMax;
	}
	if (oka::JoysticManager::GetInstance()->GetController(0)->m_yTopDown)
	{
		oka::SoundManager::GetInstance()->Play("CursorMove");
		m_titleMeny--;
		m_titleMeny = (m_titleMeny + TitleMenu::TitleMenuMax) % TitleMenu::TitleMenuMax;
	}
}

//-------------------------------------
//描画

void TitleScene::Render()
{
	const int width = oka::Screen::GetInstance()->GetWidth();
	const int height = oka::Screen::GetInstance()->GetHeight();

	oka::Screen::GetInstance()->SetViewport(0, 0, width, height);

	const float w = oka::FealdManager::GetInstance()->m_feald->GetWidth() / 2.0f;
	const float d = oka::FealdManager::GetInstance()->m_feald->GetDepth() / 2.0f;

	//カメラの座標
	static float rot = 0.0f;
	rot += glm::radians(0.3f);

	float x = sin(rot) * 300.0f;
	float z = -cos(rot) * 300.0f;

	glm::vec3 pos = glm::vec3(x, 100.0f, z);
	g_camera->SetPos(pos);

	//カメラの注視点
	glm::vec3 target = glm::vec3(w, 0.0f, -d);
	g_camera->SetTarget(target);

	//カメラのup
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	g_camera->SetUp(up);
	g_camera->Perspective();
	g_camera->SetViewMatrix();
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

	//UI描画
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		const float left = 0.0f;
		const float right = (float)oka::Screen::GetInstance()->GetWidth();
		const float bottom = 0.0f;
		const float top = (float)oka::Screen::GetInstance()->GetHeight();

		g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);
	
		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);
		oka::MyString::Draw("Flight", glm::vec2(0.0f, 650.0f), glm::vec2(2.0f, 2.0f));

		for (int i = 0; i < TitleMenu::TitleMenuMax; i++)
		{
			if (m_titleMeny == i)
			{
				glColor3f(1, 0, 0);
			}
			else
			{
				glColor3f(128.0f / 256.0f, 128.0f / 256.0f, 128.0f / 256.0f);
			}

			oka::MyString::Draw(m_titleMenyName[i], glm::vec2(500.0f, 300.0f - 100 * i), glm::vec2(0.5f, 0.5f));
		}

		fps();
	}
	glPopAttrib();
}
