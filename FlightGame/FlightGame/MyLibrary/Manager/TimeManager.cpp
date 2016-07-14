#include<stdio.h>
#include"TimeManager.h"
#include"CharacterManager.h"

namespace oka
{
	TimeManager* TimeManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ

	TimeManager::TimeManager()
	{
		//ゲームの制限時間
		m_gameTime = 60;

		m_flame = 60 * m_gameTime;
	}

	//------------------------
	//更新
	//既定のフレームをデクリメントする
	//フレーム数からミリ秒・秒・分を算出する

	void TimeManager::Update()
	{
		if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
		{
			const bool isHit = oka::CharacterManager::GetInstance()->GetPlayer()->GetIsHitAttack();
			if (isHit)
			{
				MinusTime();
			}
		}

		if (m_flame > 0)
		{
			m_flame--;
		}
		else
		{
			m_flame = 0;
		}

		m_milliSecond = ((m_flame * 1000) / 60) % 1000;
		m_second = m_flame / 60;
		m_minute = m_second / 60;
	}

	//-------------------------------------
	//フレームを取得する

	unsigned int TimeManager::GetFlame()const
	{
		return m_flame;
	}

	//-------------------------------------
	//ミリ秒を取得する

	unsigned int TimeManager::GetMilliSecond()const
	{
		return m_milliSecond;
	}

	//-------------------------------------
	//秒を取得する

	unsigned int TimeManager::GetSecond()const
	{
		return m_second % 60;
	}

	//-------------------------------------
	//分を取得する

	unsigned int TimeManager::GetMinutes()const
	{
		return m_minute;
	}

	//-------------------------------------
	//プレイヤーが攻撃を受けた際に
	//残り時間を減算する

	void TimeManager::MinusTime()
	{
		const unsigned int minusValue = 1;
		m_flame -= minusValue;
	}

}//namespace oka