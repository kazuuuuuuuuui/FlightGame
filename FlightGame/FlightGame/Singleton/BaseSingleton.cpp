#include"BaseSingleton.h"

std::vector<BaseSingleton*> BaseSingleton::m_singletons;

//-------------------------------------
//�R���X�g���N�^
//�������ꂽ�V���O���g���N���X���g��
//�x�N�^�[�Ɋi�[����

BaseSingleton::BaseSingleton()
{
	m_singletons.push_back(this);
}

//-------------------------------------
//�x�N�^�[�Ɋi�[���ꂽ�V���O���g���N���X�̍X�V���Ă�

void BaseSingleton::Update()
{
	for (unsigned int i = 0; i < m_singletons.size(); i++)
	{
		m_singletons[i]->Update();
	}
}

//-------------------------------------
//�x�N�^�[�Ɋi�[���ꂽ�V���O���g���N���X��j������

void BaseSingleton::AllDestroy()
{
	for (unsigned int i = 0; i < m_singletons.size(); i++)
	{
		m_singletons[i]->Destroy();
	}
}

//-------------------------------------
//�V���O���g���N���X���i�[����x�N�^�[����ɂ���

void BaseSingleton::Clear()
{
	m_singletons.clear();
}