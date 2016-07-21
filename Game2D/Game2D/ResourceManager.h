#pragma once
#include "Utilities/utilities.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	static  ResourceManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();

	GLuint GetModelCount() const;
	GLuint GetShaderCoumt() const;
	GLuint GetTextureCount() const;
	GLuint GetCubeTextureCount() const;
	Texture** GetListTexture() const;
	Texture** GetListCubeTexture() const;
	Model** GetListModel() const;
	Shader** GetListShader() const;


	void Init(char* fileName);
	Model* FindModelById(GLuint modelId) const;
	Shader* FindShaderById(GLuint shaderId) const;
	Texture* FindTextureById(GLuint textureId) const;
	Texture* FindCubeTextureById(GLuint cubeTextureId) const;
	void CleanUp() const;
private:
	static ResourceManager* s_Instance;
	GLuint m_iModelCount;
	GLuint m_iShaderCount;
	GLuint m_iTextureCount;
	GLuint m_iCubeTextureCount;

	Texture** m_listTexture;
	Texture** m_listCubeTexture;
	Model** m_listModel;
	Shader** m_listShader;
};