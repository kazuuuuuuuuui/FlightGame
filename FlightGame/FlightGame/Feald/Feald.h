#ifndef FEALD_H_
#define FEALD_H_

#include<vector>
#include"../MyLibrary/GameObject/GameObject.h"

//Feald�ւ̃X�}�[�g�|�C���^���`��
class Feald;
typedef std::shared_ptr<Feald> FealdSP;

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;

	unsigned int m_vertices;
	unsigned int m_indeces;
	std::vector<glm::vec3>m_vertex;
	std::vector<unsigned short>m_index;
	std::vector<glm::vec3>m_normal;
	std::vector<glm::vec2>m_tex;

	static FealdSP Create();
	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);
	void Draw();
	void Update();

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
		SetHeight("heightmap.bmp");

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

