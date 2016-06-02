#include<stdio.h>
#include<vector>
#include"glm\glm.hpp"
#include"glut.h"

class GameObj
{
public:
	virtual void Draw() = 0;
};

//-------------------------------------
//テストクラス

class Character :public GameObj
{
public:
	glm::vec3 pos;
	glm::vec3 rotate;
	glm::vec3 scale;

	void Draw();

	Character(glm::vec3 _pos) :
	pos(_pos),
	rotate(glm::vec3(0, 0, 0)),
	scale(glm::vec3(1, 1, 1))
	{}
};

void Character::Draw()
{
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(0, rotate.x, rotate.y, rotate.z);
		glScalef(scale.x, scale.y, scale.z);

		glutSolidTeapot(1);
	}
	glPopMatrix();
}

//-------------------------------------

class Feald :public GameObj
{
public:

	void Draw();
};

void Feald::Draw()
{
	//フィールド
	glBegin(GL_LINES);
	for (float i = -10; i <= 10; i++)
	{
		glColor3f(1, 0, 0);
		glVertex3f(i, 0, -10);
		glVertex3f(i, 0, 10);

		glColor3f(0, 1, 0);
		glVertex3f(-10, 0, i);
		glVertex3f(10, 0, i);
	}
	glEnd();
}

//マネージャー

class GameObjManager
{
public:
	std::vector<GameObj*>objcts;
	static GameObjManager* getInstance();
};

GameObjManager* GameObjManager::getInstance()
{
	static GameObjManager *instance;

	if (nullptr == instance)
	{
		instance = new GameObjManager();
	}
	return instance;
}


//std::vector<Character*>g_characters;
//Character *g_player = nullptr;
//Character *g_enemy = nullptr;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		0, 10, 20,
		0, 0, 0,
		0, 1, 0);

	auto itr = GameObjManager::getInstance()->objcts.begin();
	auto end = GameObjManager::getInstance()->objcts.end();

	while (itr != end)
	{
		(*itr)->Draw();
		itr++;
	}

	

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(900, 780);
	glutCreateWindow("title");

	glutDisplayFunc(display);

	glutTimerFunc(0, timer, 0);

	Character *player = new Character(glm::vec3(5, 0, 0));
	Character *enemy = new Character(glm::vec3(-5, 0, 0));

	Feald *feald = new Feald();

	GameObjManager::getInstance()->objcts.push_back(player);
	GameObjManager::getInstance()->objcts.push_back(enemy);
	GameObjManager::getInstance()->objcts.push_back(feald);

	glutMainLoop();

}