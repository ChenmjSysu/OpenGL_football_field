#include "skybox.h"
#include "base.h"

SkyBox::SkyBox() {
	for(int i = 0; i < 6; i++) {
		m_textures[i] = 0;
	}
}

SkyBox::~SkyBox() {
    release_textures();
}

void SkyBox::init(float size) {
    m_size = size;
}

bool SkyBox::load_texture(char *top, char *bottom, char *front, char *back, char *left, char *right) {
	CTargaImage image;
	//��������
	image.Load(top);
	glGenTextures(1, &m_textures[SKY_TOP]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_TOP]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//�ײ�����
	image.Load(bottom);
	glGenTextures(1, &m_textures[SKY_BOTTOM]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_BOTTOM]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//ǰ�����
	image.Load(front);
	glGenTextures(1, &m_textures[SKY_FRONT]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_FRONT]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//�������
	image.Load(back);
	glGenTextures(1, &m_textures[SKY_BACK]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_BACK]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//��ߵ���
	image.Load(left);
	glGenTextures(1, &m_textures[SKY_LEFT]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_LEFT]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//�ұߵ���
	image.Load(right);
	glGenTextures(1, &m_textures[SKY_RIGHT]);
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_RIGHT]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();

	return true;
}

void SkyBox::render(float x, float y, float z) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(x, y, z);
	//glPushAttrib(GL_FOG_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
	//glDisable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//���ƶ�������
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_TOP]);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, m_size, m_size);
	glEnd();

	//���Ƶײ�����
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_BOTTOM]);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, -m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
	glEnd();

	//����ǰ�����
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
	glEnd();

	//���ƺ������
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_BACK]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
	glEnd();

	//�����ұߵ���
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_RIGHT]);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
	glEnd();

	//������ߵ���
	glBindTexture(GL_TEXTURE_2D, m_textures[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	//glEndList();
	//�ָ�����
	glPopMatrix();
}

//�ͷ�����
void SkyBox::release_textures() {
	for (int i = 0; i < 6; ++i)
		glDeleteTextures(6, &m_textures[0]);
}