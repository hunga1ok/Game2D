#pragma once
#include "Utilities/utilities.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include <vector>
#include "Animation.h"

class ScenceManager;

using namespace std;
class Object
{
public:
	Object();
	Object(vector<Texture*>  textures, Model *model,vector<Animation*> listAniamtion, Shader *shader, OBJECTTYPE objType);
	virtual ~Object();

	void SetScale(Matrix scale);
	void SetRotate(Matrix rotate);
	void SetTranslate(Matrix translate);
	Matrix GetWorldMatrix();
	Matrix GetMVP();
	void SetObjectId(GLuint objectId);
	GLuint GetObjectId() const;
	Model* GetModel() const;
	vector<Animation*> GetListAnimation() const;
	float GetAnimatedSpeed() const;
	void SetAnimatedSpeed(float speed);
	float GetSpeed() const;
	void SetSpeed(float speed);
	Vector3 GetPosition() const;
	OBJECTSTATE GetObjectState() const;
	void SetObjectState(OBJECTSTATE state);
	SPRITETYPE GetSpriteType() const;
	void SetSpriteType(SPRITETYPE type);
	bool IsJumping() const;
	void IsJumping(bool b);

	void Init();
	void Draw();
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	virtual void OnCollision();

protected:
	Matrix m_mTranslate, m_mScale, m_mRotate;
	GLuint m_iObjectId;
	Matrix m_mMVP, m_mWorld;
	Matrix m_mMoveMatrix;
	Vector3 m_v3position;
	
	
	GLuint m_iTexturesCount;
	vector<Texture*> m_vListTextures;
	vector<Animation*> m_vListAnimation;
	Model *m_model;
	Shader *m_shader;
	OBJECTTYPE m_objectType;
	SPRITETYPE m_spriteType;
	OBJECTSTATE m_objectState;
	float m_fAnimatedSpeed;
	float m_fSpeed;
	float m_animationTemp;
	int m_iNumberOfFrame;
	int* AnimationOffset;
	bool m_bisJumping;
};