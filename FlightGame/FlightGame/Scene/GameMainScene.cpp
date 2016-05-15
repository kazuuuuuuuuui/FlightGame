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


#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

GameMainScene::GameMainScene()
{
	printf("�Q�[�����C���V�[������\n");
	printf("\n");

	//debug
	oka::GameManager::GetInstance()->AddGameObject("Feald", new Feald());
	oka::ImageManager::GetInstance()->SetHandle("FealdTex", oka::LoadImage3f("tex.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::LoadImage4f("smoke.bmp"));
	oka::ImageManager::GetInstance()->SetHandle("Target", oka::LoadImage4f("target.bmp"));

	oka::CharacterManager::GetInstance()->AddCharacter(new Player(glm::vec3(0.0f, 5.0f, 0.0f)));
	oka::CharacterManager::GetInstance()->AddCharacter(new Enemy(glm::vec3(0.0f, 5.0f, -100.0f)));

	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		oka::GameManager::GetInstance()->AddGameObject("Character", (*itr));

		itr++;
	}


	//debug
	oka::SoundManager::GetInstance()->AddSound("Shot", oka::Sound::LoadWavFile("Shot.wav"));
	oka::SoundManager::GetInstance()->AddSound("Explode", oka::Sound::LoadWavFile("Explode.wav"));

	oka::ModelManager::GetInstance()->AddModel("Airplane", oka::xFile::LoadXFile("f_35.x"));

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

	//��ŕύX

	/*
	
	�L�����N�^�[�}�l�W���[�����
	���񂾓G�����O����K�v������
	�����蔻��݂̂��c���Ă��܂��Ă���
	
	*/



	oka::BulletManager::GetInstance()->Updata();
	auto hoge = oka::BulletManager::GetInstance()->m_bullets.begin();
	auto piyo = oka::BulletManager::GetInstance()->m_bullets.end();
	while (hoge != piyo)
	{
		(*hoge)->m_transform.Update();
		(*hoge)->Update();
		hoge++;
	}


}

void GameMainScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const float value = 8.0f;//�⊮�W��

	glm::vec3 v;
	glm::vec3 toVec;
	glm::vec3 upVec;

	const auto begin = oka::CharacterManager::GetInstance()->m_characters.begin();
	v = (*begin)->m_transform.GetPosition();
	toVec = (*begin)->m_transform.m_myToVec;
	upVec = (*begin)->m_transform.m_myUpVec;

	//�J�����̒����_

	glm::vec3 target = v;

	//�J�����̍��W
	glm::vec3 pos;
	
	pos.x = v.x - toVec.x * value;
	pos.y = v.y + 3.0f;
	pos.z = v.z - toVec.z * value;

	//�J������up�x�N�g��
	glm::vec3 up;
	up.x = 0.0f + upVec.x;
	up.y = 1.0f + upVec.y;
	up.z = 0.0f + upVec.z;

	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	//�S�I�u�W�F�N�g�̕`��
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Draw();
	}

	auto hoge = oka::BulletManager::GetInstance()->m_bullets.begin();
	auto piyo = oka::BulletManager::GetInstance()->m_bullets.end();
	while (hoge != piyo)
	{
		(*hoge)->Draw();
		hoge++;
	}


	/*for (auto itr = oka::EffectManager::GetInstance()->m_effects.begin(); itr != oka::EffectManager::GetInstance()->m_effects.end(); itr++)
	{
		(*itr)->Draw();
	}


	for (auto itr = oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.begin(); itr != oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.end(); itr++)
	{
		(*itr)->Draw();
	}*/

}
