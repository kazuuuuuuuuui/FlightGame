#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"..//MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"

#include"../MyLibrary/Screen/Screen.h"
#include"../Bullet/HomingBullet.h"

#include"../glm/gtc/quaternion.hpp"
#include"../glm/gtx/quaternion.hpp"

#include"../glut.h"


//-------------------------------------
//コンストラクタ

Player::Player():
	m_isRockOn(false),
	m_target(nullptr),
	m_score(0)
{
	m_controller = oka::JoysticManager::GetInstance()->GetController(0);

	m_transform.m_position = glm::vec3(130.0f, 30.0f, 180.0f);
}

//-------------------------------------
//デストラクタ

Player::~Player()
{

}

//-------------------------------------
//自機の生成

PlayerSP Player::Create()
{
	PlayerSP player(new Player());

	return player;
}

//-------------------------------------
//更新

void Player::Update()
{
//debug
//printf("x:%fy:%fz:%f\n", m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

	//座標更新
	m_speed = m_transform.m_myToVec*0.5f + m_accel;
	m_transform.m_position += m_speed;

	SetOnRadarPos();

	//慣性
	m_accel *= 0.98f;
	m_speed *= 0.98f;

	//ボディ
	m_body->m_transform = m_transform;



	/*書き換える*/
	if (m_transform.m_position.x <= -200.0f)
	{
		m_transform.m_position.x = -200.0f;
	}
	if (m_transform.m_position.x >= 400.0f)
	{
		m_transform.m_position.x = 400.0f;
	}
	if (m_transform.m_position.z >= 180.0f)
	{
		m_transform.m_position.z = 180.0f;
	}
	if (m_transform.m_position.z <= -450.0f)
	{
		m_transform.m_position.z = -450.0f;
	}
	if (m_transform.m_position.y >= 250.0f)
	{
		m_transform.m_position.y = 250.0f;
	}

	/**/

	if (m_controller->IsConected())
	{
		unsigned short pressedKey = m_controller->m_state.Gamepad.wButtons;
		unsigned int downKeys = m_controller->m_downkey;
		float sThumbLX = m_controller->m_sThumbLX;
		float sThumbLY = m_controller->m_sThumbLY;

		Control(pressedKey, downKeys, sThumbLX, sThumbLY);
	}
	else
	{
		Control();
	}

	if (0 == m_flame %(60*2))
	{
		m_isHitAttack = false;
	}

	std::tie(m_isRockOn, m_target) = SetTarget();

	if (IsGroundOut())
	{
		if(IsIntersectSea())
		{
			m_isActive = false;
			m_body->m_isActive = false;
		}
	}
	else
	{
		if (IsIntersectGround())
		{
			m_isActive = false;
			m_body->m_isActive = false;
		}
	}

	//死亡判定
	if (!m_isActive)
	{
		//爆発音
		oka::SoundManager::GetInstance()->Play("Explode");

		//爆発エフェクト
		EffectInfo smokeInfo;
		smokeInfo.basePos = m_transform.m_position;
		smokeInfo.particleNum = 5;
		smokeInfo.color = glm::vec3(0, 0, 0);
		SmokeSP smoke = Smoke::Create(smokeInfo);
		oka::GameManager::GetInstance()->Add("Smoke", smoke);

		EffectInfo fireInfo;
		fireInfo.basePos = m_transform.m_position;;
		fireInfo.particleNum = 20;
		fireInfo.color = glm::vec3(1.0f, 0.5f, 0.25f);
		FireSP fire = Fire::Create(fireInfo);
		oka::GameManager::GetInstance()->Add("Fire", fire);

		oka::CharacterManager::GetInstance()->m_player->PlusMyScore();

	}
}

//-------------------------------------
//キーボードでの操作

void Player::Control()
{
	Accel();
	Shot();

	const float value = oka::MyMath::ToRadian(1.0f);

	//Roll
	//if (oka::Keyboard::GetStates('m'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));
	//}
	//else if (oka::Keyboard::GetStates('n'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 0, -1));
	//}

	////Yaw
	//if (oka::Keyboard::GetStates('d'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));
	//}
	//else if (oka::Keyboard::GetStates('a'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 1, 0));
	//}

	////Pitch
	//if (oka::Keyboard::GetStates('s'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));
	//}
	//else if (oka::Keyboard::GetStates('w'))
	//{
	//	m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));
	//}

}

//-------------------------------------
//ゲームパッドでの操作

