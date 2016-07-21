#include "ScenceManager.h"


ScenceManager* ScenceManager::s_Instance = nullptr;
ScenceManager::ScenceManager() : m_mainCamera(nullptr), m_mainCharater(nullptr)
{
}

ScenceManager::~ScenceManager()
{
	CleanUp();
}
ScenceManager* ScenceManager::GetInstance()
{
	return s_Instance;
}
void ScenceManager::CreateInstance()
{
	if (!s_Instance)
		s_Instance = new ScenceManager();
}
void ScenceManager::DestroyInstance()
{
	if (s_Instance)
		delete s_Instance;
}
void ScenceManager::Init(char *fileName)
{
	FILE *f;
	f = fopen(fileName, "r");
	if (f)
	{
		int objectCount;
		fscanf(f, "ObjectsCount %d\n", &objectCount);
		for (int i = 0; i < objectCount; i++)
		{
			int objectId, modelId, textureId, animationID, shaderId, textureCount, textcubeCount, animationCount;
			float px, py, pz, rx, ry, rz, sx, sy, sz, speed, frameRate;
			char* type = new char[15];
			OBJECTTYPE objType = ENDO;
			SPRITETYPE spriteType = ENDS;
			std::vector<Texture*> listTextures;
			std::vector<Animation*> listAnimation;
			fscanf(f, "ID %d //%*s\n", &objectId);
			fscanf(f, "TYPE %s\n", type);
			if (strcmp(type, "OBJECT2D") == 0)
			{
				fscanf(f, "SPRITETYPE %s\n", type);
			}
			fscanf(f, "MODEL_ID %d\n", &modelId);
			fscanf(f, "ANIMATIONS %d\n", &animationCount);
			for (int j = 0; j < animationCount; j++)
			{
				fscanf(f, "ANIMATION_ID %d\n", &animationID);
				Animation *animation = AnimationManager::GetInstance()->FindAnimationById(animationID);
				listAnimation.push_back(animation);
			}

			fscanf(f, "TEXTURES %d\n", &textureCount);
			for (int j = 0; j < textureCount; j++)
			{
				fscanf(f, "TEXTURE_ID %d\n", &textureId);
				Texture *texture = ResourceManager::GetInstance()->FindTextureById(textureId);
				listTextures.push_back(texture);
			}
			fscanf(f, "CUBETEXS %d\n", &textcubeCount);
			for (int j = 0; j < textcubeCount; j++)
			{
				fscanf(f, "CUBETEX_ID %d\n", &textureId);
				Texture *texture = ResourceManager::GetInstance()->FindCubeTextureById(textureId);
				listTextures.push_back(texture);
			}
			fscanf(f, "SHADER_ID %d\n", &shaderId);
			fscanf(f, "SPEED %f\n", &speed);
			fscanf(f, "FRAMERATE %f\n", &frameRate);

			fscanf(f, "POS %f,%f,%f\n", &px, &py, &pz);
			fscanf(f, "ROTATION %f,%f,%f\n", &rx, &ry, &rz);
			fscanf(f, "SCALE %f,%f,%f\n", &sx, &sy, &sz);

			Model *model = ResourceManager::GetInstance()->FindModelById(modelId);
			Shader* shader = ResourceManager::GetInstance()->FindShaderById(shaderId);

			if (strcmp(type, "CUBEOBJECT") == 0)
				objType = CUBEOBJECT;
			else
				if (strcmp(type, "OBJECT2D") == 0)
					objType = OBJECT2D;
				else
					if (strcmp(type, "OBJECT3D") == 0)
						objType = OBJECT3D;
					else
						if (strcmp(type, "TERRAIN") == 0)
							objType = TERRAIN;
			if (strcmp(type, "RAT") == 0)
				spriteType = RAT;
			else if (strcmp(type, "CAT") == 0)
				spriteType = CAT;
			else if (strcmp(type, "TRAP") == 0)
				spriteType = TRAP;
			else if (strcmp(type, "ITEM") == 0)
				spriteType = ITEM;
			else spriteType = BACKGROUND;

			Object* object = nullptr;
			if (objType == ENDO)
			{
				vector<AnimationProperties> listAnimationIndex;
				if (listAnimation.size() > 0)
				{
					for (auto it : listAnimation)
					{
						for (auto k = 0; k < it->GetIndexNumber(); k++)
						{
							listAnimationIndex.push_back(it->GetListIndex()[k]);
						}
					}
					model->LoadModel(listAnimationIndex);
					model->BufferVBO();
					model->BufferIBO();
				}
				object = new Sprite(listTextures, model, listAnimation, shader, spriteType);
				object->SetSpeed(speed);
				object->SetAnimatedSpeed(frameRate);
			}
			else
				object = new Object(listTextures, model, listAnimation, shader, objType);
			object->SetObjectId(objectId);


			Matrix tran, rotate, scale, rox, roy, roz;
			tran.SetTranslation(px, py, pz);
			rox.SetRotationX(rx*3.14 / 180);
			roy.SetRotationY(ry*3.14 / 180);
			roz.SetRotationZ(rz*3.14 / 180);
			rotate.SetIdentity();
			rotate = roz*rox*roy;
			scale.SetScale(sx, sy, sz);
			object->SetTranslate(tran);
			object->SetRotate(rotate);
			object->SetScale(scale);
			object->GetWorldMatrix();
			if (spriteType == RAT)
				m_mainCharater = object;
			AddObject(object);
		}
		float cnear, cfar, cfov, cspeed, csensitivity;
		fscanf(f, "#Camera\n");
		fscanf(f, "NEAR %f\n", &cnear);
		fscanf(f, "FAR %f\n", &cfar);
		fscanf(f, "FOV %f\n", &cfov);
		fscanf(f, "SPEED %f\n", &cspeed);
		fscanf(f, "SEN %f\n", &csensitivity);
		m_mainCamera = new Camera(cspeed, csensitivity);
		m_mPerspective.SetPerspective(cfov, Globals::screenWidth / Globals::screenHeight, cnear, cfar);
	}
	fclose(f);
	//m_mainCharater = GetObjByType(RAT);
}

