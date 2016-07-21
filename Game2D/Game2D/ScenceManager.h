 #pragma once
#include "Utilities/utilities.h"
#include "Object.h"
#include <vector>
#include "ResourceManager.h"
#include "Camera.h"
#include "AnimationManager.h"
#include "AnimationProperties.h"
#include "Sprite.h"
#include "Globals.h"

class Object;

class ScenceManager
{
public:
	ScenceManager();
	~ScenceManager();
	static  ScenceManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();

	Camera* GetCamara() const;
	Matrix GetPerspectiveMatrix() const;


	void Init(char *fileName);
	void Update(float deltaTime);
	void Draw();
	void AddObject(Object *object);
	void CleanUp();
	Object* GetObjByID(int id);
	Object* GetObjByType(SPRITETYPE type);
	Object* GetMainCharater() const;
private:
	static ScenceManager* s_Instance;
	vector<Object*> m_vlistObject;
	Camera *m_mainCamera;
	Matrix m_mPerspective;
	Object *m_mainCharater;
};