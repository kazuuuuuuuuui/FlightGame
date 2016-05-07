#include<stdio.h>
#include<time.h>
#include"MyLibrary\Manager\GameManager.h"
#include"MyLibrary\Manager\SceneManager.h"
#include"MyLibrary\Manager\JoysticManager.h"
#include"MyLibrary\Input\Controller.h"

#include"MyLibrary\Manager\CharacterManager.h"

#include"MyLibrary\Input\Keyboard.h"
#include"MyLibrary\Screen\Screen.h"
#include"MyLibrary\Camera\Camera.h"
#include"glut.h"

//-------------------------------------
//fps�v���p�ϐ��Ɗ֐�(debug�p)

int g_GLframe = 0; //�t���[����
int g_GLtimenow = 0;//�o�ߎ���
int g_GLtimebase = 0;//�v���J�n����

void fps()
{
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

	if (g_GLtimenow - g_GLtimebase > 1000)      //�P�b�ȏソ������fps���o��
	{
		printf("fps:%f\r", g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase));
		g_GLtimebase = g_GLtimenow;//����Ԃ�ݒ�                
		g_GLframe = 0;//�t���[���������Z�b�g
	}
}



//debug
GLenum g_mode = GL_FILL;

void keyboard(unsigned char key, int x, int y)
{
	//debug
	//printf("keyboard: key:%c x:%d y:%d\n", key, x, y);
	if (GL_FILL == g_mode)
		g_mode = GL_LINE;
	else
		g_mode = GL_FILL;

	oka::Keyboard::KeyPress(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	//debug
	//printf("keyboardUp: key:%c x:%d y:%d\n", key, x, y);

	oka::Keyboard::KeyUp(key);
}

//----------------------------------------
//�X�V�ƕ`��

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) 
{
	//fps();
	/*for (unsigned int i = 0; i<oka::CharacterManager::GetInstance()->m_characters.size(); i++)
	{
		printf("[%d]HP:%d\n", i, oka::CharacterManager::GetInstance()->m_characters[i]->m_hp);
	}*/

	//��ŕύX
	BillboardMatrix = glm::inverse(g_camera->GetViewMatrix());
	BillboardMatrix[3][0] = 0;
	BillboardMatrix[3][1] = 0;
	BillboardMatrix[3][2] = 0;

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

void Init()
{
	srand(time(NULL));
	g_camera = new oka::Camera();

	//-------------------------------------
	//�R���g���[���̒ǉ�
	//�悭�킩��Ȃ�

	for (unsigned int i = 0; i < 2; i++)
	{
		oka::JoysticManager::GetInstance()->AddController(new oka::Contoroller());
	}
	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(oka::Screen::GetInstance()->GetWidth(), oka::Screen::GetInstance()->GetHeight());
	glutInitWindowSize(900, 900);
	
	glutCreateWindow("Flight Game");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(0, timer, 0);

	Init();

	glutMainLoop();
}