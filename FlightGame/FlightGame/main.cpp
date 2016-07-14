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
//�L�[�{�[�h���������ۂ̃R�[���o�b�N�֐�

void keyboard(unsigned char key, int x, int y)
{
	oka::Keyboard::KeyPress(key);
}

//-------------------------------------
//�L�[�{�[�h�𗣂����ۂ̃R�[���o�b�N�֐�

void keyboardUp(unsigned char key, int x, int y)
{
	oka::Keyboard::KeyUp(key);
}

//----------------------------------------
//�X�V�ƕ`��

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
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

//-------------------------------------
//��ʂ̔䗦���ς�������ɕ`��T�C�Y���Čv�Z����R�[���o�b�N�֐�

void reshape(int _width, int _height)
{
	oka::Screen::GetInstance()->SetWidth(_width);
	oka::Screen::GetInstance()->SetHeight(_height);
}

//-------------------------------------
//�G���g���[�|�C���g

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