#include<assert.h>
#include"SoundManager.h"
#include"../../AL/al.h"
#include"../../AL/alc.h"

namespace oka
{
	SoundManager* SoundManager::m_instance = nullptr;
	
	//--------------------------------------------
	//�V���O���g���ɂ��邽�߂ɃC���X�^���X��
	//��������Ă��Ȃ���΃C���X�^���X�𐶐���
	//���ɃC���X�^���X����������Ă���΂��̃C���X�^���X��Ԃ�

	SoundManager* SoundManager::GetInstance() 
	{

		if (nullptr == m_instance) 
		{
			m_instance = new SoundManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//������key��Sound�^��value���󂯎����
	//�����o��map�Ɋ��ɓo�^����Ă��邩�`�F�b�N��
	//�o�^����Ă��Ȃ���Βǉ�����

	void SoundManager::AddSound(const std::string _str, const unsigned int _sound)
	{
		if (m_sounds.find(_str)==m_sounds.end())
		{
			m_sounds.insert(std::make_pair(_str, _sound));
		}
		else
		{
			
		}
	}

	


	//-------------------------------------
	//������key��Sound�^��value���󂯎����
	//�����o��map�Ɋ��ɓo�^����Ă��邩�`�F�b�N��
	//�o�^����Ă����map���珜�O��delete����

	//�g���Ƃ��v����

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
	//���̍Đ�

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
	//���̒�~

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
	//���ʂ̒���

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
	//���K�̕ύX
	void SoundManager::ChangePitch(const std::string _str, const float _value)
	{
		alSourcef(m_sounds[_str], AL_PITCH, _value);

	}

}//namespace oka