void ScenceManager::AddObject(Object* object)
{
	m_vlistObject.push_back(object);
}
void ScenceManager::Update(float deltaTime)
{
	if (deltaTime <= 0)
		return;
	m_mainCharater->Update(deltaTime);
	Vector3 vec3 = Vector3(m_mainCharater->GetPosition().x, 0, 0);
	m_mainCamera->SetPosition(vec3);
	m_mainCamera->CalculateViewMatrix();
//	m_mainCharater->SetViewMatrix(m_mainCamera->GetViewMatrix());
	for (auto it : m_vlistObject)
	{
		if (it->GetSpriteType()!=RAT)
		{
			it->Update(deltaTime);
//			it->SetViewMatrix(m_mainCamera->GetViewMatrix());
			if (it->GetSpriteType() == BACKGROUND)
			{
				if (m_mainCamera->GetPosition().x - it->GetPosition().x > 1)
				{
					Matrix a;
					a.SetTranslation(2, 0, 0);
					it->SetTranslate(a);
					it->GetWorldMatrix();
				}
			}
		}
	}
	/*Vector3 vec3 = Vector3(m_mainCharater->GetPosition().x, 0, 0);
	m_mainCamera->SetPosition(vec3);
	m_mainCamera->CalculateViewMatrix();*/

}

void ScenceManager::Draw()
{
	for (auto it : m_vlistObject)
	{
		it->Draw();
	}
}
void ScenceManager::CleanUp()
{
	for (auto it : m_vlistObject)
		delete it;
	delete m_mainCamera;
}

Object* ScenceManager::GetObjByID(int id)
{
	for (auto it : m_vlistObject)
	{
		if (it->GetObjectId() == id)
			return it;
	}
	return nullptr;
}

Object* ScenceManager::GetObjByType(SPRITETYPE type)
{
	for (auto it : m_vlistObject)
	{
		if (it->GetSpriteType() == type)
			return it;
	}
	return nullptr;
}

Object* ScenceManager::GetMainCharater() const
{
	return m_mainCharater;
}

Camera* ScenceManager::GetCamara() const
{
	return m_mainCamera;
}
Matrix ScenceManager::GetPerspectiveMatrix() const
{
	return m_mPerspective;
}