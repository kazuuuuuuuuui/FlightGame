#include<stdio.h>
#include<time.h>
#include"Singleton\BaseSingleton.h"
#include"MyLibrary\Manager\GameManager.h"
#include"MyLibrary\Manager\SceneManager.h"
#include"MyLibrary\Manager\JoysticManager.h"
#include"MyLibrary\Input\Controller.h"
#include"MyLibrary\Input\Keyboard.h"
#include"MyLibrary\Screen\Screen.h"
#include"AL\al.h"
#include"AL\alc.h"
#include"glut.h"

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//-------------------------------------
//キーボードを押した際のコールバック関数

void keyboard(unsigned char key, int x, int y)
{
	oka::Keyboard::KeyPress(key);
}

//-------------------------------------
//キーボードを離した際のコールバック関数

void keyboardUp(unsigned char key, int x, int y)
{
	oka::Keyboard::KeyUp(key);
}

//----------------------------------------
//更新と描画

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//BaseSingleton::Update();

	oka::GameManager::GetInstance()->Update();
	oka::JoysticManager::GetInstance()->Update();
	oka::SceneManager::GetInstance()->Update();
	
	oka::Keyboard::GetPrevStates();

	glFlush();
}

//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) 
{
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

//-------------------------------------
//エントリーポイント

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

	ALCdevice *device = alcOpenDevice(NULL);
	assert(alcGetError(device) == ALC_NO_ERROR);

	ALCcontext *context;
	context = alcCreateContext(device, NULL);
	assert(alcGetError(device) == ALC_NO_ERROR);

	alcMakeContextCurrent(context);
	assert(alcGetError(device) == ALC_NO_ERROR);

	glutMainLoop();
}