#include"GameMainScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../glut.h"

void GameMainScene::Update()
{
	//�L�����N�^�[�̑���
	//for (unsigned int i = 0; i < oka::JoysticManager::GetInstance()->GetContorollerNumber(); i++)
	//{
	//	if (oka::JoysticManager::GetInstance()->GetContoroller(i).m_isConnect)
	//	{
	//		unsigned short pressedKey = oka::JoysticManager::GetInstance()->GetContoroller(i).m_state.Gamepad.wButtons;
	//		unsigned int downKeys = oka::JoysticManager::GetInstance()->GetContoroller(i).m_downkey;
	//		float sThumbLX = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLX;
	//		float sThumbLY = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLY;

	//		oka::CharacterManager::GetInstance()->m_characters[i]->Control(pressedKey, downKeys, sThumbLX, sThumbLY);
	//	}
	//	else
	//	{
	//		//oka::CharacterManager::GetInstance()->m_characters[i]->Control();
	//	}

	//}

	//�S�I�u�W�F�N�g�̍X�V
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin()->second.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.begin()->second.end();

	for (; itr != end; itr++)
	{
		(*itr)->Update();
	}

	/*
	
	�e�ύX�\��
	
	*/

	//�e 
	/*for (auto itr = oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.begin(); itr != oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.end();itr++)
	{
		(*itr)->Update();
	}*/

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
	pos.y = v.y - toVec.y * value;
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
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin()->second.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.begin()->second.end();

	for (; itr != end; itr++)
	{
		(*itr)->Draw();
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
