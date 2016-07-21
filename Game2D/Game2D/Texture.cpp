#include "Texture.h"
Texture::Texture()
{
	Init();
}
Texture::Texture(GLuint textureId, char* source, OBJECTTYPE type)
{
	Init();
	m_iID = textureId;
	m_type = type;
	BindTextureData(source);
	SetWrappingMode(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	SetFilter(GL_LINEAR, GL_LINEAR);
}
Texture::Texture(GLuint textureId, char** source, OBJECTTYPE type)
{
	Init();
	m_iID = textureId;
	m_type = type;
	BindTextureData(source);
}
Texture::~Texture()
{
	CleanBuffer();
}

void Texture::Init()
{
	glGenTextures(1, &(this->m_iTextureId));
}

void Texture::BindTextureData(char* sourceFile) const
{
	int w, h, bpp;
	char *imageData;
	glBindTexture(GL_TEXTURE_2D, this->m_iTextureId);
	imageData = LoadTGA(sourceFile, &w, &h, &bpp);
	if (bpp == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	delete[]imageData;
}

void Texture::BindTextureData(char** sourceFile) const
{
	int w, h, bpp;
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_iTextureId);
	char *imageData;
	for (int i = 0; i < 6; i++)
	{
		imageData = LoadTGA(sourceFile[i], &w, &h, &bpp);
		if (bpp == 24)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		else
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		delete[] imageData;
	}
}

void Texture::SetWrappingMode(GLint wrap_s, GLint wrap_t)
{

	if (m_type == CUBEOBJECT)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap_t);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
	}

}

void Texture::SetFilter(GLint maxFilter, GLint minFilter)
{
	if (m_type == CUBEOBJECT)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, maxFilter);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
	}
}
void Texture::CleanBuffer()
{
	glDeleteTextures(1, &(this->m_iTextureId));
}

GLuint Texture::GetID() const
{
	return  this->m_iID;
}
void Texture::SetID(GLuint ID)
{
	this->m_iID = ID;
}

OBJECTTYPE Texture::GetType() const
{
	return m_type;
}
void Texture::SetType(OBJECTTYPE type)
{
	m_type = type;
}
GLuint Texture::GetTextureId() const
{
	return m_iTextureId;
}