void Player::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	Accel(_pressedKey);
	Shot(_downKeys);
	HomingShot(_downKeys);

	const float value = oka::MyMath::ToRadian(0.8f);
	glm::tquat<float> quat;

	//Roll
	if (_pressedKey & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;
		
	}
	else if (_pressedKey & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;
	}

	//Yaw
	if (_sThumbLX > 0.5f)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;
		
	}
	else if (_sThumbLX < -0.5f){
		quat = oka::MyMath::Rotate(-value, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;
	}

	//Pitch
	if (_sThumbLY > 0.5f)
	{
		quat = oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	else if (_sThumbLY < -0.5f)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
}

//-------------------------------------
//前進処理
//キーボード スペースキー で前進

void Player::Accel()
{
	if (oka::Keyboard::GetStates(' '))
	{
		const float value = 0.02f;

		glm::vec3 accel;
		accel = m_transform.m_myToVec*value;

		m_accel = accel;
	}
	else
	{
		m_accel = glm::vec3(0, 0, 0);
	}
}

//-------------------------------------
//前進処理
//ゲームパッド A で前進

void Player::Accel(unsigned short _pressedKey)
{
	if (_pressedKey & XINPUT_GAMEPAD_A)
	{
		const float value = 0.02f;//加速度補間値
		m_accel += m_transform.m_myToVec*value;
	}
}

//-------------------------------------
//弾による攻撃
//弾の座標を自身の座標にセットし
//弾のスピードを設定する

void Player::Shot()
{
	if (oka::Keyboard::GetStates('b'))
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");
		
		glm::vec3 pos;
		const float distance = 2.0f;//自機と弾発射点の間隔
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//弾のスピード補完値
		speed = m_transform.m_myToVec * value;

		glm::tquat<float>quat = m_transform.m_rotate;
	
		BulletSP bullet = Bullet::Create(pos, quat, speed);
		oka::BulletManager::GetInstance()->AddBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//弾による攻撃

void Player::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_X)
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 5.0f;//自機と弾発射点の間隔
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 3.0f;//弾のスピード補完値
		speed = m_transform.m_myToVec * value;

		glm::tquat<float> mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->AddBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//ホーミング弾による攻撃
//ロックオンしていないと打てない

void Player::HomingShot(unsigned short _downKeys)
{
	if (m_isRockOn && (_downKeys & XINPUT_GAMEPAD_Y))
	{
		oka::SoundManager::GetInstance()->Play("HomingBullet");

		//自機と弾発射点の間隔
		const float downDis = 5.0f;
		const float toDis = 10.0f;
		
		const glm::vec3 pos = m_transform.m_position + m_transform.m_myToVec*toDis - m_transform.m_myUpVec*downDis;

		glm::vec3 speed;
		speed = m_transform.m_myToVec;
	
		const glm::tquat<float>quat = m_transform.m_rotate;

		HomingBulletSP homingBullet = HomingBullet::Create(m_target, pos, quat, speed);
		oka::BulletManager::GetInstance()->AddBullet(homingBullet);
		oka::GameManager::GetInstance()->Add("HomingBullet", homingBullet);
	}
}

//-------------------------------------
//的の描画位置決定

std::tuple<bool, glm::vec3*> Player::SetTarget()
{
	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const float rad = 100.0f;
	float distance;

	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		static const float dis = 200.0f;
		if (IsNear((*itr)->m_transform.m_position,dis))
		{
			if (glm::intersectRaySphere(pos, dir, (*itr)->m_transform.m_position, rad, distance))
			{
				return std::make_tuple(true, &((*itr)->m_transform.m_position));
			}
		}
		itr++;
	}

	return std::make_tuple(false, nullptr);
}

//-------------------------------------
//弾の行先を定める為の的の描画

void Player::DrawTarget()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//的の縦横
		static const float width = 3.0f;
		static const float height = 3.0f;
		
		//debug
//printf("x:%fy:%fz:%f\n", m_targetPos.x, m_targetPos.y, m_targetPos.z);

		//描画場所
		unsigned int tex;
	
		glPushMatrix();
		{
			if (m_isRockOn)
			{
				oka::SoundManager::GetInstance()->Play("RockOn");
				tex = oka::ImageManager::GetInstance()->GetHandle("RockOn");
				glTranslatef((*m_target).x, (*m_target).y, (*m_target).z);
			}
			else
			{
				oka::SoundManager::GetInstance()->Stop("RockOn");
				tex = oka::ImageManager::GetInstance()->GetHandle("Target");

				const float value = 30.0f;//キャラクターとの間隔補完値
				const glm::vec3 pos = m_transform.m_position;
				const glm::vec3 toVec = m_transform.m_myToVec*value;
				const glm::vec3 v = pos + toVec;

				glTranslatef(v.x, v.y, v.z);
			}

			glMultMatrixf((GLfloat*)&BillboardMatrix);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex);
			
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f, 0.0f); glVertex2f(-width / 2, -height / 2);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(width / 2, -height / 2);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(width / 2, height / 2);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(-width / 2, height / 2);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();

}

//-------------------------------------
//自身のスコアを表示する

void Player::DrawMyScore()const
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		char buf[256];
		
		const int width = oka::Screen::GetInstance()->GetWidth() / 10 - 50;
		const int height = oka::Screen::GetInstance()->GetHeight() - oka::Screen::GetInstance()->GetHeight() / 8;

		sprintf_s(buf, "Hit:%d", m_score);

		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(2);

		glPushMatrix();
		{
			glTranslatef(width, height, 0.0f);
			glScalef(0.5f, 0.5f, 0.5f);

			for (unsigned int i = 0; i < strlen(buf); i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, buf[i]);
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
}

//-------------------------------------
//敵索上での自分の位置を描画する

void Player::DrawRadarPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glColor3f(0, 0, 1);
		glPointSize(15);

		glBegin(GL_POINTS);
		{
			glVertex2f(m_onRadarPos.x, m_onRadarPos.y);
		}
		glEnd();
	}
	glPopAttrib();
}

//-------------------------------------
//自分のスコアを返す

unsigned int Player::GetMyScore()const
{
	return m_score;
}


//-------------------------------------
//自身の撃退数を１増加させる

void Player::PlusMyScore()
{
	m_score++;
}