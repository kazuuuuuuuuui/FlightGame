#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include"Feald.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Image/BmpImage.h"

#include"../glut.h"

//------------------------
//コースの頂点データの生成

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
//コースのインデックスデータの生成

void Feald::SetIndex()
{
	for (int z = 0; z < (m_height - 1); z++)
	{
		for (int x = 0; x < (m_width - 1); x++)
		{
			m_index.push_back(0 + x + m_height * z);//0
			m_index.push_back(1 + x + m_height * z);//1
			m_index.push_back(m_width + x + m_height * z);//256
		
			m_index.push_back(1 + x + m_height * z);//1
			m_index.push_back((m_width + 1) + x + m_height * z);//257
			m_index.push_back(m_width + x + m_height * z);//256
		}
	}

	m_indeces = m_index.size();

}

//-------------------------------------
//法線の計算
//三角ポリゴン2枚を1組として外積計算

void Feald::SetNormal()
{
	for (unsigned int i = 0; i < m_indeces ;i+=3)
	{
		glm::vec3 v0 = m_vertex[m_index[i]];
		glm::vec3 v1 = m_vertex[m_index[i + 1]];
		glm::vec3 v2 = m_vertex[m_index[i + 2]];

//printf("v0 x:%f y:%f z:%f\n", m_vertex[m_index[i]].x, m_vertex[m_index[i]].y, m_vertex[m_index[i]].z);
//printf("v1 x:%f y:%f z:%f\n", m_vertex[m_index[i+1]].x, m_vertex[m_index[i + 1]].y, m_vertex[m_index[i + 1]].z);
//printf("v2 x:%f y:%f z:%f\n", m_vertex[m_index[i + 2]].x, m_vertex[m_index[i + 2]].y, m_vertex[m_index[i + 2]].z);

		glm::vec3 v01 = v1 - v0;
		glm::vec3 v02 = v2 - v0;

//printf("v01 x:%f y:%f z:%f\n", v01.x, v01.y, v01.z);
//printf("v02 x:%f y:%f z:%f\n", v02.x, v02.y, v02.z);

		glm::vec3 normal= glm::cross(v01, v02);

//printf("normal x:%f y:%f z:%f\n", normal.x, normal.y, normal.z);

//printf("\n");

		normal = glm::normalize(normal);
		
		m_normal.push_back(normal);
		m_normal.push_back(normal);
		m_normal.push_back(normal);
		
	}
}

//----------------
//uv座標の設定

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

//-------------------------------------
//拡張子bmpからコースの各頂点のY座標を設定する

void Feald::SetHeight(const char *_fileName)
{
	FILE *fp;
	fp = fopen(_fileName, "rb");

	assert(fp != NULL);

	BITMAPFILEHEADER bh;
	fread(&bh, sizeof(BITMAPFILEHEADER), 1, fp);

	BITMAPINFOHEADER bih;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

	int imageSize = bih.biWidth * bih.biHeight * sizeof(oka::RGB);

	oka::RGB *pixels = (oka::RGB*)malloc(imageSize);

	pixels = (oka::RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, fp);

	fclose(fp);

	//ピクセル単位でRとBを逆転させる
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//Y座標の設定
	for (int z = 0; z < bih.biHeight; z++)
	{
		for (int x = 0; x < bih.biWidth; x++)
		{
			float height = (pixels[z*bih.biWidth + x].r + pixels[z*bih.biWidth + x].g + pixels[z*bih.biWidth + x].b)/3.0f;
			
			height = 255.0f - height;//白と黒逆転
			height /= 255.0f;//0.0～1.0f;

			//最高座標点
			const int max = 3.0f;
			height *= max;//0.0～max

			m_vertex[z*bih.biWidth + x].y = height;
		}
	}

}


//-------------------------------------
//フィールド全体の描画

void Feald::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("FealdTex"));

		glPushMatrix();
		{
			auto v = m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto t = m_tex.begin();
			glTexCoordPointer(2, GL_FLOAT, 0, &(*t));

			auto i = m_index.begin();

			glDrawElements(GL_TRIANGLES, m_indeces, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Feald::Update()
{
	//debug
	//DrawNormals();
}


//-------------------------------------
//debug

void Feald::DrawNormals()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glm::vec3 root;
		glm::vec3 aim;

		for (unsigned int i = 0; i < m_indeces; i += 3)
		{
			root = (m_vertex[m_index[i]] + m_vertex[m_index[i + 1]] + m_vertex[m_index[i + 2]]) / 3.0f;

			//法線根元
			glPointSize(5);
			glColor3f(0, 0, 1);
			glBegin(GL_POINTS);
			{
				glVertex3f(root.x, root.y, root.z);
			}
			glEnd();


			aim = root + m_normal[i];

			//法線
			glBegin(GL_LINES);
			{
				glVertex3f(root.x, root.y, root.z);
				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
	}
	glPopAttrib();
}