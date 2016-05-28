#include<stdio.h>
#include<time.h>
#include"MyLibrary\Manager\GameManager.h"
#include"MyLibrary\Manager\SceneManager.h"
#include"MyLibrary\Manager\JoysticManager.h"
#include"MyLibrary\Input\Controller.h"

#include"MyLibrary\Sound\Sound.h"

#include"MyLibrary\Input\Keyboard.h"
#include"MyLibrary\Screen\Screen.h"
#include"MyLibrary\Camera\Camera.h"
#include"glut.h"

//-------------------------------------
//fps計測用変数と関数(debug用)

int g_GLframe = 0; //フレーム数
int g_GLtimenow = 0;//経過時間
int g_GLtimebase = 0;//計測開始時間

void fps()
{
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	if (g_GLtimenow - g_GLtimebase > 1000)      //１秒以上たったらfpsを出力
	{
		printf("fps:%f\r", g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase));
		g_GLtimebase = g_GLtimenow;//基準時間を設定                
		g_GLframe = 0;//フレーム数をリセット
	}
}



//debug
GLenum g_mode = GL_FILL;

void keyboard(unsigned char key, int x, int y)
{
	//debug
	if ('l' == key)
	{
		g_mode = GL_LINE;
	}
	else if ('f' == key)
	{
		g_mode = GL_FILL;
	}

	oka::Keyboard::KeyPress(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	//debug
	//printf("keyboardUp: key:%c x:%d y:%d\n", key, x, y);

	oka::Keyboard::KeyUp(key);
}

//----------------------------------------
//更新と描画

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	//debug
	glPolygonMode(GL_FRONT_AND_BACK, g_mode);

	oka::GameManager::GetInstance()->Updata();
	oka::JoysticManager::GetInstance()->Update();
	oka::SceneManager::GetInstance()->Update();

	oka::Keyboard::GetPrevStates();

	glFlush();

}

//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) 
{
	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

//-------------------------------------
//画面の比率が変わった時に描画サイズを再計算するコールバック関数

void reshape(int _width, int _height)
{
	oka::Screen::GetInstance()->SetWidth(_width);
	oka::Screen::GetInstance()->SetHeight(_height);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	const int width = oka::Screen::GetInstance()->GetWidth();
	const int height = oka::Screen::GetInstance()->GetHeight();

	glutInitWindowSize(width, height);
	glutCreateWindow("Flight Game");
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(0, timer, 0);

	srand(time(NULL));
	oka::Sound::Init();
	g_camera = new oka::Camera();

	glutMainLoop();
}