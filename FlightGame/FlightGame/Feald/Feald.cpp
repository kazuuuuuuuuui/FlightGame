#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include"Feald.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Image/BmpImage.h"
#include"../glut.h"

Feald::Feald() :
	m_width(256),
	m_depth(256),
	m_leftBottom(glm::vec3(-200.0f, 2.0f, 180.0f)),
	m_rightBottom(glm::vec3(400.0f, 2.0f, 180.0f)),
	m_leftTop(glm::vec3(-200.0f, 2.0f, -450.0f)),
	m_rightTop(glm::vec3(400.0f, 2.0f, -450.0f))
{
	//頂点データ
	SetVertex();

	//インデックスデータ
	SetIndex();

	//頂点の高さ設定
	SetHeight("Image/heightmap.bmp");

	//法線データ
	SetNormal();

	//uvデータ
	SetTex();

};

Feald::~Feald()
{

};

//-------------------------------------
//フィールドの生成
//戻り値としてFealdへのsharedポインタを返す

FealdSP Feald::Create()
{
	FealdSP feald(new Feald());

	return feald;
}

//------------------------
//コースの頂点データの生成

void Feald::SetVertex()
{
	for (int z = 0; z < m_depth; z++)
	{
		for (int x = 0; x < m_width; x++)
		{
			m_vertex.push_back(glm::vec3(x, 0, -z));
		}
	}

	m_vertices = m_vertex.size();

}

/*
distance = 10.f;
for (int i = 0; i < index_num;  i += 3);{
v  m_vertex[m_index[i]]
v1 m_vertex[m_index[i + 1]]
v2 m_vertex[m_index[i + 2]]

c = (v + v1 + v2) / 3;

m_distance = zettaiti(p.x - c.x) + zettaiti(p.z - c.z);
if (m_distance < distance) {
	distance = m_distance;
	tmp = i;
}
}

v  m_vertex[m_index[tmp]]
v1 m_vertex[m_index[tmp + 1]]
v2 m_vertex[m_index[tmp + 2]]

p.Upvec = vの三角形の法線;

v1.y-v.y/ ( (p.x-v.x) /(v1.x-v.x))
*/


//-------------------------------------
//コースのインデックスデータの生成

void Feald::SetIndex()
{
	for (int z = 0; z < (m_depth - 1); z++)
	{
		for (int x = 0; x < (m_width - 1); x++)
		{
			m_index.push_back(0 + x + m_depth * z);
			m_index.push_back(1 + x + m_depth * z);
			m_index.push_back(m_width + x + m_depth * z);
		
			m_index.push_back(1 + x + m_depth * z);
			m_index.push_back((m_width + 1) + x + m_depth * z);
			m_index.push_back(m_width + x + m_depth * z);
		}
	}

	m_indeces = m_index.size();

}

//-------------------------------------
//法線の設定

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
//uv座標の設定

void Feald::SetTex()
{
	for (int v = m_depth; v > 0; v--)
	{
		for (int u = 0; u < m_width; u++)
		{
			glm::vec2 t;
			t.x = (u / 1.0f) / m_width;//u
			t.y = (v / 1.0f) / m_depth;//v

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
			const int max = 20.0f;
			height *= max;//0.0～max

			m_vertex[z*bih.biWidth + x].y = height;
		}
	}

}

//-------------------------------------
//フィールドの幅を返す

int Feald::GetWidth()const
{
	return m_width;
}

//-------------------------------------
//フィールドの奥行を返す

int Feald::GetDepth()const
{
	return m_depth;
}


//-------------------------------------
//フィールド全体の描画

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
			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Grand"));

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
