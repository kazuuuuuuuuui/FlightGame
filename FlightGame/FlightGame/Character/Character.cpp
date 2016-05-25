#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"Player.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../glm/gtx/transform.hpp"
#include"../glut.h"


//-------------------------------------
//コンストラクタ

Character::Character()
{
	printf("キャラクター生成\n");

	m_transform.m_scale = glm::vec3(0.3f, 0.6f, 0.3f);


	//体部分
	oka::Model *body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = new oka::Mesh(body, tex);
	oka::GameManager::GetInstance()->AddGameObject("Body", m_body);

	//プロペラ部分
	/*oka::Model *propeller = oka::ModelManager::GetInstance()->m_models["Propeller"];
	m_propeller = new oka::Mesh(propeller, tex);
	m_propeller->m_transform.m_scale = glm::vec3(0.5f, 1.0f, 0.5f);
	oka::GameManager::GetInstance()->AddGameObject("Propeller", m_propeller);*/

	m_controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->AddController(m_controller);

	m_isHitAttack = false;
	m_hp = 100;

	m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
};

void Character::Update()
{
	//座標更新
	m_speed += m_accel;
	m_transform.m_position += m_speed;

	//慣性
	m_speed *= 0.965f;

	//ボディ
	m_body->m_transform = m_transform;

	//オフセット計算
	//glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.0f, -10.0f));

	
   //プロペラ
	/*m_propeller->m_transform.m_translateMatrix = m_transform.m_translateMatrix;
	m_propeller->m_transform.m_rotateMatrix = m_transform.m_rotateMatrix;

	m_propeller->m_transform.m_matrix *= offSet;*/
	//

	if (m_controller->CheckIsConect())
	{
		unsigned short pressedKey = m_controller->m_state.Gamepad.wButtons;
		unsigned int downKeys = m_controller->m_downkey;
		float sThumbLX = m_controller->m_sThumbLX;
		float sThumbLY = m_controller->m_sThumbLY;

		Control(pressedKey, downKeys, sThumbLX, sThumbLY);
	}
	else
	{
		//Control();
	}
	
	if (m_isHitAttack)
	{
		//書き換え
		m_hp -= 100;
	}

	m_isHitAttack = false;


	//死亡判定
	if (m_isActive)
	{
		if (CheckIsDead())
		{
			m_isActive = false;
			m_body->m_isActive = false;
			
			//爆発音
			oka::SoundManager::GetInstance()->Play("Explode");

			//爆発エフェクト
			const unsigned int num = 15;
			oka::GameManager::GetInstance()->AddGameObject("Smoke", Smoke::Create(m_transform.m_position, num));
			oka::GameManager::GetInstance()->AddGameObject("Fire", Fire::Create(m_transform.m_position));
		}
	}

	//debug
	m_transform.DrawMyToVec();
	m_transform.DrawMyUpVec();
	m_transform.DrawMySideVec();
}

//-------------------------------------
//HPの値を参照し0以下になっていればtrue
//そうでなければfalseを返す

bool Character::CheckIsDead()const
{
	if (m_hp <= 0)
	{	
		return true;
	}

	return false;
	
}
