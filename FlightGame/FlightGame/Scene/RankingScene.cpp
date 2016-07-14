#include"RankingScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/ScoreManager.h"
#include"../MyLibrary/MyString/MyString.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/FPS/Fps.h"

#include"../glut.h"

//-------------------------------------
//コンストラクタ

RankingScene::RankingScene()
{
	oka::ImageManager::GetInstance()->SetHandle("RankingBackGround", oka::LoadImage4f("Image/Ranking.bmp", false));
};


//-------------------------------------
//デストラクタ

RankingScene::~RankingScene()
{
	
};

//-------------------------------------
//更新

void RankingScene::Update()
{
	
}

//-------------------------------------
//描画

void RankingScene::Render()
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
		DrawRanking();

		fps();
	}
	glPopAttrib();
}

//-------------------------------------
//背景の描画

void RankingScene::DrawBackGround()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		const float width = oka::Screen::GetInstance()->GetWidth();
		const float height = oka::Screen::GetInstance()->GetHeight();

		//描画場所
		unsigned int tex;
		tex = oka::ImageManager::GetInstance()->GetHandle("RankingBackGround");

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

//-------------------------------------
//ランキングの描画

void RankingScene::DrawRanking()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		oka::MyString::Draw("Ranking", glm::vec2(220.0f, 749.0f), glm::vec2(1.0f, 1.0f));
		glColor3f(1.0f, 0.0f, 0.0f);
		oka::MyString::Draw("Ranking", glm::vec2(221.0f, 750.0f), glm::vec2(1.0f, 1.0f));


		//変える
		for (unsigned int i = 0; i < 5; i++)
		{
			char buf[256];
			sprintf_s(buf, "%dHits", oka::ScoreManager::GetInstance()->GetRankingScore(i));
			glColor3f(1.0f, 1.0f, 1.0f);
			oka::MyString::Draw(buf, glm::vec2(300.0f, 600.0f-150.0f*i), glm::vec2(0.8f, 0.8f));
		}

	
	}
	glPopAttrib();
}