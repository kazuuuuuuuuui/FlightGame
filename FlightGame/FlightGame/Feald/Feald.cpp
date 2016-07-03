#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include"Feald.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../glut.h"

Feald::Feald() :
	m_width(256),
	m_height(256),
	m_leftBottom(glm::vec3(-200.0f, 2.0f, 180.0f)),
	m_rightBottom(glm::vec3(400.0f, 2.0f, 180.0f)),
	m_leftTop(glm::vec3(-200.0f, 2.0f, -450.0f)),
	m_rightTop(glm::vec3(400.0f, 2.0f, -450.0f))
{
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

Feald::~Feald()
{
	//debug
	printf("�t�B�[���h���폜����܂���\n");
	printf("\n");
};

//-------------------------------------
//�t�B�[���h�̐���
//�߂�l�Ƃ���Feald�ւ�shared�|�C���^��Ԃ�

FealdSP Feald::Create()
{
	FealdSP feald(new Feald());

	return feald;
}

//------------------------
//�R�[�X�̒��_�f�[�^�̐���

void Feald::SetVertex()
{
	for (int z = 0; z < m_height; z++)
	{
		for (int x = 0; x < m_width; x++)
		{
			m_vertex.push_back(glm::vec3(x, 0, -z));
		}
	}

	m_vertices = m_vertex.size();

}

//-------------------------------------
//�R�[�X�̃C���f�b�N�X�f�[�^�̐���

void Feald::SetIndex()
{
	for (int z = 0; z < (m_height - 1); z++)
	{
		for (int x = 0; x < (m_width - 1); x++)
		{
			m_index.push_back(0 + x + m_height * z);
			m_index.push_back(1 + x + m_height * z);
			m_index.push_back(m_width + x + m_height * z);
		
			m_index.push_back(1 + x + m_height * z);
			m_index.push_back((m_width + 1) + x + m_height * z);
			m_index.push_back(m_width + x + m_height * z);
		}
	}

	m_indeces = m_index.size();

}

//-------------------------------------
//�@���̐ݒ�

void Feald::SetNormal()
{
	for (unsigned int i = 0; i < m_indeces ;i+=3)
	{
		glm::vec3 normal = glm::vec3(0, 1, 0);
		
		m_normal.push_back(normal);
		m_normal.push_back(normal);
		m_normal.push_back(normal);
		
	}
}

//----------------
//uv���W�̐ݒ�

void Feald::SetTex()
{
	for (int v = m_height; v > 0; v--)
	{
		for (int u = 0; u < m_width; u++)
		{
			glm::vec2 t;
			t.x = (u / 1.0f) / m_width;//u
			t.y = (v / 1.0f) / m_height;//v

			m_tex.push_back(t);

		}
	}
}

struct RGB
{
	unsigned char r, g, b;
};

//-------------------------------------
//�g���qbmp����R�[�X�̊e���_��Y���W��ݒ肷��

void Feald::SetHeight(const char *_fileName)
{
	FILE *fp;
	fp = fopen(_fileName, "rb");

	assert(fp != NULL);

	BITMAPFILEHEADER bh;
	fread(&bh, sizeof(BITMAPFILEHEADER), 1, fp);

	BITMAPINFOHEADER bih;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

	int imageSize = bih.biWidth * bih.biHeight * sizeof(RGB);

	RGB *pixels = (RGB*)malloc(imageSize);

	pixels = (RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, fp);

	fclose(fp);

	//�s�N�Z���P�ʂ�R��B���t�]������
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//Y���W�̐ݒ�
	for (int z = 0; z < bih.biHeight; z++)
	{
		for (int x = 0; x < bih.biWidth; x++)
		{
			float height = (pixels[z*bih.biWidth + x].r + pixels[z*bih.biWidth + x].g + pixels[z*bih.biWidth + x].b)/3.0f;
			
			height = 255.0f - height;//���ƍ��t�]
			height /= 255.0f;//0.0�`1.0f;

			//�ō����W�_
			const int max = 20.0f;
			height *= max;//0.0�`max

			m_vertex[z*bih.biWidth + x].y = height;
		}
	}

}


//-------------------------------------
//�t�B�[���h�S�̂̕`��

void Feald::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("FealdTex"));

			auto v = m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto t = m_tex.begin();
			glTexCoordPointer(2, GL_FLOAT, 0, &(*t));

			auto i = m_index.begin();

			glDrawElements(GL_TRIANGLES, m_indeces, GL_UNSIGNED_SHORT, &(*i));

			glPopMatrix();
		}
	}
	glPopAttrib();
}
