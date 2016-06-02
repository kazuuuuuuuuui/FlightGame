#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"Model.h"

namespace oka
{
	//-------------------------------------
	//x�t�@�C������3D���f����ǂݍ���
	
	ModelSP Model::LoadXFile(const char *_xFileName)
	{
		ModelSP model(new Model());

		FILE *fp = fopen(_xFileName, "r");
		char buf[256];

		if (NULL == fp)
		{
			printf("�t�@�C����������܂���\n");
			assert(0);
		}

		//-------------------------------------
		//�ǂݔ�΂�

		while (1)
		{
			fscanf(fp, "%s", buf);

			if (0 == strcmp("Mesh", buf))
			{
				break;
			}
		}
		fscanf(fp, "%s", buf); //{


		/*************
		 ���_���ǂݍ���
		 **************/
		fscanf(fp, "%u", &(model->m_vertexNum));
		//printf("���_��:%u\n", vertexNum);

		fscanf(fp, "%s", buf); //;�̓ǂݔ�΂�

		/***********
		 ���_�ǂݍ���
		 ************/
		for (unsigned int i = 0; i < model->m_vertexNum; i++)
		{
			glm::vec3 v;

			fscanf(fp, "%f;%f;%f;", &v.x, &v.y, &v.z);

			//z�̗v�f�������]
			v.z *= (-1.0f);

			model->m_vertex.push_back(v);

			fscanf(fp, "%*1s", buf);// ,�̓ǂݔ�΂�	
		}


		/*********************
		�C���f�b�N�X���ǂݍ���
		*********************/
		fscanf(fp, "%u", &model->m_indexNum);
		//printf("�C���f�b�N�X��:%u\n", indexNum);

		fscanf(fp, "%s", buf); //;�̓ǂݔ�΂�

		/********************
		 �C���f�b�N�X�ǂݍ���
		*********************/
		for (unsigned int i = 0; i < model->m_indexNum; i++)
		{
			unsigned short index[3];

			fscanf(fp, "%s", buf);// 3; �ǂݔ�΂�

			fscanf(fp, "%hu,%hu,%hu", &index[0], &index[1], &index[2]);

			fscanf(fp, "%s", buf);// , �ǂݔ�΂�

			model->m_index.push_back(index[0]);
			model->m_index.push_back(index[1]);
			model->m_index.push_back(index[2]);
		}

		//-------------------------------------
		//�ǂݔ�΂�

		while (1)
		{
			fscanf(fp, "%s", buf);

			if (0 == strcmp("MeshNormals", buf))
			{
				break;
			}
		}
		fscanf(fp, "%s", buf); //{


		/*************
		 �@�����ǂݍ���
		**************/
		fscanf(fp, "%u", &model->m_normalNum);
		//printf("�@����:%u\n", normalNum);

		fscanf(fp, "%s", buf); //;�̓ǂݔ�΂�

		/***********
		 �@���ǂݍ���
		************/
		for (unsigned int i = 0; i < model->m_normalNum; i++)
		{
			glm::vec3 n;

			fscanf(fp, "%f;%f;%f;", &n.x, &n.y, &n.z);

			//z�̗v�f�������]
			n.z *= (-1.0f);

			fscanf(fp, "%*1s", buf);// ,�̓ǂݔ�΂�	

			model->m_normal.push_back(n);
		}

		//-------------------------------------
		//�ǂݔ�΂�

		while (1)
		{
			fscanf(fp, "%s", buf);

			if (0 == strcmp("MeshTextureCoords", buf))
			{
				break;
			}
		}
		fscanf(fp, "%s", buf); //{

		/***********
		 uv���ǂݍ���
		************/
		fscanf(fp, "%u", &model->m_texNum);
		//printf("uv��:%u\n", texNum);

		fscanf(fp, "%s", buf); //;�̓ǂݔ�΂�

		/***********
		 uv�ǂݍ���
		************/
		for (unsigned int i = 0; i < model->m_texNum; i++)
		{
			glm::vec2 t;

			fscanf(fp, "%f;%f;", &t.x, &t.y);

			model->m_tex.push_back(t);

			fscanf(fp, "%*1s", buf);// ,�̓ǂݔ�΂�	
		}


		return model;
	}

}//namespace oka
