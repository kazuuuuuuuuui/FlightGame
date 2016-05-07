#include"Particle.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"
#include"../glut.h"

void Particle::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Smoke"));

		glPushMatrix();
		{
			//glMultMatrixf((GLfloat*)&m_matrix);

			glTranslatef(m_transform.GetPosition().x, m_transform.GetPosition().y, m_transform.GetPosition().z);

			//ビルボード回転行列適用
			glMultMatrixf((GLfloat*)&BillboardMatrix);

			glScalef(m_transform.GetScale().x, m_transform.GetScale().y, m_transform.GetScale().z);

			glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.f, 1.f);
				glVertex2f(-1.f, -1.f);

				glTexCoord2f(0.f, 0.f);
				glVertex2f(-1.f, 1.f);

				glTexCoord2f(1.f, 0.f);
				glVertex2f(1.f, 1.f);

				glTexCoord2f(1.f, 1.f);
				glVertex2f(1.f, -1.f);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Particle::Update()
{
	/*glm::mat4 translate = glm::mat4::Translate(m_transform.GetPosition());
	
	BillboardMatrix = glm::inverse(g_camera->GetViewMatrix());
	BillboardMatrix[3][0] = 0;
	BillboardMatrix[3][1] = 0;
	BillboardMatrix[3][2] = 0;

	glm::mat4 scale = glm::mat4::Scale(m_transform.GetScale());*/

	//m_matrix = translate * BillboardMatrix * scale;

}