#include<assert.h>
#include"SoundManager.h"
#include"../../AL/al.h"
#include"../../AL/alc.h"

namespace oka
{
	SoundManager* SoundManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^
	//AL�̏���������
	//�f�o�C�X�̎擾�ƃR���e�L�X�g�̍쐬������

	SoundManager::SoundManager()
	{
	
	}

	//-------------------------------------
	//�f�X�g���N�^

	SoundManager::~SoundManager()
	{
		m_sounds.clear();
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