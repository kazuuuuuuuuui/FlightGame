#include"PauseScene.h"

#include"../MyLibrary/Camera/Camera.h"

//debug
#include"../StrokeString.h"
#include"../glut.h"

//-------------------------------------
//現在選択されているモード初期化

int PauseScene::m_nowSelect = PauseScene::Selection::BackGameMain;

//-------------------------------------
//選択肢配列初期化

const char* PauseScene::m_selections[SelectionMax] =
{
	"Back Game",
	"Exit"
};


void PauseScene::Update()
{
	

}

void PauseScene::Render()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		

		const float left = 0.0f;
		const float right = 300.f;
		const float bottom = 0.0f;
		const float top = 300.f;
		const float near = 1.0f;
		const float far = -1.0f;

		g_camera->Ortho(left, right, bottom, top, near, far);

		glColor3f(1, 0, 0);
		


	}
	glPopAttrib();
}