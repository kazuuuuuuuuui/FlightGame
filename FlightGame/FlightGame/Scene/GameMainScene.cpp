#include"GameMainScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Sound/Sound.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"

#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../Feald/Feald.h"
#include"../Character/Player.h"
#include"../Character/Enemy.h"
#include"../MyLibrary/SkyDome/Sky.h"
#include"../MyLibrary/Sea/Sea.h"

#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

GameMainScene::GameMainScene()
{
	printf("�Q�[�����C���V�[������\n");
	printf("\n");

	//debug
	
	oka::ImageManager::GetInstance()->SetHandle("FealdTex", oka::LoadImage3f("tex.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("smoke.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("target.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("FlyTex", oka::LoadImage3f("flyTex.bmp"));

	//���f�[�^
	oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile("Shot.wav"));
	oka::SoundManager::GetInstance()->AddSound("Explode", oka::Sound::LoadWavFile("Explode.wav"));

	//���f���f�[�^
	oka::ModelManager::GetInstance()->AddModel("Body", oka::Model::LoadXFile("body.x"));
	oka::ModelManager::GetInstance()->AddModel("Propeller", oka::Model::LoadXFile("propeller.x"));

	//�t�B�[���h
	oka::GameManager::GetInstance()->AddGameObject("Feald", new Feald());

	//��
	oka::ImageManager::GetInstance()->SetHandle("Sky", oka::LoadImage3f("sky.bmp"));
	oka::ModelManager::GetInstance()->AddModel("Sky", oka::Model::LoadXFile("sky.x"));
	oka::GameManager::GetInstance()->AddGameObject("Sky", new oka::Sky());

	//�C
	oka::ImageManager::GetInstance()->SetHandle("Sea", oka::LoadImage4f("sea.bmp"));
	oka::ModelManager::GetInstance()->AddModel("Sea", oka::Model::LoadXFile("sea.x"));
	oka::GameManager::GetInstance()->AddGameObject("Sea", new oka::Sea());

	//�L�����N�^�[�̓o�^
	oka::CharacterManager::GetInstance()->AddCharacter(new Player(glm::vec3(0.0f, 10.0f, 0.0f)));
	oka::CharacterManager::GetInstance()->AddCharacter(new Enemy(glm::vec3(100.0f, 10.0f, 0.0f)));

	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		oka::GameManager::GetInstance()->AddGameObject("Character", (*itr));

		itr++;
	}
};


//-------------------------------------
//�f�X�g���N�^

GameMainScene::~GameMainScene()
{
	printf("�Q�[�����C���V�[���폜\n");
	printf("\n");
};

//-------------------------------------
//

void GameMainScene::Update()
{
	//�S�I�u�W�F�N�g�̍X�V
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Update();
	}
}

void GameMainScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	const float value = 8.0f;//�⊮�W��

	glm::vec3 toVec;
	glm::vec3 upVec;

	const auto begin = oka::CharacterManager::GetInstance()->m_characters.begin();

	toVec = (*begin)->m_transform.m_myToVec;
	upVec = (*begin)->m_transform.m_myUpVec;

	//�J�����̒����_
	glm::vec3 target = (*begin)->m_transform.m_position;

	//�J�����̍��W
	glm::vec3 pos;
	pos = target - ( toVec * 6.0f ) ;
	pos = pos + ( upVec * 2.0f ) ;

	glm::vec3 up = upVec;

	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	float v[] = { 0,100,100,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	//�S�I�u�W�F�N�g�̕`��
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Draw();
	}
}


/*

1�_���߂�
�j���[�g���̖��L���͂������x�ɂ���


*/
