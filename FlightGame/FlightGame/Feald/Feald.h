#ifndef FEALD_H_
#define FEALD_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;

	void Draw();
	void Update();

	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);


	//debug
	void DrawNormals();

	
	Feald() :
	//�ύX�\��
	m_width(64),
	m_height(64)
	{
		//debug
		printf("�t�B�[���h����������܂���\n");
		printf("\n");

		//���_�f�[�^
		SetVertex();

		//�C���f�b�N�X�f�[�^
		SetIndex();

		//���_�̍����ݒ�
		SetHeight("test.bmp");

		//�@���f�[�^
		SetNormal();

		//uv�f�[�^
		SetTex();

	};

	~Feald()
	{
		//debug
		printf("�t�B�[���h���폜����܂���\n");
		printf("\n");
	};

};

#endif

