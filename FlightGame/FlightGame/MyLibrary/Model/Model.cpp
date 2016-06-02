#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"Model.h"

namespace oka
{
	//-------------------------------------
	//xファイルから3Dモデルを読み込み
	
	ModelSP Model::LoadXFile(const char *_xFileName)
	{
		ModelSP model(new Model());

		FILE *fp = fopen(_xFileName, "r");
		char buf[256];

		if (NULL == fp)
		{
			printf("ファイルが見つかりません\n");
			assert(0);
		}

		//-------------------------------------
		//読み飛ばし

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
		 頂点数読み込み
		 **************/
		fscanf(fp, "%u", &(model->m_vertexNum));
		//printf("頂点数:%u\n", vertexNum);

		fscanf(fp, "%s", buf); //;の読み飛ばし

		/***********
		 頂点読み込み
		 ************/
		for (unsigned int i = 0; i < model->m_vertexNum; i++)
		{
			glm::vec3 v;

			fscanf(fp, "%f;%f;%f;", &v.x, &v.y, &v.z);

			//zの要素符号反転
			v.z *= (-1.0f);

			model->m_vertex.push_back(v);

			fscanf(fp, "%*1s", buf);// ,の読み飛ばし	
		}


		/*********************
		インデックス数読み込み
		*********************/
		fscanf(fp, "%u", &model->m_indexNum);
		//printf("インデックス数:%u\n", indexNum);

		fscanf(fp, "%s", buf); //;の読み飛ばし

		/********************
		 インデックス読み込み
		*********************/
		for (unsigned int i = 0; i < model->m_indexNum; i++)
		{
			unsigned short index[3];

			fscanf(fp, "%s", buf);// 3; 読み飛ばし

			fscanf(fp, "%hu,%hu,%hu", &index[0], &index[1], &index[2]);

			fscanf(fp, "%s", buf);// , 読み飛ばし

			model->m_index.push_back(index[0]);
			model->m_index.push_back(index[1]);
			model->m_index.push_back(index[2]);
		}

		//-------------------------------------
		//読み飛ばし

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
		 法線数読み込み
		**************/
		fscanf(fp, "%u", &model->m_normalNum);
		//printf("法線数:%u\n", normalNum);

		fscanf(fp, "%s", buf); //;の読み飛ばし

		/***********
		 法線読み込み
		************/
		for (unsigned int i = 0; i < model->m_normalNum; i++)
		{
			glm::vec3 n;

			fscanf(fp, "%f;%f;%f;", &n.x, &n.y, &n.z);

			//zの要素符号反転
			n.z *= (-1.0f);

			fscanf(fp, "%*1s", buf);// ,の読み飛ばし	

			model->m_normal.push_back(n);
		}

		//-------------------------------------
		//読み飛ばし

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
		 uv数読み込み
		************/
		fscanf(fp, "%u", &model->m_texNum);
		//printf("uv数:%u\n", texNum);

		fscanf(fp, "%s", buf); //;の読み飛ばし

		/***********
		 uv読み込み
		************/
		for (unsigned int i = 0; i < model->m_texNum; i++)
		{
			glm::vec2 t;

			fscanf(fp, "%f;%f;", &t.x, &t.y);

			model->m_tex.push_back(t);

			fscanf(fp, "%*1s", buf);// ,の読み飛ばし	
		}


		return model;
	}

}//namespace oka
