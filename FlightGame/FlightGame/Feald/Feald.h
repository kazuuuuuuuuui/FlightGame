#ifndef FEALD_H_
#define FEALD_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;

	/*
	
	Mesh�ɏ�������
	
	*/

	//���_��
	unsigned int m_vertices;

	//�C���f�b�N�X��
	unsigned int m_indeces;

	//���_���
	std::vector<glm::vec3>m_vertex;

	//�C���f�b�N�X���
	std::vector<unsigned short>m_index;

	//�@�����
	std::vector<glm::vec3>m_normal;

	//uv���
	std::vector<glm::vec2>m_tex;

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
	m_width(256),
	m_height(256)
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

