#include<assert.h>
#include"SoundManager.h"
#include"../../AL/al.h"
#include"../../AL/alc.h"

namespace oka
{
	SoundManager* SoundManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ
	//ALの初期化処理
	//デバイスの取得とコンテキストの作成をする

	SoundManager::SoundManager()
	{
	
	}

	//-------------------------------------
	//デストラクタ

	SoundManager::~SoundManager()
	{
		m_sounds.clear();
	}

	//-------------------------------------
	//文字列keyとSound型のvalueを受け取って
	//メンバのmapに既に登録されているかチェックし
	//登録されていなければ追加する

	void SoundManager::AddSound(const std::string _str, const unsigned int _sound)
	{
		if (m_sounds.find(_str)==m_sounds.end())
		{
			m_sounds.insert(std::make_pair(_str, _sound));
		}
	}


	//-------------------------------------
	//文字列keyとSound型のvalueを受け取って
	//メンバのmapに既に登録されているかチェックし
	//登録されていればmapから除外しdeleteする

	//使うとき要注意

	void SoundManager::DeleteSound(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			assert(0);
		}
		else
		{
			m_sounds.erase(_str);
		}
	}

	//-------------------------------------
	//音の再生

	void SoundManager::Play(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			assert(0);
		}
		else
		{
			alSourcePlay(m_sounds[_str]);
		}
	}


	//-------------------------------------
	//音の停止

	void SoundManager::Stop(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			assert(0);
		}
		else
		{
			alSourceStop(m_sounds[_str]);
		}
		
	}

	//-------------------------------------
	//音量の調整

	void SoundManager::ChangeVolume(const std::string _str,const float _value)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			assert(0);
		}
		else
		{
			alSourcef(m_sounds[_str], AL_GAIN, _value);
		}
	}

	//-------------------------------------
	//音階の変更
	void SoundManager::ChangePitch(const std::string _str, const float _value)
	{
		alSourcef(m_sounds[_str], AL_PITCH, _value);

	}

}//namespace oka