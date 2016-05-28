#include"Mesh.h"

#include"../../glut.h"

namespace oka
{
	Mesh::Mesh(Model *_model,unsigned int _texture)
	{
		m_isLighting = true;
		m_isBlend = false;
		m_model = _model;
		m_texture = _texture;
	}

	void Mesh::Draw()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			if (NULL != m_texture)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_texture);
			}

			if (false == m_isLighting)
			{
				glDisable(GL_LIGHTING);
			}

			if (m_isBlend)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
			}

			glEnableClientState(GL_VERTEX_ARRAY);
			auto v = m_model->m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			glEnableClientState(GL_NORMAL_ARRAY);
			auto n = m_model->m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto t = m_model->m_tex.begin();
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, &(*t));

			auto i = m_model->m_index.begin();

			glPushMatrix();
			{
				glMultMatrixf((GLfloat*)&m_transform.m_matrix);

				glDrawElements(GL_TRIANGLES, m_model->m_indexNum * 3, GL_UNSIGNED_SHORT, &(*i));

			}
			glPopMatrix();
		}
		glPopAttrib();
	}
}