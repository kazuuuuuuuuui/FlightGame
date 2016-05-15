#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"xFile.h"
//#include"../Vector/Vec3.h"

namespace oka
{
	//-------------------------------------
	//x�t�@�C������3D���f����ǂݍ���
	
	xFile* xFile::LoadXFile(const char *_FileName)
	{
		xFile *model = new xFile();

		FILE *fp = fopen(_FileName, "r");
		char buf[256];

		if (NULL == fp)
		{
			assert(0);
		}

		while (EOF != fscanf(fp, "%s", buf))
		{
			//-------------------------------------
			//���_�f�[�^�ǂݍ���

			if (0 == strcmp("Mesh", buf))
			{
				fscanf(fp, "%*1s", buf);// { �̓ǂݔ�΂�

										//���_���ǂݍ���
				fscanf(fp, "%u", &model->m_vertices);
				
				fscanf(fp, "%*1s", buf);// ; �̓ǂݔ�΂�
										//���_�̓ǂݍ���
				for (unsigned int i = 0; i < model->m_vertices; i++)
				{
					glm::vec3 v;

					fscanf(fp, "%f;%f;%f;", &v.x, &v.y, &v.z);

					model->m_vertex.push_back(v);

					fscanf(fp, "%*1s", buf);// ,�@�̓ǂݔ�΂�	
				}


				//-------------------------------------
				//�C���f�b�N�X�f�[�^�ǂݍ���

				//�C���f�b�N�X���̓ǂݍ���
				fscanf(fp, "%u", &model->m_indeces);

				fscanf(fp, "%*s", buf);// ; �̓ǂݔ�΂�

									   //�C���f�b�N�X�̓ǂݍ���
				for (unsigned int i = 0; i < model->m_indeces; i++)
				{
					unsigned short index[3];

					fscanf(fp, "%*2s", buf);// 3; �ǂݔ�΂�

					fscanf(fp, "%hu,%hu,%hu", &index[0], &index[1], &index[2]);

					fscanf(fp, "%*s", buf);// , �ǂݔ�΂�

					model->m_index.push_back(index[0]);
					model->m_index.push_back(index[1]);
					model->m_index.push_back(index[2]);
				}
			}

			//-------------------------------------
			//�@�����̓ǂݍ���

			if (0 == strcmp("MeshNormals", buf))
			{
				fscanf(fp, "%*1s", buf);// { �̓ǂݔ�΂�

										//�@�����̓ǂݍ���
				fscanf(fp, "%u", &model->m_normals);

				fscanf(fp, "%*1s", buf);// ; �̓ǂݔ�΂�

										//�@���̓ǂݍ���
				for (unsigned int i = 0; i < model->m_normals; i++)
				{
					glm::vec3 n;

					fscanf(fp, "%f;%f;%f;", &n.x, &n.y, &n.z);

					model->m_normal.push_back(n);

					fscanf(fp, "%*1s", buf);// ,�@�̓ǂݔ�΂�	
				}
			}

			//-------------------------------------
			//uv���̓ǂݍ���

			//fscanf(fp, "%s", buf);
			//printf("%s", buf);
		}

		fclose(fp);

		return model;
	}

}//namespace oka
