#include"GameOverScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/MyString/MyString.h"
#include"../glm/glm.hpp"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

GameOverScene::GameOverScene()
{
	
};


//-------------------------------------
//デストラクタ

GameOverScene::~GameOverScene()
{
	
};

//-------------------------------------
//

void GameOverScene::Update()
{
	
}

void GameOverScene::Render()
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

		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);
		oka::MyString::Draw("GameOver", glm::vec2(150.0f, 400.0f), glm::vec2(1.0f, 1.0f));

		glPopAttrib();
	}
}
