#include"GameMainScene.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../glut.h"

void GameMainScene::Update()
{
	//全オブジェクトの更新
	auto itr = oka::GameManager::GetInstance()->m_gameObjects.begin();
	auto end = oka::GameManager::GetInstance()->m_gameObjects.end();

	for (; itr != end; itr++)
	{
		itr->second->Update();
	}


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

	const float value = 8.0f;//補完係数

	glm::vec3 v;
	glm::vec3 toVec;
	glm::vec3 upVec;

	const auto begin = oka::CharacterManager::GetInstance()->m_characters.begin();
	v = (*begin)->m_transform.GetPosition();
	toVec = (*begin)->m_transform.m_myToVec;
	upVec = (*begin)->m_transform.m_myUpVec;

	//カメラの注視点

	glm::vec3 target = v;

	//カメラの座標
	glm::vec3 pos;
	
	pos.x = v.x - toVec.x * value;
	pos.y = v.y + 3.0f;
	pos.z = v.z - toVec.z * value;

	//カメラのupベクトル
	glm::vec3 up;
	up.x = 0.0f + upVec.x;
	up.y = 1.0f + upVec.y;
	up.z = 0.0f + upVec.z;

	g_camera->Perspective();
	g_camera->SetViewMatrix(pos, target, up);
	g_camera->MultViewMatrix();

	//全オブジェクトの描画
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
