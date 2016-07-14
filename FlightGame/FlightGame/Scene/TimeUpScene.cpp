#include"TimeUpScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/MyString/MyString.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

TimeUpScene::TimeUpScene()
{


};


//-------------------------------------
//デストラクタ

TimeUpScene::~TimeUpScene()
{

};

//-------------------------------------
//

void TimeUpScene::Update()
{

}

void TimeUpScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		const float left = 0.0f;
		const float right = (float)oka::Screen::GetInstance()->GetWidth();
		const float bottom = 0.0f;
		const float top = (float)oka::Screen::GetInstance()->GetHeight();

		g_camera->Ortho(left, right, bottom, top, 1.0f, -1.0f);

		oka::Screen::GetInstance()->SetMask(glm::vec4(0.0f, 0.0f, 0.0f, 0.8f));

		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);
		oka::MyString::Draw("TimeUp!!", glm::vec2(80.0f, 400.0f), glm::vec2(1.5f, 1.5f));
	}
	glPopAttrib();
}