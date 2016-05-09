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

	glm::vec3 pos;
	const float value = 7.0f;//�⊮�W��
	pos.x = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetPosition().x + sin(oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetRotation().y) * value;
	pos.y = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetPosition().y + 3.0f;
	pos.z = oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetPosition().z + cos(oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetRotation().y) * value;

	glm::vec3 target = {oka::CharacterManager::GetInstance()->m_characters[0]->m_transform.GetPosition()};

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	
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
