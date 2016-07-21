#pragma once
#include "Utilities/utilities.h"
#include "Globals.h"

class Texture
{
public:
	Texture();
	Texture(GLuint textureId, char* source,OBJECTTYPE type);
	Texture(GLuint textureId, char** source,OBJECTTYPE type);
	~Texture();

	GLuint GetTextureId() const;
	GLuint GetID() const;
	void SetID(GLuint textureId);
	OBJECTTYPE GetType() const;
	void SetType(OBJECTTYPE type);

	void Init();
	void SetWrappingMode(GLint wrap_s, GLint wrap_t);
	void SetFilter(GLint maxFilter, GLint minFilter);
	void BindTextureData(char* sourceFile) const;
	void BindTextureData(char** sourceFile) const;
	
	void CleanBuffer();

private:
	GLuint m_iTextureId, m_iID;
	OBJECTTYPE m_type;
};