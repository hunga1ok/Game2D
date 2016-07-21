#include "ResourceManager.h"

ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	CleanUp();
}
ResourceManager* ResourceManager::GetInstance()
{
	return s_Instance;
}
void ResourceManager::CreateInstance()
{
	if (!s_Instance)
		s_Instance = new ResourceManager();
}
void ResourceManager::DestroyInstance()
{
	if (s_Instance)
	delete s_Instance;
}

void ResourceManager::Init(char* fileName)
{
	FILE *f;
	f = fopen(fileName, "r");
	if (f)
	{
		int id;

		OBJECTTYPE type;
		fscanf(f, "ModelsCount %d\n", &this->m_iModelCount);
		this->m_listModel = new Model*[this->m_iModelCount];
		for (auto i = 0; i < m_iModelCount; i++)
		{
			auto modelType = new char[10];
			auto path = new char[100];
			Model *model;
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "TYPE %s\n", modelType);
			if (!strcmp(modelType,"SPRITE"))
			{
				int x, y, w, h, tw, th;
				fscanf(f, "POS: %d, %d, %d, %d, %d, %d\n", &x, &y, &w, &h, &tw, &th);
				auto index = AnimationProperties(x,y,w,h,tw,th);
				model = new Model(index,id);
			}
			else
			{
				fscanf(f, "FILE %s\n", path);
				model = new Model(path, id);
			}
			
			m_listModel[i] = model;
			delete[] path;
		}
		fscanf(f, "TexturesCount %d\n", &this->m_iTextureCount);
		this->m_listTexture = new Texture*[m_iTextureCount];
		for (int i = 0; i < m_iTextureCount; i++)
		{
			char *stype = new char[10];
			char *path = new char[100];
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "TYPE %s\n", stype);
			fscanf(f, "FILE %s\n", path);
			if (strcmp(stype, "OBJECT2D") == 0)
				type = OBJECT2D;
			else
				if (strcmp(stype, "OBJECT3D") == 0)
					type = OBJECT3D;
				else
					type = TERRAIN;
			Texture *texture = new Texture(id, path, type);
			m_listTexture[i] = texture;
			delete[]path;
			delete[]stype;
		}
		fscanf(f, "CubeTexturesCount %d\n", &this->m_iCubeTextureCount);
		this->m_listCubeTexture = new Texture*[m_iCubeTextureCount];
		for (int i = 0; i < m_iCubeTextureCount; i++)
		{
			char **t = new char*[6];
			char *path1 = new char[100];
			char *path2 = new char[100];
			char *path3 = new char[100];
			char *path4 = new char[100];
			char *path5 = new char[100];
			char *path6 = new char[100];
			fscanf(f, "ID %d\n", &id);

			fscanf(f, "FILE %s\n", path1);
			fscanf(f, "FILE %s\n", path2);
			fscanf(f, "FILE %s\n", path3);
			fscanf(f, "FILE %s\n", path4);
			fscanf(f, "FILE %s\n", path5);
			fscanf(f, "FILE %s\n", path6);

			t[0] = path1;
			t[1] = path2;
			t[2] = path3;
			t[3] = path4;
			t[4] = path5;
			t[5] = path6;

			Texture *cubeTexture = new Texture(id, t, CUBEOBJECT);
			m_listCubeTexture[i] = cubeTexture;
			delete[] path1;
			delete[] path2;
			delete[] path3;
			delete[] path4;
			delete[] path5;
			delete[] path6;
			delete[] t;
		}
		fscanf(f, "ShadersCount %d\n", &this->m_iShaderCount);
		this->m_listShader = new Shader*[m_iShaderCount];
		for (int i = 0; i < m_iShaderCount; i++)
		{
			char *pathvs = new char[100], *pathfs = new char[100];
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "VS %s\n", pathvs);
			fscanf(f, "FS %s\n", pathfs);
			Shader *shader = new Shader(id,pathvs, pathfs);
			m_listShader[i] = shader;
			delete[] pathfs;
			delete[] pathvs;
		}
		fclose(f);
	}
}
Texture* ResourceManager::FindTextureById(GLuint textureId) const
{
	for (int i = 0; i < m_iTextureCount; i++)
	{
		if (m_listTexture[i]->GetID() == textureId)
			return m_listTexture[i];
	}
	return nullptr;

}
Shader* ResourceManager::FindShaderById(GLuint shaderId) const
{
	for (int i = 0; i < m_iShaderCount; i++)
	{
		if (m_listShader[i]->GetID() == shaderId)
			return m_listShader[i];
	}
	return nullptr;

}
Model* ResourceManager::FindModelById(GLuint modelId) const
{
	for (int i = 0; i < m_iModelCount; i++)
	{
		if (m_listModel[i]->GetID() == modelId)
			return m_listModel[i];
	}
	return nullptr;

}
Texture* ResourceManager::FindCubeTextureById(GLuint cubeTextureId) const
{
	for (int i = 0; i < m_iCubeTextureCount; i++)
	{
		if (m_listCubeTexture[i]->GetID() == cubeTextureId)
			return  m_listCubeTexture[i];
	}
	return nullptr;
}

void ResourceManager::CleanUp() const
{
	for (int i = 0; i < m_iModelCount; i++)
	{
		delete m_listModel[i];
	}

	for (int i = 0; i < m_iTextureCount; i++)
	{
		delete m_listTexture[i];
	}
	for (int i = 0; i < m_iCubeTextureCount; i++)
	{
		delete m_listCubeTexture[i];
	}
	for (int i = 0; i < m_iShaderCount; i++)
	{
		delete m_listShader[i];
	}
	delete m_listShader;
	delete m_listTexture;
	delete m_listCubeTexture;
	delete m_listModel;
}

GLuint ResourceManager::GetModelCount() const
{
	return m_iModelCount;
}
GLuint ResourceManager::GetTextureCount() const
{
	return m_iTextureCount;
}
GLuint ResourceManager::GetShaderCoumt() const
{
	return m_iShaderCount;
}
GLuint ResourceManager::GetCubeTextureCount() const
{
	return m_iCubeTextureCount;
}
Texture** ResourceManager::GetListCubeTexture() const
{
	return m_listCubeTexture;
}
Model** ResourceManager::GetListModel() const
{
	return m_listModel;
}

Shader** ResourceManager::GetListShader() const
{
	return m_listShader;
}
Texture** ResourceManager::GetListTexture() const
{
	return m_listTexture;
}



