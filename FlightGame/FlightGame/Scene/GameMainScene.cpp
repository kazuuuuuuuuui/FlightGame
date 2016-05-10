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
	for (unsigned int i = 0; i < oka::JoysticManager::GetInstance()->GetContorollerNumber(); i++)
	{
		if (oka::JoysticManager::GetInstance()->GetContoroller(i).m_isConnect)
		{
			unsigned short pressedKey = oka::JoysticManager::GetInstance()->GetContoroller(i).m_state.Gamepad.wButtons;
			unsigned int downKeys = oka::JoysticManager::GetInstance()->GetContoroller(i).m_downkey;
			float sThumbLX = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLX;
			float sThumbLY = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLY;

			oka::CharacterManager::GetInstance()->m_characters[i]->Control(pressedKey, downKeys, sThumbLX, sThumbLY);
		}
		else
		{
			//oka::CharacterManager::GetInstance()->m_characters[i]->Control();
		}

	}

	//�S�I�u�W�F�N�g�̍X�V
	for (auto itr = oka::GameManager::GetInstance()->m_gameObject.begin(); itr != oka::GameManager::GetInstance()->m_gameObject.end(); itr++)
	{
		itr->second->Update();
	}

	//�G�t�F�N�g
	for (auto itr = oka::EffectManager::GetInstance()->m_effects.begin(); itr != oka::EffectManager::GetInstance()->m_effects.end(); itr++)
	{
		(*itr)->Update();
	}

	oka::EffectManager::GetInstance()->EraseEffect();

	/*
	
	�e�ύX�\��
	
	*/

	//�e 
	for (auto itr = oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.begin(); itr != oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.end();itr++)
	{
		(*itr)->Update();
	}

}

void GameMainScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const float value = 8.0f;//�⊮�W��

	//�J�����̒����_
	glm::vec3 v = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetPosition();
	glm::vec3 target = v;

	//�J�����̍��W
	glm::vec3 pos;
	glm::vec3 toVec = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.m_myToVec;
	pos.x = v.x - toVec.x * value;
	pos.y = v.y - toVec.y * value;
	pos.z = v.z - toVec.z * value;

	//�J������up�x�N�g��
	glm::vec3 up;
	glm::vec3 upVec = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.m_myUpVec;
	up.x = 0.0f + upVec.x;
	up.y = 1.0f + upVec.y;
	up.z = 0.0f + upVec.z;

	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	//�S�I�u�W�F�N�g�̕`��
	for (auto itr = oka::GameManager::GetInstance()->m_gameObject.begin(); itr != oka::GameManager::GetInstance()->m_gameObject.end(); itr++)
	{
		itr->second->Draw();
	}

	for (auto itr = oka::EffectManager::GetInstance()->m_effects.begin(); itr != oka::EffectManager::GetInstance()->m_effects.end(); itr++)
	{
		(*itr)->Draw();
	}


	for (auto itr = oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.begin(); itr != oka::CharacterManager::GetInstance()->m_characters[0]->m_bullets.end(); itr++)
	{
		(*itr)->Draw();
	}

}
