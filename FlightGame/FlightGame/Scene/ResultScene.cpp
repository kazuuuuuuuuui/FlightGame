#include"ResultScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Manager/ScoreManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/StringManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../MyLibrary/FPS/Fps.h"
#include"../glut.h"

//-------------------------------------
//現在選択されているリザルトメニュー初期化

int ResultScene::m_resultMeny = ResultMenu::ReturnTitle;

//-------------------------------------
//リザルトメニューの配列初期化

const char* ResultScene::m_resultMenyName[ResultMenuMax] =
{
	"ReturnTitle",
	"Ranking"
	//"RegisterScore"
};

//-------------------------------------
//コンストラクタ

ResultScene::ResultScene()
{
	oka::ImageManager::GetInstance()->SetHandle("ResultBackGround", oka::LoadImage4f("Image/Result.bmp", false));
	oka::ScoreManager::GetInstance()->ExportRankingScore("Ranking.txt");
};


//-------------------------------------
//デストラクタ

ResultScene::~ResultScene()
{
	
};

//-------------------------------------
//更新

void ResultScene::Update()
{
	if (oka::JoysticManager::GetInstance()->GetController(0)->m_yBottomDown)
	{
		oka::SoundManager::GetInstance()->Play("CursorMove");
		m_resultMeny++;
		m_resultMeny = (m_resultMeny + ResultMenu::ResultMenuMax) % ResultMenu::ResultMenuMax;
	}
	if (oka::JoysticManager::GetInstance()->GetController(0)->m_yTopDown)
	{
		oka::SoundManager::GetInstance()->Play("CursorMove");
		m_resultMeny--;
		m_resultMeny = (m_resultMeny + ResultMenu::ResultMenuMax) % ResultMenu::ResultMenuMax;
	}
}

//-------------------------------------
//描画

void ResultScene::Render()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		const int width = oka::Screen::GetInstance()->GetWidth();
		const int height = oka::Screen::GetInstance()->GetHeight();

		glViewport(0, 0, width, height);

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		const float left = 0.0f;
		const float right = (float)oka::Screen::GetInstance()->GetWidth();
		const float bottom = 0.0f;
		const float top = (float)oka::Screen::GetInstance()->GetHeight();

		g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);

		DrawBackGround();

		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		oka::MyString::Draw("Result", glm::vec2(50.0f, 749.0f), glm::vec2(1.0f, 1.0f));
		glColor3f(1.0f, 0.0f, 0.0f);
		oka::MyString::Draw("Result", glm::vec2(51.0f, 750.0f), glm::vec2(1.0f, 1.0f));

		char score[256];
		sprintf_s(score,"TotalScore:%d",oka::ScoreManager::GetInstance()->GetScore());

		glLineWidth(3.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
		oka::MyString::Draw(score, glm::vec2(501.0f, 199.0f), glm::vec2(0.5f, 0.5f));

		glColor3f(1.0f, 0.0f, 0.0f);
		oka::MyString::Draw(score, glm::vec2(500.0f, 200.0f), glm::vec2(0.5f, 0.5f));

		for (int i = 0; i < ResultMenu::ResultMenuMax; i++)
		{
			if (m_resultMeny == i)
			{
				glColor3f(1, 0, 0);
			}
			else
			{
				glColor3f(128.0f / 256.0f, 128.0f / 256.0f, 128.0f / 256.0f);
			}

			oka::MyString::Draw(m_resultMenyName[i], glm::vec2(50.0f, 250.0f - 100.0f*i), glm::vec2(0.4f, 0.4f));
		}

		fps();
	}
	glPopAttrib();
}

//-------------------------------------
//背景の描画

void ResultScene::DrawBackGround()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		const float width = oka::Screen::GetInstance()->GetWidth();
		const float height = oka::Screen::GetInstance()->GetHeight();

		//描画場所
		unsigned int tex;
		tex = oka::ImageManager::GetInstance()->GetHandle("ResultBackGround");

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);

		glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
		}
		glEnd();

	}
	glPopAttrib();
}