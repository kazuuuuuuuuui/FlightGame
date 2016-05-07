#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"xFile.h"
#include"../Vector/Vec3.h"

namespace oka
{
	//-------------------------------------
	//x�t�@�C������3D���f����ǂݍ���
	//�@�������͌v�Z(�t���b�g�V�F�C�f�B���O)����
	//������x�t�@�C�����ƃ��f���f�[�^���i�[����o�b�t�@��n��

	void xFile::LoadXfile(const char *_xFileName)
	{
		FILE *pFile = fopen(_xFileName, "r");

		printf("%s��������܂���\n");
		assert(pFile != NULL);

		char buf[256];
		char prevBuf[256];
		while (EOF != fscanf(pFile, "%s", buf)) {
			if (strcmp("Mesh", buf) == 0 && 0 != strcmp("template", prevBuf) && 0 != strcmp("the", prevBuf)) {

				fscanf(pFile, "%s", buf);

				//���_���ǂݍ���
				fscanf(pFile, "%u", &(model->m_indeces));

				fscanf(pFile, "%*c", buf);

				//���_�̓ǂݍ���
				for (unsigned int i = 0; i < model->m_indeces / 3; i++) {
					oka::Vec3 v[3];
					oka::Vec3 n;

					fscanf(pFile, "%f", &v[0].m_x);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[0].m_y);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[0].m_z);
					fscanf(pFile, "%*s", buf);

					model->m_vertex.push_back(v[0].m_x);
					model->m_vertex.push_back(v[0].m_y);
					model->m_vertex.push_back(v[0].m_z);

					fscanf(pFile, "%f", &v[1].m_x);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[1].m_y);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[1].m_z);
					fscanf(pFile, "%*s", buf);

					model->m_vertex.push_back(v[1].m_x);
					model->m_vertex.push_back(v[1].m_y);
					model->m_vertex.push_back(v[1].m_z);

					fscanf(pFile, "%f", &v[2].m_x);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[2].m_y);
					fscanf(pFile, "%*c", buf);

					fscanf(pFile, "%f", &v[2].m_z);
					fscanf(pFile, "%*s", buf);

					model->m_vertex.push_back(v[2].m_x);
					model->m_vertex.push_back(v[2].m_y);
					model->m_vertex.push_back(v[2].m_z);

					//�@���v�Z
					oka::Vec3 v01 = v[1] - v[0];
					oka::Vec3 v02 = v[2] - v[0];

					n = oka::Vec3::Cross(v01, v02);

					model->m_normal.push_back(n.m_x);
					model->m_normal.push_back(n.m_y);
					model->m_normal.push_back(n.m_z);

					model->m_normal.push_back(n.m_x);
					model->m_normal.push_back(n.m_y);
					model->m_normal.push_back(n.m_z);

					model->m_normal.push_back(n.m_x);
					model->m_normal.push_back(n.m_y);
					model->m_normal.push_back(n.m_z);

				}

				//�C���f�b�N�X���ǂݍ���
				fscanf(pFile, "%u", &(model->m_indeces));

				fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

				//�C���f�b�N�X�̓ǂݍ���
				for (unsigned int i = 0; i < model->m_indeces; i++) {

					fscanf(pFile, "%*2s", buf);//*�͓ǂݎ̂Ă�

					unsigned short indeces[3];
					fscanf(pFile, "%hu", &indeces[0]);

					fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

					fscanf(pFile, "%hu", &indeces[1]);

					fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

					fscanf(pFile, "%hu", &indeces[2]);

					fscanf(pFile, "%*s", buf);//*�͓ǂݎ̂Ă�

					model->m_index.push_back(indeces[0]);
					model->m_index.push_back(indeces[1]);
					model->m_index.push_back(indeces[2]);
				}

			}

			strcpy(prevBuf, buf);
		}

		fclose(pFile);
	}

}//namespace oka
