#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"xFile.h"
//#include"../Vector/Vec3.h"

namespace oka
{
	//-------------------------------------
	//xファイルから3Dモデルを読み込み
	
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
			//頂点データ読み込み

			if (0 == strcmp("Mesh", buf))
			{
				fscanf(fp, "%*1s", buf);// { の読み飛ばし

										//頂点数読み込み
				fscanf(fp, "%u", &model->m_vertices);
				
				fscanf(fp, "%*1s", buf);// ; の読み飛ばし
										//頂点の読み込み
				for (unsigned int i = 0; i < model->m_vertices; i++)
				{
					glm::vec3 v;

					fscanf(fp, "%f;%f;%f;", &v.x, &v.y, &v.z);

					model->m_vertex.push_back(v);

					fscanf(fp, "%*1s", buf);// ,　の読み飛ばし	
				}


				//-------------------------------------
				//インデックスデータ読み込み

				//インデックス数の読み込み
				fscanf(fp, "%u", &model->m_indeces);

				fscanf(fp, "%*s", buf);// ; の読み飛ばし

									   //インデックスの読み込み
				for (unsigned int i = 0; i < model->m_indeces; i++)
				{
					unsigned short index[3];

					fscanf(fp, "%*2s", buf);// 3; 読み飛ばし

					fscanf(fp, "%hu,%hu,%hu", &index[0], &index[1], &index[2]);

					fscanf(fp, "%*s", buf);// , 読み飛ばし

					model->m_index.push_back(index[0]);
					model->m_index.push_back(index[1]);
					model->m_index.push_back(index[2]);
				}
			}

			//-------------------------------------
			//法線情報の読み込み

			if (0 == strcmp("MeshNormals", buf))
			{
				fscanf(fp, "%*1s", buf);// { の読み飛ばし

										//法線数の読み込み
				fscanf(fp, "%u", &model->m_normals);

				fscanf(fp, "%*1s", buf);// ; の読み飛ばし

										//法線の読み込み
				for (unsigned int i = 0; i < model->m_normals; i++)
				{
					glm::vec3 n;

					fscanf(fp, "%f;%f;%f;", &n.x, &n.y, &n.z);

					model->m_normal.push_back(n);

					fscanf(fp, "%*1s", buf);// ,　の読み飛ばし	
				}
			}

			//-------------------------------------
			//uv情報の読み込み

			//fscanf(fp, "%s", buf);
			//printf("%s", buf);
		}

		fclose(fp);

		return model;
	}

}//namespace oka
